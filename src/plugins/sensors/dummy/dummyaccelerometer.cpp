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

#include "dummyaccelerometer.h"
#include <QDebug>
#include <QtGlobal>

char const * const dummyaccelerometer::id("dummy.accelerometer");

dummyaccelerometer::dummyaccelerometer(QSensor *sensor)
    : dummycommon(sensor)
{
    setReading<QAccelerometerReading>(&m_reading);
    addDataRate(100, 100); // 100Hz
}

void dummyaccelerometer::poll()
{
    m_reading.setTimestamp(getTimestamp());
    // Your average desktop computer doesn't move :)
    m_reading.setX(0);
    m_reading.setY(9.8); // facing the user, gravity goes here
    m_reading.setZ(0);

    newReadingAvailable();
}

