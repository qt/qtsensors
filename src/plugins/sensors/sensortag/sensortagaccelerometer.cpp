/****************************************************************************
**
** Copyright (C) 2017 Lorn Potter
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

#include "sensortagaccelerometer.h"
#include <QtSensors/qsensorbackend.h>

char const * const SensorTagAccelerometer::id("sensortag.accelerometer");

SensorTagAccelerometer::SensorTagAccelerometer(QSensor *sensor)
    : SensorTagBase(sensor)
{
    init();
    setDescription(QLatin1String("x, y, and z axes accelerations in m/s^2"));
    setReading<QAccelerometerReading>(&m_reading);
    sensor->setDataRate(50);//set a default rate
}

void SensorTagAccelerometer::slotDataAvailable(const QAccelerometerReading &data)
{
    m_reading.setX(data.x());
    m_reading.setY(data.y());
    m_reading.setZ(data.z());
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}

void SensorTagAccelerometer::init()
{
    m_initDone = false;
}

void SensorTagAccelerometer::start()
{
    QObject::connect(this, &SensorTagBase::accelDataAvailable,
                     this, &SensorTagAccelerometer::slotDataAvailable);
    d_ptr->enableService(TI_SENSORTAG_ACCELEROMETER_SERVICE);
}

void SensorTagAccelerometer::stop()
{
    QObject::disconnect(this, &SensorTagBase::accelDataAvailable,
                        this, &SensorTagAccelerometer::slotDataAvailable);
    d_ptr->disableService(TI_SENSORTAG_ACCELEROMETER_SERVICE);
}

