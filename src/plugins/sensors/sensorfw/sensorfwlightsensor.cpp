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

#include "sensorfwlightsensor.h"

char const * const SensorfwLightSensor::id("sensorfw.lightsensor");

SensorfwLightSensor::SensorfwLightSensor(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QLightReading>(&m_reading);
    sensor->setDataRate(10);//set a default rate
}

void SensorfwLightSensor::slotDataAvailable(const Unsigned& data)
{
    m_reading.setLux(data.UnsignedData().value_);
    m_reading.setTimestamp(data.UnsignedData().timestamp_);
    newReadingAvailable();
}

bool SensorfwLightSensor::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    return QObject::connect(m_sensorInterface, SIGNAL(ALSChanged(Unsigned)),
                            this, SLOT(slotDataAvailable(Unsigned)));
}


QString SensorfwLightSensor::sensorName() const
{
    return "alssensor";
}
void SensorfwLightSensor::init()
{
    m_initDone = false;
    initSensor<ALSSensorChannelInterface>(m_initDone);
}

void SensorfwLightSensor::start()
{
    if (reinitIsNeeded)
        init();
    SensorfwSensorBase::start();
}
