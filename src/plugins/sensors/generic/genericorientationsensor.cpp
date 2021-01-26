/****************************************************************************
**
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

#include "genericorientationsensor.h"
#include <QDebug>

char const * const genericorientationsensor::id("generic.orientation");

genericorientationsensor::genericorientationsensor(QSensor *sensor)
    : QSensorBackend(sensor)
{
    accelerometer = new QAccelerometer(this);
    accelerometer->addFilter(this);
    accelerometer->connectToBackend();

    setReading<QOrientationReading>(&m_reading);
    setDataRates(accelerometer);
}

void genericorientationsensor::start()
{
    accelerometer->setDataRate(sensor()->dataRate());
    accelerometer->setAlwaysOn(sensor()->isAlwaysOn());
    accelerometer->start();
    if (!accelerometer->isActive())
        sensorStopped();
    if (accelerometer->isBusy())
        sensorBusy();
}

void genericorientationsensor::stop()
{
    accelerometer->stop();
}

bool genericorientationsensor::filter(QAccelerometerReading *reading)
{
    QOrientationReading::Orientation o = m_reading.orientation();

    if (reading->y() > 7.35)
        o = QOrientationReading::TopUp;
    else if (reading->y() < -7.35)
        o = QOrientationReading::TopDown;
    else if (reading->x() > 7.35)
        o = QOrientationReading::RightUp;
    else if (reading->x() < -7.35)
        o = QOrientationReading::LeftUp;
    else if (reading->z() > 7.35)
        o = QOrientationReading::FaceUp;
    else if (reading->z() < -7.35)
        o = QOrientationReading::FaceDown;

    if (o != m_reading.orientation() || m_reading.timestamp() == 0) {
        m_reading.setTimestamp(reading->timestamp());
        m_reading.setOrientation(o);
        newReadingAvailable();
    }

    return false;
}

