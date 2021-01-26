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

#include "qmlirproximitysensor.h"
#include <QtSensors/QIRProximitySensor>

/*!
    \qmltype IRProximitySensor
    \instantiates QmlIRProximitySensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The IRProximitySensor element reports on infra-red reflectance values.

    This element wraps the QIRProximitySensor class. Please see the documentation for
    QIRProximitySensor for details.

    \sa IRProximityReading
*/

QmlIRProximitySensor::QmlIRProximitySensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QIRProximitySensor(this))
{
}

QmlIRProximitySensor::~QmlIRProximitySensor()
{
}

QmlSensorReading *QmlIRProximitySensor::createReading() const
{
    return new QmlIRProximitySensorReading(m_sensor);
}

QSensor *QmlIRProximitySensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype IRProximityReading
    \instantiates QmlIRProximitySensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The IRProximityReading element holds the most recent IR proximity reading.

    The IRProximityReading element holds the most recent IR proximity reading.

    This element wraps the QIRProximityReading class. Please see the documentation for
    QIRProximityReading for details.

    This element cannot be directly created.
*/

QmlIRProximitySensorReading::QmlIRProximitySensorReading(QIRProximitySensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
{
}

QmlIRProximitySensorReading::~QmlIRProximitySensorReading()
{
}

/*!
    \qmlproperty qreal IRProximityReading::reflectance
    This property holds the reflectance value.

    Please see QIRProximityReading::reflectance for information about this property.
*/

qreal QmlIRProximitySensorReading::reflectance() const
{
    return m_reflectance;
}

QSensorReading *QmlIRProximitySensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlIRProximitySensorReading::readingUpdate()
{
    qreal fl = m_sensor->reading()->reflectance();
    if (m_reflectance != fl) {
        m_reflectance = fl;
        Q_EMIT reflectanceChanged();
    }
}
