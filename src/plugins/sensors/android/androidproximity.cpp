/****************************************************************************
**
** Copyright (C) 2016 BogDan Vatra <bogdan@kde.org>
** Copyright (C) 2021 The Qt Company Ltd.
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

#include "androidproximity.h"

AndroidProximity::AndroidProximity(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QProximityReading>(type, sensor, parent)
{
    m_maximumRange = m_sensorManager->getMaximumRange(m_sensor);

    // if we can't get the range, we arbitrarily define anything closer than 10 cm as "close"
    if (m_maximumRange <= 0)
        m_maximumRange = 10.0;
}


void AndroidProximity::dataReceived(const ASensorEvent &event)
{
    // https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_proximity:
    bool close = qreal(event.distance) < m_maximumRange;
    if (sensor()->skipDuplicates() && close == m_reader.close())
        return;
    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setClose(close);
    newReadingAvailable();
}
