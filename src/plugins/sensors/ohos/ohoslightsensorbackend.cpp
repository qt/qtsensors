// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qohoslogger_p.h>
#include <ohoslightsensorbackend.h>

OhosLightSensorBackend::OhosLightSensorBackend(QSensor *sensor)
    : OhosSensorBackendBase(sensor, true)
{
}

void OhosLightSensorBackend::processSensorData(const OhosSensorData &sensorData)
{
    constexpr std::size_t expectedDataSize = 3;
    if (sensorData.data.size() != expectedDataSize) {
        qOhosPrintfError(
            "%s: sensorData data has size: %lu. Expected: %lu",
            Q_FUNC_INFO, sensorData.data.size(), expectedDataSize);
        return;
    }
    auto lux = qreal(sensorData.data[0]);
    if (sensor()->skipDuplicates() && qFuzzyCompare(m_reading.lux(), lux)) {
        return;
    }
    m_reading.setLux(lux);
    m_reading.setTimestamp(sensorData.timestamp);
    newReadingAvailable();
}
