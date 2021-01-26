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

#include "androidlight.h"

AndroidLight::AndroidLight(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QLightReading>(type, sensor, parent)
{}

void AndroidLight::dataReceived(const ASensorEvent &event)
{
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_light:
    if (sensor()->skipDuplicates() && qFuzzyCompare(m_reader.lux(), qreal(event.light)))
        return;

    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setLux(qreal(event.light));
    newReadingAvailable();
}
