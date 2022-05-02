/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#include "iosmotionmanager.h"
#include "iosgyroscope.h"

#import <CoreMotion/CoreMotion.h>
#import <QtCore/qmath.h>

char const * const IOSGyroscope::id("ios.gyroscope");

QT_BEGIN_NAMESPACE

int IOSGyroscope::s_startCount = 0;

IOSGyroscope::IOSGyroscope(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_motionManager([QIOSMotionManager sharedManager])
    , m_timer(0)
{
    setReading<QGyroscopeReading>(&m_reading);
    addDataRate(1, 100); // 100Hz is max it seems
    addOutputRange(-360, 360, 0.01);
}

void IOSGyroscope::start()
{
    if (m_timer != 0)
        return;

    int hz = sensor()->dataRate();
    m_timer = startTimer(1000 / (hz == 0 ? 60 : hz));
    if (++s_startCount == 1)
        [m_motionManager startGyroUpdates];
}

void IOSGyroscope::stop()
{
    if (m_timer == 0)
        return;

    killTimer(m_timer);
    m_timer = 0;
    if (--s_startCount == 0)
        [m_motionManager stopGyroUpdates];
}

void IOSGyroscope::timerEvent(QTimerEvent *)
{
    // Convert NSTimeInterval to microseconds and radians to degrees:
    CMGyroData *data = m_motionManager.gyroData;
    CMRotationRate rate = data.rotationRate;
    // skip update if NaN
    if (rate.x != rate.x || rate.y != rate.y || rate.z != rate.z)
        return;
    m_reading.setTimestamp(quint64(data.timestamp * 1e6));
    m_reading.setX(qRadiansToDegrees(qreal(rate.x)));
    m_reading.setY(qRadiansToDegrees(qreal(rate.y)));
    m_reading.setZ(qRadiansToDegrees(qreal(rate.z)));
    newReadingAvailable();
}

QT_END_NAMESPACE
