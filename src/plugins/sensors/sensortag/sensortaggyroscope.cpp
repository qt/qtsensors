/****************************************************************************
**
** Copyright (C) 2017 Lorn Potter
** Copyright (C) 2021 The Qt Company Ltd.
** Copyright (C) 2016 Canonical, Ltd.
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

#include "sensortaggyroscope.h"

char const * const SensorTagGyroscope::id("sensortag.gyroscope");
const float SensorTagGyroscope::MILLI = 0.001;

SensorTagGyroscope::SensorTagGyroscope(QSensor *sensor)
    : SensorTagBase(sensor)
{
    init();
    setDescription(QLatin1String("angular velocities around x, y, and z axis in degrees per second"));
    setReading<QGyroscopeReading>(&m_reading);
    sensor->setDataRate(50);//set a default rate
}

void SensorTagGyroscope::slotDataAvailable(const QGyroscopeReading& data)
{
    m_reading.setX(data.x());
    m_reading.setY(data.y());
    m_reading.setZ(data.z());
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}

void SensorTagGyroscope::init()
{
    m_initDone = false;
}

void SensorTagGyroscope::start()
{
    QObject::connect(this, &SensorTagBase::gyroDataAvailable,
                     this, &SensorTagGyroscope::slotDataAvailable);
    d_ptr->enableService(TI_SENSORTAG_GYROSCOPE_SERVICE);
}


void SensorTagGyroscope::stop()
{
    QObject::disconnect(this, &SensorTagBase::gyroDataAvailable,
                        this, &SensorTagGyroscope::slotDataAvailable);
    d_ptr->disableService(TI_SENSORTAG_GYROSCOPE_SERVICE);
}

