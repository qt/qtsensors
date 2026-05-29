// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qohoslogger_p.h>
#include <ohosaccelerometerbackend.h>

OhosAccelerometerBackend::OhosAccelerometerBackend(QSensor *sensor)
    : OhosSensorBackendBase(sensor)
{
}

void OhosAccelerometerBackend::processSensorData(const OhosSensorData &sensorData)
{
    constexpr std::size_t expectedDataSize = 3;
    if (sensorData.data.size() != expectedDataSize) {
        qOhosPrintfError(
            "%s: sensorData data has size: %lu. Expected: %lu",
            Q_FUNC_INFO, sensorData.data.size(), expectedDataSize);
        return;
    }
    auto x = qreal(sensorData.data[0]);
    auto y = qreal(sensorData.data[1]);
    auto z = qreal(sensorData.data[2]);
    if (sensor()->skipDuplicates()
        && qFuzzyCompare(m_reading.x(), x)
        && qFuzzyCompare(m_reading.y(), y)
        && qFuzzyCompare(m_reading.z(), z)) {
        return;
    }
    m_reading.setX(x);
    m_reading.setY(y);
    m_reading.setZ(z);
    m_reading.setTimestamp(sensorData.timestamp);
    newReadingAvailable();
}
