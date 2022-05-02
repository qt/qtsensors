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
******************************************************************************/

#include "androidpressure.h"

AndroidPressure::AndroidPressure(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QPressureReading>(type, sensor, parent)
{}


void AndroidPressure::dataReceived(const ASensorEvent &event)
{
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_pressure:
    auto pressurePa = qreal(event.pressure) * 100;
    if (sensor()->skipDuplicates() && qFuzzyCompare(pressurePa, m_reader.pressure()))
        return;
    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setPressure(pressurePa); //Android uses hPa, we use Pa
    newReadingAvailable();
}
