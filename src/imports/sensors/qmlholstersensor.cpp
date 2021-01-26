/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
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
#include "qmlholstersensor.h"
#include <QtSensors/QHolsterSensor>

/*!
    \qmltype HolsterSensor
    \instantiates QmlHolsterSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits Sensor
    \brief The HolsterSensor element reports on whether a device is holstered.

    The HolsterSensor element reports on whether a device is holstered.

    This element wraps the QHolsterSensor class. Please see the documentation for
    QHolsterSensor for details.

    \sa HolsterReading
*/

QmlHolsterSensor::QmlHolsterSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QHolsterSensor(this))
{
}

QmlHolsterSensor::~QmlHolsterSensor()
{
}

QmlSensorReading *QmlHolsterSensor::createReading() const
{
    return new QmlHolsterReading(m_sensor);
}

QSensor *QmlHolsterSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype HolsterReading
    \instantiates QmlHolsterReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits SensorReading
    \brief The HolsterReading element holds the most recent HolsterSensor reading.

    The HolsterReading element holds the most recent HolsterSensor reading.

    This element wraps the QHolsterReading class. Please see the documentation for
    QHolsterReading for details.

    This element cannot be directly created.
*/

QmlHolsterReading::QmlHolsterReading(QHolsterSensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
    , m_holstered(false)
{
}

QmlHolsterReading::~QmlHolsterReading()
{
}

/*!
    \qmlproperty qreal HolsterReading::holstered
    This property holds whether the device is holstered.

    Please see QHolsterReading::holstered for information about this property.
*/

bool QmlHolsterReading::holstered() const
{
    return m_holstered;
}

QSensorReading *QmlHolsterReading::reading() const
{
    return m_sensor->reading();
}

void QmlHolsterReading::readingUpdate()
{
    const bool holstered = m_sensor->reading()->holstered();
    if (m_holstered != holstered) {
        m_holstered = holstered;
        Q_EMIT holsteredChanged();
    }
}
