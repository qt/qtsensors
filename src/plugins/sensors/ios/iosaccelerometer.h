/****************************************************************************
**
** Copyright (C) 2016 Lorn Potter
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

#ifndef IOSACCELEROMETER_H
#define IOSACCELEROMETER_H

#include <qsensorbackend.h>
#include <qaccelerometer.h>

@class CMMotionManager;

QT_BEGIN_NAMESPACE

class IOSAccelerometer : public QSensorBackend
{
public:
    static char const * const id;

    explicit IOSAccelerometer(QSensor *sensor);
    void timerEvent(QTimerEvent *) override;

    void start() override;
    void stop() override;

private:
    CMMotionManager *m_motionManager;
    QAccelerometerReading m_reading;
    int m_timer;

    static int s_startCount;
};
QT_END_NAMESPACE

#endif // IOSACCELEROMETER_H

