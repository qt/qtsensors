/****************************************************************************
**
** Copyright (C) 2016 BlackBerry Limited. All rights reserved.
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
#include "qmldistancesensor.h"
#include <QDistanceSensor>

/*!
    \qmltype DistanceSensor
    \instantiates QmlDistanceSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.4
    \inherits Sensor
    \brief The DistanceSensor element reports the distance in cm from an object to the device.

    The DistanceSensor element reports the distance in cm from an object to the device.

    This element wraps the QDistanceSensor class. Please see the documentation for
    QDistanceSensor for details.

    \sa DistanceReading
*/

QmlDistanceSensor::QmlDistanceSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QDistanceSensor(this))
{
}

QmlDistanceSensor::~QmlDistanceSensor()
{
}

QmlSensorReading *QmlDistanceSensor::createReading() const
{
    return new QmlDistanceReading(m_sensor);
}

QSensor *QmlDistanceSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype DistanceReading
    \instantiates QmlDistanceReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.4
    \inherits SensorReading
    \brief The DistanceReading element holds the most recent DistanceSensor reading.

    The DistanceReading element holds the most recent DistanceSensor reading.

    This element wraps the QDistanceReading class. Please see the documentation for
    QDistanceReading for details.

    This element cannot be directly created.
*/

QmlDistanceReading::QmlDistanceReading(QDistanceSensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
    , m_distance(0.0)
{
}

QmlDistanceReading::~QmlDistanceReading()
{
}

/*!
    \qmlproperty qreal DistanceReading::distance
    This property holds the distance measurement

    Please see QDistanceReading::distance for information about this property.
*/

qreal QmlDistanceReading::distance() const
{
    return m_distance;
}

QSensorReading *QmlDistanceReading::reading() const
{
    return m_sensor->reading();
}

void QmlDistanceReading::readingUpdate()
{
    qreal distance = m_sensor->reading()->distance();
    if (m_distance != distance) {
        m_distance = distance;
        Q_EMIT distanceChanged();
    }
}
