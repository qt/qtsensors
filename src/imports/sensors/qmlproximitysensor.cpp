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

#include "qmlproximitysensor.h"
#include <QtSensors/QProximitySensor>

/*!
    \qmltype ProximitySensor
    \instantiates QmlProximitySensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The ProximitySensor element reports on object proximity.

    The ProximitySensor element reports on object proximity.

    This element wraps the QProximitySensor class. Please see the documentation for
    QProximitySensor for details.

    \sa ProximityReading
*/

QmlProximitySensor::QmlProximitySensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QProximitySensor(this))
{
}

QmlProximitySensor::~QmlProximitySensor()
{
}

QmlSensorReading *QmlProximitySensor::createReading() const
{
    return new QmlProximitySensorReading(m_sensor);
}

QSensor *QmlProximitySensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype ProximityReading
    \instantiates QmlProximitySensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The ProximityReading element holds the most recent ProximitySensor reading.

    The ProximityReading element holds the most recent ProximitySensor reading.

    This element wraps the QProximityReading class. Please see the documentation for
    QProximityReading for details.

    This element cannot be directly created.
*/

QmlProximitySensorReading::QmlProximitySensorReading(QProximitySensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
{
}

QmlProximitySensorReading::~QmlProximitySensorReading()
{
}

/*!
    \qmlproperty bool ProximityReading::near
    This property holds a value indicating if something is near.

    Please see QProximityReading::near for information about this property.
*/

bool QmlProximitySensorReading::near() const
{
    return m_near;
}

QSensorReading *QmlProximitySensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlProximitySensorReading::readingUpdate()
{
    bool pNear = m_sensor->reading()->close();
    if (m_near != pNear) {
        m_near = pNear;
        Q_EMIT nearChanged();
    }
}
