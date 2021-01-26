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

#include "sensorfworientationsensor.h"

#include <datatypes/posedata.h>

char const * const SensorfwOrientationSensor::id("sensorfw.orientationsensor");

SensorfwOrientationSensor::SensorfwOrientationSensor(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QOrientationReading>(&m_reading);
    sensor->setDataRate(10);//set a default rate
}


void SensorfwOrientationSensor::start()
{
    if (reinitIsNeeded)
        init();
    if (m_sensorInterface) {
        Unsigned data(((OrientationSensorChannelInterface*)m_sensorInterface)->orientation());
        m_reading.setOrientation(SensorfwOrientationSensor::getOrientation(data.x()));
        m_reading.setTimestamp(data.UnsignedData().timestamp_);
        newReadingAvailable();
    }
    SensorfwSensorBase::start();
}


void SensorfwOrientationSensor::slotDataAvailable(const Unsigned& data)
{
    m_reading.setOrientation(SensorfwOrientationSensor::getOrientation(data.x()));
    m_reading.setTimestamp(data.UnsignedData().timestamp_);
    newReadingAvailable();
}

bool SensorfwOrientationSensor::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    return QObject::connect(m_sensorInterface, SIGNAL(orientationChanged(Unsigned)),
                            this, SLOT(slotDataAvailable(Unsigned)));
}

QString SensorfwOrientationSensor::sensorName() const
{
    return "orientationsensor";
}

QOrientationReading::Orientation SensorfwOrientationSensor::getOrientation(int orientation)
{
    switch (orientation) {
    case PoseData::BottomDown: return QOrientationReading::TopUp;
    case PoseData::BottomUp:   return QOrientationReading::TopDown;
    case PoseData::LeftUp:     return QOrientationReading::LeftUp;
    case PoseData::RightUp:    return QOrientationReading::RightUp;
    case PoseData::FaceUp:     return QOrientationReading::FaceUp;
    case PoseData::FaceDown:   return QOrientationReading::FaceDown;
    }
    return QOrientationReading::Undefined;
}

void SensorfwOrientationSensor::init()
{
    m_initDone = false;
    initSensor<OrientationSensorChannelInterface>(m_initDone);
}
