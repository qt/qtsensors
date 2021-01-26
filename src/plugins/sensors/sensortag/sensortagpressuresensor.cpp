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

#include "sensortagpressuresensor.h"
#include "sensortagbase.h"

char const * const SensorTagPressureSensor::id("sensortag.pressure");

SensorTagPressureSensor::SensorTagPressureSensor(QSensor *sensor)
    : SensorTagBase(sensor)
{
    setReading<QPressureReading>(&m_reading);
}

void SensorTagPressureSensor::pressureChanged(qreal value)
{
    m_reading.setPressure(value);
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}

void SensorTagPressureSensor::start()
{
    QObject::connect(this, &SensorTagBase::pressureDataAvailable,
                     this, &SensorTagPressureSensor::pressureChanged);
    d_ptr->enableService(TI_SENSORTAG_BAROMETER_SERVICE);
}

void SensorTagPressureSensor::stop()
{
    QObject::disconnect(this, &SensorTagBase::pressureDataAvailable,
                        this, &SensorTagPressureSensor::pressureChanged);
    d_ptr->disableService(TI_SENSORTAG_BAROMETER_SERVICE);
}

