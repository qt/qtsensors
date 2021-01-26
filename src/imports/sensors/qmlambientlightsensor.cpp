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

#include "qmlambientlightsensor.h"
#include <QtSensors/QAmbientLightSensor>

/*!
    \qmltype AmbientLightSensor
    \instantiates QmlAmbientLightSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The AmbientLightSensor element repors on ambient lighting conditions.

    The AmbientLightSensor element repors on ambient lighting conditions.

    This element wraps the QAmbientLightSensor class. Please see the documentation for
    QAmbientLightSensor for details.

    \sa AmbientLightReading
*/

QmlAmbientLightSensor::QmlAmbientLightSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QAmbientLightSensor(this))
{
}

QmlAmbientLightSensor::~QmlAmbientLightSensor()
{
}

QmlSensorReading *QmlAmbientLightSensor::createReading() const
{
    return new QmlAmbientLightSensorReading(m_sensor);
}

QSensor *QmlAmbientLightSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype AmbientLightReading
    \instantiates QmlAmbientLightSensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The AmbientLightReading element holds the most AmbientLightSensor reading.

    The AmbientLightReading element holds the most AmbientLightSensor reading.

    This element wraps the QAmbientLightReading class. Please see the documentation for
    QAmbientLightReading for details.

    This element cannot be directly created.
*/

QmlAmbientLightSensorReading::QmlAmbientLightSensorReading(QAmbientLightSensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
{
}

QmlAmbientLightSensorReading::~QmlAmbientLightSensorReading()
{
}

/*!
    \qmlproperty LightLevel AmbientLightReading::lightLevel
    This property holds the ambient light level.

    Please see QAmbientLightReading::lightLevel for information about this property.

    Note that LightLevel constants are exposed through the AmbientLightReading class.
    \code
        AmbientLightSensor {
            onReadingChanged: {
                if (reading.lightLevel == AmbientLightReading.Dark)
                    // do something
            }
        }
    \endcode
*/

QAmbientLightReading::LightLevel QmlAmbientLightSensorReading::lightLevel() const
{
    return m_lightLevel;
}

QSensorReading *QmlAmbientLightSensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlAmbientLightSensorReading::readingUpdate()
{
    QAmbientLightReading::LightLevel ll = m_sensor->reading()->lightLevel();
    if (m_lightLevel != ll) {
        m_lightLevel = ll;
        Q_EMIT lightLevelChanged();
    }
}
