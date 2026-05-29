// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSSENSORUTILS_H
#define OHOSSENSORUTILS_H

#include <QtCore/private/qohoscommon_p.h>
#include <QtCore/private/qohoslogger_p.h>
#include <memory>
#include <optional>
#include <sensors/oh_sensor_type.h>

namespace ohossensorutils_h_details {

template<typename SensorObjectPtr, typename T>
std::optional<T> tryGetSensorDataField(
    SensorObjectPtr sensorObjectPtr,
    std::int32_t (*sensorObjDataGetter)(SensorObjectPtr, T *))
{
    T value{};
    std::int32_t ret = sensorObjDataGetter(sensorObjectPtr, &value);
    if (ret != ::SENSOR_SUCCESS) {
        qOhosPrintfError("%s: sensor getter failed, code=%d", Q_FUNC_INFO, ret);
        return std::nullopt;
    }
    return value;
}

}

template<typename T>
std::optional<T> tryGetSensorInfoField(
    ::Sensor_Info *sensorInfo,
    std::int32_t (*sensorInfoDataGetter)(::Sensor_Info *, T *));

template<typename T>
std::optional<T> tryGetSensorEventField(
    ::Sensor_Event *sensorEvent,
    std::int32_t (*sensorEventDataGetter)(::Sensor_Event *, T *));

template<typename T>
std::shared_ptr<T> tryCreateSensorResource(
    T *(*sensorResourceCreator)(),
    std::int32_t (*sensorResourceDeleter)(T *));

const char *tryMapOhosToQtSensorType(::Sensor_Type sensorType);
std::optional<::Sensor_Type> tryMapQtToOhosSensorType(const char *qtType);

template<typename T>
std::optional<T> tryGetSensorInfoField(
    ::Sensor_Info *sensorInfo,
    std::int32_t (*sensorInfoDataGetter)(::Sensor_Info *, T *))
{
    return ohossensorutils_h_details::tryGetSensorDataField<::Sensor_Info *, T>(sensorInfo, sensorInfoDataGetter);
}

template<typename T>
std::optional<T> tryGetSensorEventField(
    ::Sensor_Event *sensorEvent,
    std::int32_t (*sensorEventDataGetter)(::Sensor_Event *, T *))
{
    return ohossensorutils_h_details::tryGetSensorDataField<::Sensor_Event *, T>(sensorEvent, sensorEventDataGetter);
}

template<typename T>
std::shared_ptr<T> tryCreateSensorResource(
    T *(*sensorResourceCreator)(),
    std::int32_t (*sensorResourceDeleter)(T *))
{
    T *resourcePtr = sensorResourceCreator();
    return (resourcePtr != nullptr)
        ? std::shared_ptr<T>(
            resourcePtr,
            [sensorResourceDeleter](T *ptr) {
                auto ret = sensorResourceDeleter(ptr);
                if (ret != ::SENSOR_SUCCESS) {
                    qOhosPrintfError(
                        "%s: Failed to delete resource, err code=%d", Q_FUNC_INFO, ret);
                }
            })
        : nullptr;
}

#endif
