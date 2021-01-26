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

#include "sensortaglightsensor.h"

char const * const SensorTagLightSensor::id("sensortag.lightsensor");

SensorTagLightSensor::SensorTagLightSensor(QSensor *sensor)
    : SensorTagBase(sensor)
{
    init();
    setReading<QLightReading>(&m_reading);
    sensor->setDataRate(10);//set a default rate
}

void SensorTagLightSensor::slotDataAvailable(qreal data)
{
    m_reading.setLux(data);
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}

void SensorTagLightSensor::init()
{
    m_initDone = false;
}

void SensorTagLightSensor::start()
{
    QObject::connect(this, &SensorTagBase::luxDataAvailable,
                     this, &SensorTagLightSensor::slotDataAvailable);
    d_ptr->enableService(TI_SENSORTAG_LIGHT_SERVICE);
}

void SensorTagLightSensor::stop()
{
    QObject::disconnect(this, &SensorTagBase::luxDataAvailable,
                        this, &SensorTagLightSensor::slotDataAvailable);
    d_ptr->disableService(TI_SENSORTAG_LIGHT_SERVICE);
}
