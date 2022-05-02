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

#include "sensorfwirproximitysensor.h"
#define RM680_PS "/dev/bh1770glc_ps"

char const * const SensorfwIrProximitySensor::id("sensorfw.irproximitysensor");

SensorfwIrProximitySensor::SensorfwIrProximitySensor(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QIRProximityReading>(&m_reading);
    setDescription(QLatin1String("reflectance as percentage (%) of maximum"));
    addOutputRange(0, 100, 1);
    addDataRate(10,10);
    rangeMax = QFile::exists(RM680_PS)?255:1023;
    sensor->setDataRate(10);//set a default rate
}

void SensorfwIrProximitySensor::slotDataAvailable(const Proximity& proximity)
{
    m_reading.setReflectance((float)proximity.reflectance()*100 / rangeMax);
    m_reading.setTimestamp(proximity.UnsignedData().timestamp_);
    newReadingAvailable();
}


bool SensorfwIrProximitySensor::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    return QObject::connect(m_sensorInterface, SIGNAL(reflectanceDataAvailable(Proximity)),
                            this, SLOT(slotDataAvailable(Proximity)));
}


QString SensorfwIrProximitySensor::sensorName() const
{
    return "proximitysensor";
}


void SensorfwIrProximitySensor::init()
{
    m_initDone = false;
    initSensor<ProximitySensorChannelInterface>(m_initDone);
}

void SensorfwIrProximitySensor::start()
{
    if (reinitIsNeeded)
        init();
    SensorfwSensorBase::start();
}
