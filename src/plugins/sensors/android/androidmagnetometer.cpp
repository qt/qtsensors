/****************************************************************************
**
** Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "androidmagnetometer.h"

AndroidMagnetometer::AndroidMagnetometer(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QMagnetometerReading>(type, sensor, parent)
{}

void AndroidMagnetometer::dataReceived(const ASensorEvent &event)
{
    const auto &mag = event.magnetic;
    qreal accuracy = mag.status == ASENSOR_STATUS_NO_CONTACT ? 0 : mag.status / 3.0;
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_magnetic_field:
    // Android uses micro-Tesla, Qt uses Tesla
    qreal x = qreal(mag.x) / 1e6;
    qreal y = qreal(mag.y) / 1e6;
    qreal z = qreal(mag.z) / 1e6;
    if (sensor()->skipDuplicates() && qFuzzyCompare(accuracy, m_reader.calibrationLevel()) &&
            qFuzzyCompare(x, m_reader.x()) &&
            qFuzzyCompare(y, m_reader.y()) &&
            qFuzzyCompare(z, m_reader.z())) {
        return;
    }
    m_reader.setCalibrationLevel(accuracy);
    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setX(x);
    m_reader.setY(y);
    m_reader.setZ(z);
    newReadingAvailable();
}
