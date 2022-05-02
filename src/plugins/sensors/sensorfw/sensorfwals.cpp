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


#include "sensorfwals.h"

char const * const Sensorfwals::id("sensorfw.als");

Sensorfwals::Sensorfwals(QSensor *sensor)
    : SensorfwSensorBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QAmbientLightReading>(&m_reading);
    // metadata
    setDescription(QLatin1String("ambient light intensity given as 5 pre-defined levels"));
    addOutputRange(0, 5, 1);
    addDataRate(10,10);
    sensor->setDataRate(10);//set a default rate
}

void Sensorfwals::start()
{
    if (reinitIsNeeded)
        init();
    if (m_sensorInterface) {
        Unsigned data(((ALSSensorChannelInterface*)m_sensorInterface)->lux());
        m_reading.setLightLevel(getLightLevel(data.x()));
        m_reading.setTimestamp(data.UnsignedData().timestamp_);
        newReadingAvailable();
    }
    SensorfwSensorBase::start();
}


void Sensorfwals::slotDataAvailable(const Unsigned& data)
{
    QAmbientLightReading::LightLevel level = getLightLevel(data.UnsignedData().value_);
    if (level != m_reading.lightLevel()) {
        m_reading.setLightLevel(level);
        m_reading.setTimestamp(data.UnsignedData().timestamp_);
        newReadingAvailable();
    }
}

bool Sensorfwals::doConnect()
{
    Q_ASSERT(m_sensorInterface);
    return QObject::connect(m_sensorInterface, SIGNAL(ALSChanged(Unsigned)),
                            this, SLOT(slotDataAvailable(Unsigned)));
}


QString Sensorfwals::sensorName() const
{
    return "alssensor";
}


QAmbientLightReading::LightLevel Sensorfwals::getLightLevel(int lux)
{
    // Convert from integer to fixed levels
    if (lux < 0) {
        return QAmbientLightReading::Undefined;
    } else if (lux < 10) {
        return QAmbientLightReading::Dark;
    } else if (lux < 80) {
        return QAmbientLightReading::Twilight;
    } else if (lux < 400) {
        return QAmbientLightReading::Light;
    } else if (lux < 2500) {
        return QAmbientLightReading::Bright;
    } else {
        return QAmbientLightReading::Sunny;
    }

}
void Sensorfwals::init()
{
    m_initDone = false;
    initSensor<ALSSensorChannelInterface>(m_initDone);
}
