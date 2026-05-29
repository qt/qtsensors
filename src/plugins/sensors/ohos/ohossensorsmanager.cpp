// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qcore_ohos_p.h>
#include <QtCore/private/qohoslogger_p.h>
#include <ohossensorsmanager.h>
#include <ohossensorutils.h>
#include <algorithm>
#include <chrono>
#include <optional>

namespace {

std::optional<std::vector<float>> tryGetSensorEventData(::Sensor_Event *sensorEvent)
{
    float *data = nullptr;
    std::uint32_t len = 0;
    std::int32_t getDataResult = ::OH_SensorEvent_GetData(sensorEvent, &data, &len);
    if (getDataResult != ::SENSOR_SUCCESS) {
        qOhosPrintfError("%s: OH_SensorEvent_GetData failed, code=%d", Q_FUNC_INFO, getDataResult);
        return std::nullopt;
    }
    if (data == nullptr) {
        qOhosPrintfError("%s: data pointer is null", Q_FUNC_INFO);
        return std::nullopt;
    }
    return std::vector<float>(data, data + len);
}

std::shared_ptr<std::vector<::Sensor_Info *>> tryCreateInfos(std::uint32_t count)
{
    ::Sensor_Info **sensors = ::OH_Sensor_CreateInfos(count);
    if (sensors == nullptr) {
        qOhosPrintfError("%s: cannot create sensor infos objects", Q_FUNC_INFO);
        return nullptr;
    }

    auto sensorsWrapper = std::shared_ptr<void>(
        sensors,
        [sensors, count](auto *) {
            std::uint32_t destroyInfosResult = ::OH_Sensor_DestroyInfos(sensors, count);
            if (destroyInfosResult != ::SENSOR_SUCCESS) {
                qOhosPrintfError(
                    "%s: cannot destroy sensor infos, error: %d", Q_FUNC_INFO, destroyInfosResult);
            }
        }
    );

    return QtOhos::makeSharedPtrWithAttachedExtraData(
        std::make_shared<std::vector<::Sensor_Info *>>(sensors, sensors + count),
        sensorsWrapper);
}

std::shared_ptr<std::vector<::Sensor_Info *>> tryGetAvailableSensorsInfo()
{
    std::uint32_t sensorsCount = 0;
    std::uint32_t getSensorsCountResult = ::OH_Sensor_GetInfos(nullptr, &sensorsCount);
    if (getSensorsCountResult != ::SENSOR_SUCCESS) {
        qOhosPrintfError(
            "%s: cannot get sensors count, error: %d", Q_FUNC_INFO, getSensorsCountResult);
        return nullptr;
    }

    auto sensors = tryCreateInfos(sensorsCount);
    if (!sensors) {
        return nullptr;
    }

    std::uint32_t getInfosResult = ::OH_Sensor_GetInfos(sensors->data(), &sensorsCount);
    if (getInfosResult != ::SENSOR_SUCCESS) {
        qOhosPrintfError(
            "%s: cannot get sensors infos, error: %d", Q_FUNC_INFO, getInfosResult);
        return nullptr;
    }

    return sensors;
}

}

OhosSensorsManager::OhosSensorsManager()
{
    QOhosJsThreadGateway::runAndWait(
        [&](QOhosJsState &) {
            m_jsScopeData = QtOhos::makeProxyWithJsThreadDeleter(std::make_shared<JsScopeData>());

            m_jsScopeData->availableSensorsInfo = tryGetAvailableSensorsInfo();

            m_jsScopeData->subscriber = tryCreateSensorResource<::Sensor_Subscriber>(
                ::OH_Sensor_CreateSubscriber, ::OH_Sensor_DestroySubscriber);
            if (!m_jsScopeData->subscriber) {
                qOhosReportFatalErrorAndAbort("%s: Failed to create sensor subscriber.", Q_FUNC_INFO);
            }

            std::int32_t setCallbackRetVal = ::OH_SensorSubscriber_SetCallback(
                m_jsScopeData->subscriber.get(), OhosSensorsManager::sensorEventCallbackHandler);
            if (setCallbackRetVal != ::SENSOR_SUCCESS) {
                qOhosReportFatalErrorAndAbort(
                    "%s: OH_SensorSubscriber_SetCallback fail with error code: %d",
                    Q_FUNC_INFO, setCallbackRetVal);
            }
        });
}

OhosSensorsManager *OhosSensorsManager::instance()
{
    static OhosSensorsManager sensorManager;
    return &sensorManager;
}

std::vector<::Sensor_Type> OhosSensorsManager::getAvailableSensorsTypes()
{
    return QOhosJsThreadGateway::eval(
        [&](QOhosJsState &) {
            std::vector<::Sensor_Type> result;

            auto sensorsInfo = m_jsScopeData->availableSensorsInfo;
            if (sensorsInfo) {
                for (auto *sensorInfo : *sensorsInfo) {
                    auto sensorType = tryGetSensorInfoField<::Sensor_Type>(sensorInfo, ::OH_SensorInfo_GetType);
                    if (sensorType.has_value()) {
                        result.push_back(sensorType.value());
                    }
                }
            }

            return result;
        });
}

std::optional<OhosSensorCapabilities> OhosSensorsManager::tryGetSensorCapabilities(QSensor *sensor)
{
    auto ohosSensorType = tryMapQtToOhosSensorType(sensor->type());
    if (!ohosSensorType.has_value()) {
        qOhosPrintfError(
            "%s: Cannot map Qt sensor type: %s, to OHOS Sensor_Type",
            Q_FUNC_INFO, sensor->type().toStdString().c_str());
        return std::nullopt;
    }

    return QOhosJsThreadGateway::eval(
        [&](QOhosJsState &) -> std::optional<OhosSensorCapabilities> {
            auto availableSensorsInfo = m_jsScopeData->availableSensorsInfo;
            if (!availableSensorsInfo) {
                return std::nullopt;
            }

            auto sensorInfo = std::find_if(
                availableSensorsInfo->begin(),
                availableSensorsInfo->end(),
                [&](auto *info) {
                    return tryGetSensorInfoField<::Sensor_Type>(info, ::OH_SensorInfo_GetType) == ohosSensorType;
                });

            if (sensorInfo == availableSensorsInfo->end()) {
                qOhosPrintfError(
                    "%s: Cannot find a sensor info for a sensor of type: %d",
                    Q_FUNC_INFO, ohosSensorType.value());
                return std::nullopt;
            }

            auto resolution = tryGetSensorInfoField<float>(*sensorInfo, ::OH_SensorInfo_GetResolution);
            if (!resolution.has_value()) {
                qOhosPrintfError(
                    "%s: Cannot get resolution for a sensor of type: %d", Q_FUNC_INFO, ohosSensorType.value());
                return std::nullopt;
            }

            auto minSamplingIntervalInNs = tryGetSensorInfoField<std::int64_t>(
                *sensorInfo, ::OH_SensorInfo_GetMinSamplingInterval);
            if (!minSamplingIntervalInNs.has_value()) {
                qOhosPrintfError(
                    "%s: Cannot get minimal sampling interval for a sensor of type: %d",
                    Q_FUNC_INFO, ohosSensorType.value());
                return std::nullopt;
            }

            auto maxSamplingIntervalInNs = tryGetSensorInfoField<std::int64_t>(
                *sensorInfo, ::OH_SensorInfo_GetMaxSamplingInterval);
            if (!maxSamplingIntervalInNs.has_value()) {
                qOhosPrintfError(
                    "%s: Cannot get maximal sampling interval for a sensor of type: %d",
                    Q_FUNC_INFO, ohosSensorType.value());
                return std::nullopt;
            }

            auto samplingIntervalToDataRate =
                [](std::int64_t intervalInNs) -> int {
                    return intervalInNs != 0
                        ? 1e9 / intervalInNs
                        : 0;
                };

            return OhosSensorCapabilities{
                resolution.value(),
                samplingIntervalToDataRate(maxSamplingIntervalInNs.value()),
                samplingIntervalToDataRate(minSamplingIntervalInNs.value())
            };
        });
}

void OhosSensorsManager::subscribeSensor(QSensor *sensor, QOhosConsumer<const OhosSensorData &> sensorDataConsumer)
{
    auto subscribedSensor = m_subscribedSensors.find(sensor);
    if (subscribedSensor != m_subscribedSensors.end()) {
        qOhosPrintfError(
            "%s: Sensor %s already subscribed.",
            Q_FUNC_INFO, sensor->type().toStdString().c_str());
        return;
    }

    auto ohosSensorType = tryMapQtToOhosSensorType(sensor->type());
    if (!ohosSensorType.has_value()) {
        qOhosPrintfError(
            "%s: Cannot map Qt sensor type: %s, to OHOS Sensor_Type",
            Q_FUNC_INFO, sensor->type().toStdString().c_str());
        return;
    }

    auto sensorSubscriptionHandle = QOhosJsThreadGateway::eval(
        [&](QOhosJsState &) -> std::shared_ptr<void> {
            auto sensorSubId = tryCreateSensorResource<::Sensor_SubscriptionId>(
                ::OH_Sensor_CreateSubscriptionId, ::OH_Sensor_DestroySubscriptionId);
            if (!sensorSubId) {
                qOhosPrintfError("%s: OH_Sensor_CreateSubscriptionId return nullptr", Q_FUNC_INFO);
                return nullptr;
            }

            std::int32_t idRetVal = ::OH_SensorSubscriptionId_SetType(sensorSubId.get(), ohosSensorType.value());
            if (idRetVal != ::SENSOR_SUCCESS) {
                qOhosPrintfError("%s: OH_Sensor_CreateSubscriptionId fail with error code: %d",
                    Q_FUNC_INFO, idRetVal);
                return nullptr;
            }

            auto sensorSubAttr = tryCreateSensorResource<::Sensor_SubscriptionAttribute>(
                ::OH_Sensor_CreateSubscriptionAttribute, ::OH_Sensor_DestroySubscriptionAttribute);
            if (!sensorSubAttr) {
                qOhosPrintfError("%s: OH_Sensor_CreateSubscriptionAttribute returned nullptr", Q_FUNC_INFO);
                return nullptr;
            }

            auto sensorSamplePeriod = std::chrono::duration<double>(1.0 / sensor->dataRate());
            std::int32_t sensorSubAttrRetVal = ::OH_SensorSubscriptionAttribute_SetSamplingInterval(
                sensorSubAttr.get(),
                std::chrono::duration_cast<std::chrono::nanoseconds>(sensorSamplePeriod).count());
            if (sensorSubAttrRetVal != ::SENSOR_SUCCESS) {
                qOhosPrintfError(
                    "%s: OH_SensorSubscriptionAttribute_SetSamplingInterval fail with error code: %d",
                    Q_FUNC_INFO, sensorSubAttrRetVal);
                return nullptr;
            }

            std::int32_t subscribeRetVal = ::OH_Sensor_Subscribe(
                sensorSubId.get(), sensorSubAttr.get(), m_jsScopeData->subscriber.get());
            if (subscribeRetVal != ::SENSOR_SUCCESS) {
                qOhosPrintfError("%s: OH_Sensor_Subscribe fail with error code: %d",
                    Q_FUNC_INFO, subscribeRetVal);
                return nullptr;
            }

            auto sensorSubscriptionHandle = std::shared_ptr<void>(
                sensorSubId.get(),
                [sensorSubId = std::move(sensorSubId),
                weakSubscriber = std::weak_ptr<::Sensor_Subscriber>(m_jsScopeData->subscriber)](void *) mutable {
                    auto subscriber = weakSubscriber.lock();
                    if (subscriber) {
                        std::int32_t unsubRetVal = ::OH_Sensor_Unsubscribe(sensorSubId.get(), subscriber.get());
                        if (unsubRetVal != ::SENSOR_SUCCESS) {
                            qOhosPrintfError(
                                "%s: OH_Sensor_Unsubscribe fail with error code: %d",
                                Q_FUNC_INFO, unsubRetVal);
                        }
                    }
                    sensorSubId.reset();
                });

            return QtOhos::makeProxyWithJsThreadDeleter(std::move(sensorSubscriptionHandle));
        });

    if (sensorSubscriptionHandle) {
        m_subscribedSensors.emplace(sensor, SensorSubscriptionHandle{sensorSubscriptionHandle, sensorDataConsumer});
    }
}

void OhosSensorsManager::unsubscribeSensor(QSensor *sensor)
{
    auto subscribedSensor = m_subscribedSensors.find(sensor);
    if (subscribedSensor == m_subscribedSensors.end()) {
        qOhosPrintfError(
            "%s: Sensor %s not subscribed. Cannot unsubscribe.",
            Q_FUNC_INFO, sensor->type().toStdString().c_str());
        return;
    }

    m_subscribedSensors.erase(subscribedSensor);
}

void OhosSensorsManager::sensorEventCallbackHandler(::Sensor_Event *event)
{
    if (event == nullptr) {
        qOhosPrintfInfo("%s: sensor event is null", Q_FUNC_INFO);
        return;
    }

    auto sensorType = tryGetSensorEventField<::Sensor_Type>(event, ::OH_SensorEvent_GetType);
    if (!sensorType.has_value()) {
        qOhosPrintfError("%s: Cannot obtain sensor type from event.", Q_FUNC_INFO);
        return;
    }

    auto timestamp = tryGetSensorEventField<std::int64_t>(event, ::OH_SensorEvent_GetTimestamp);
    if (!timestamp.has_value()) {
        qOhosPrintfError("%s: Cannot obtain timestamp from event.", Q_FUNC_INFO);
        return;
    }

    auto accuracy = tryGetSensorEventField<::Sensor_Accuracy>(event, ::OH_SensorEvent_GetAccuracy);
    if (!accuracy.has_value()) {
        qOhosPrintfError("%s: Cannot obtain sensor accuracy from event.", Q_FUNC_INFO);
        return;
    }

    auto data = tryGetSensorEventData(event);
    if (!data.has_value()) {
        qOhosPrintfError("%s: Cannot obtain sensor data from event.", Q_FUNC_INFO);
        return;
    }

    OhosSensorData sensorData{timestamp.value(), accuracy.value(), data.value()};

    QtOhos::invokeInQtThread(
        [sensorType, sensorData]() {
            auto sensorDataConsumer =
                OhosSensorsManager::instance()->tryGetSensorConsumerForGivenOhosSensorType(sensorType.value());
            if (sensorDataConsumer != nullptr) {
                sensorDataConsumer(sensorData);
            }
        });
}

QOhosConsumer<const OhosSensorData &>
OhosSensorsManager::tryGetSensorConsumerForGivenOhosSensorType(::Sensor_Type ohosSensorType)
{
    auto sensor = std::find_if(
        m_subscribedSensors.begin(),
        m_subscribedSensors.end(),
        [&](const auto &kv) {
            return kv.first->identifier() == QByteArray::number(ohosSensorType);
        });

    if (sensor == m_subscribedSensors.end()) {
        qOhosPrintfError(
            "%s: Sensor with identifier %d is not subscribed.",
            Q_FUNC_INFO, ohosSensorType);
        return nullptr;
    }

    return sensor->second.sensorDataConsumer;
}
