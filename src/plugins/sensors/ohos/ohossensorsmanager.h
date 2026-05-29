// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSSENSORSMANAGER_H
#define OHOSSENSORSMANAGER_H

#include <QtCore/private/qohoscommon_p.h>
#include <QtSensors/qsensor.h>
#include <memory>
#include <optional>
#include <sensors/oh_sensor.h>
#include <unordered_map>
#include <vector>

struct OhosSensorData
{
    std::int64_t timestamp;
    ::Sensor_Accuracy accuracy;
    std::vector<float> data;
};

struct OhosSensorCapabilities
{
    qreal resolution;
    int minDataRate;
    int maxDataRate;
};

class OhosSensorsManager
{
public:
    static OhosSensorsManager *instance();

    std::vector<::Sensor_Type> getAvailableSensorsTypes();
    std::optional<OhosSensorCapabilities> tryGetSensorCapabilities(QSensor *sensor);
    void subscribeSensor(QSensor *sensor, QOhosConsumer<const OhosSensorData &> sensorDataConsumer);
    void unsubscribeSensor(QSensor *sensor);

private:
    OhosSensorsManager();

    struct JsScopeData
    {
        std::shared_ptr<std::vector<::Sensor_Info *>> availableSensorsInfo;
        std::shared_ptr<::Sensor_Subscriber> subscriber;
    };

    struct SensorSubscriptionHandle
    {
        std::shared_ptr<void> sensorSubscriptionHandle;
        QOhosConsumer<const OhosSensorData &> sensorDataConsumer;
    };

    static void sensorEventCallbackHandler(::Sensor_Event *event);

    QOhosConsumer<const OhosSensorData &> tryGetSensorConsumerForGivenOhosSensorType(::Sensor_Type ohosSensorType);

    std::shared_ptr<JsScopeData> m_jsScopeData;
    std::unordered_map<QSensor *, SensorSubscriptionHandle> m_subscribedSensors;
};

#endif
