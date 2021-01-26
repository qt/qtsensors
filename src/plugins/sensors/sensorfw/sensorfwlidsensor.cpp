/****************************************************************************
**
** Copyright (C) 2016 Canonical, Ltd
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

#include "sensorfwlidsensor.h"

char const * const SensorfwLidSensor::id("sensorfw.lidsensor");

SensorfwLidSensor::SensorfwLidSensor(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QLidReading>(&m_reading);
    sensor->setDataRate(10);//set a default rate
}

void SensorfwLidSensor::slotDataAvailable(const LidData& data)
{
    switch (data.type_) {
    case data.BackLid:
        m_reading.setBackLidClosed(data.value_);
        break;
    case data.FrontLid:
        m_reading.setFrontLidClosed(data.value_);
        break;
    };

    m_reading.setTimestamp(data.timestamp_);
    newReadingAvailable();
}

bool SensorfwLidSensor::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    return QObject::connect(m_sensorInterface, SIGNAL(lidChanged(LidData)),
                            this, SLOT(slotDataAvailable(LidData)));
}

QString SensorfwLidSensor::sensorName() const
{
    return "lidsensor";
}

void SensorfwLidSensor::init()
{
    m_initDone = false;
    initSensor<LidSensorChannelInterface>(m_initDone);
}

void SensorfwLidSensor::start()
{
    if (reinitIsNeeded)
        init();
    SensorfwSensorBase::start();
}
