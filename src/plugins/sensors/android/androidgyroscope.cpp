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

#include "androidgyroscope.h"
#include <QtCore/qmath.h>

AndroidGyroscope::AndroidGyroscope(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QGyroscopeReading>(type, sensor, parent)
{}

void AndroidGyroscope::dataReceived(const ASensorEvent &event)
{
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_gyroscope:
    const auto &vec = event.vector;
    qreal x = qRadiansToDegrees(qreal(vec.x));
    qreal y = qRadiansToDegrees(qreal(vec.y));
    qreal z = qRadiansToDegrees(qreal(vec.z));
    if (sensor()->skipDuplicates() && qFuzzyCompare(m_reader.x(), x) &&
            qFuzzyCompare(m_reader.y(), y) &&
            qFuzzyCompare(m_reader.z(), z)) {
        return;
    }
    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setX(x);
    m_reader.setY(y);
    m_reader.setZ(z);
    newReadingAvailable();
}
