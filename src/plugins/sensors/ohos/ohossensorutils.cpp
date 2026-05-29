// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qohoscommon_p.h>
#include <QtSensors/qaccelerometer.h>
#include <QtSensors/qgyroscope.h>
#include <QtSensors/qlightsensor.h>
#include <QtSensors/qmagnetometer.h>
#include <QtSensors/qrotationsensor.h>
#include <algorithm>
#include <cstring>
#include <ohossensorutils.h>

namespace {

struct SensorTypeMapping
{
    ::Sensor_Type ohosType;
    const char *qtType;
};

const SensorTypeMapping sensorTypeTable[] = {
    {::SENSOR_TYPE_ACCELEROMETER, QAccelerometer::sensorType},
    {::SENSOR_TYPE_GYROSCOPE, QGyroscope::sensorType},
    {::SENSOR_TYPE_AMBIENT_LIGHT, QLightSensor::sensorType},
    {::SENSOR_TYPE_MAGNETIC_FIELD, QMagnetometer::sensorType},
    {::SENSOR_TYPE_ORIENTATION, QRotationSensor::sensorType},
};

}

const char *tryMapOhosToQtSensorType(::Sensor_Type sensorType)
{
    auto it = std::find_if(
        std::begin(sensorTypeTable),
        std::end(sensorTypeTable),
        [sensorType](const SensorTypeMapping &entry) {
            return entry.ohosType == sensorType;
        }
    );
    return (it != std::end(sensorTypeTable))
        ? it->qtType
        : nullptr;
}

std::optional<::Sensor_Type> tryMapQtToOhosSensorType(const char *qtType)
{
    auto it = std::find_if(
        std::begin(sensorTypeTable),
        std::end(sensorTypeTable),
        [qtType](const SensorTypeMapping &entry) {
            return std::strcmp(entry.qtType, qtType) == 0;
        }
    );
    return (it != std::end(sensorTypeTable))
        ? std::optional(it->ohosType)
        : std::nullopt;
}
