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
#include "sensortagmagnetometer.h"

char const * const SensorTagMagnetometer::id("sensortag.magnetometer");
const float SensorTagMagnetometer::NANO = 0.000000001;

SensorTagMagnetometer::SensorTagMagnetometer(QSensor *sensor)
    : SensorTagBase(sensor)
{
    init();
    setDescription(QLatin1String("magnetic flux density in teslas (T)"));
    setReading<QMagnetometerReading>(&m_reading);
}

void SensorTagMagnetometer::start()
{
    QObject::connect(this, &SensorTagBase::magDataAvailable,
                     this, &SensorTagMagnetometer::slotDataAvailable);
    d_ptr->enableService(TI_SENSORTAG_MAGNETOMETER_SERVICE);
}

void SensorTagMagnetometer::stop()
{
    QObject::disconnect(this, &SensorTagBase::magDataAvailable,
                        this, &SensorTagMagnetometer::slotDataAvailable);
    d_ptr->disableService(TI_SENSORTAG_MAGNETOMETER_SERVICE);
}

void SensorTagMagnetometer::slotDataAvailable(const QMagnetometerReading &data)
{
    m_reading.setX(data.x());
    m_reading.setY(data.y());
    m_reading.setZ(data.z());
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}

void SensorTagMagnetometer::init()
{
    m_initDone = false;
}
