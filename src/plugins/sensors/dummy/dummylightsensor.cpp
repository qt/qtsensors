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

#include "dummylightsensor.h"
#include <QDebug>
#include <QRandomGenerator>

char const * const dummylightsensor::id("dummy.lightsensor");

dummylightsensor::dummylightsensor(QSensor *sensor)
    : dummycommon(sensor)
{
    setReading<QAmbientLightReading>(&m_reading);
    addDataRate(100,100);
}

void dummylightsensor::poll()
{
    m_reading.setTimestamp(getTimestamp());
    if (QRandomGenerator::global()->bounded(100) == 0)
        m_reading.setLightLevel(QAmbientLightReading::Dark);
    else
        m_reading.setLightLevel(QAmbientLightReading::Light);

    newReadingAvailable();
}

