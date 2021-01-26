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

#include "sensortagals.h"
#include "sensortagbase.h"
#include <QDebug>

char const * const SensorTagAls::id("sensortag.als");

SensorTagAls::SensorTagAls(QSensor *sensor)
    : SensorTagBase(sensor)
    , m_initDone(false)
{
    init();
    setReading<QAmbientLightReading>(&m_reading);
    setDescription(QLatin1String("ambient light intensity given as 5 pre-defined levels"));
}

void SensorTagAls::start()
{
    QObject::connect(this, &SensorTagBase::luxDataAvailable, this, &SensorTagAls::slotDataAvailable);
    d_ptr->enableService(TI_SENSORTAG_LIGHT_SERVICE);
}

void SensorTagAls::stop()
{
    QObject::disconnect(this, &SensorTagBase::luxDataAvailable, this, &SensorTagAls::slotDataAvailable);
    d_ptr->disableService(TI_SENSORTAG_LIGHT_SERVICE);
}

void SensorTagAls::slotDataAvailable(qreal data)
{
    QAmbientLightReading::LightLevel level = getLightLevel(data);
    if (level != m_reading.lightLevel()) {
        m_reading.setLightLevel(level);
        m_reading.setTimestamp(produceTimestamp());
        newReadingAvailable();
    }
}

QAmbientLightReading::LightLevel SensorTagAls::getLightLevel(int lux)
{
    if (lux < 0)
        return QAmbientLightReading::Undefined;
    if (lux < 10)
        return QAmbientLightReading::Dark;
    if (lux < 80)
        return QAmbientLightReading::Twilight;
    if (lux < 400)
        return QAmbientLightReading::Light;
    if (lux < 2500)
        return QAmbientLightReading::Bright;
    return QAmbientLightReading::Sunny;
}

void SensorTagAls::init()
{
    m_initDone = false;
}
