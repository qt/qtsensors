// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qohoslogger_p.h>
#include <ohosrotationsensorbackend.h>

OhosRotationSensorBackend::OhosRotationSensorBackend(QSensor *sensor)
    : OhosSensorBackendBase(sensor)
{
}

void OhosRotationSensorBackend::processSensorData(const OhosSensorData &sensorData)
{
    constexpr std::size_t expectedDataSize = 3;
    if (sensorData.data.size() != expectedDataSize) {
        qOhosPrintfError(
            "%s: sensorData data has size: %lu. Expected: %lu",
            Q_FUNC_INFO, sensorData.data.size(), expectedDataSize);
        return;
    }
    auto z = qreal(sensorData.data[0]);
    auto x = qreal(sensorData.data[1]);
    auto y = qreal(sensorData.data[2]);
    if (sensor()->skipDuplicates()
        && qFuzzyCompare(m_reading.x(), x)
        && qFuzzyCompare(m_reading.y(), y)
        && qFuzzyCompare(m_reading.z(), z)) {
        return;
    }
    m_reading.setFromEuler(x, y, z);
    m_reading.setTimestamp(sensorData.timestamp);
    newReadingAvailable();
}
