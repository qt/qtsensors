/****************************************************************************
**
** Copyright (C) 2016 Canonical Ltd
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

#include "qmlhumiditysensor.h"
#include <QtSensors/QHumiditySensor>

/*!
    \qmltype HumiditySensor
    \instantiates QmlHumiditySensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.9
    \inherits Sensor
    \brief The HumiditySensor element reports on humidity.

    The HumiditySensor element reports on humidity.

    This element wraps the QHumiditySensor class. Please see the documentation for
    QHumiditySensor for details.

    \sa HumidityReading
*/

QmlHumiditySensor::QmlHumiditySensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QHumiditySensor(this))
{
}

QmlHumiditySensor::~QmlHumiditySensor()
{
}

QmlSensorReading *QmlHumiditySensor::createReading() const
{
    return new QmlHumidityReading(m_sensor);
}

QSensor *QmlHumiditySensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype HumidityReading
    \instantiates QmlHumidityReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.9
    \inherits SensorReading
    \brief The HumidityReading element holds the most recent HumiditySensor reading.

    The HumidityReading element holds the most recent HumiditySensor reading.

    This element wraps the QHumidityReading class. Please see the documentation for
    QHumidityReading for details.

    This element cannot be directly created.
*/

QmlHumidityReading::QmlHumidityReading(QHumiditySensor *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
    , m_relativeHumidity(0)
    , m_absoluteHumidity(0)
{
}

QmlHumidityReading::~QmlHumidityReading()
{
}

/*!
    \qmlproperty qreal HumidityReading::relativeHumidity
    This property holds the relative humidity as a percentage.

    Please see QHumidityReading::relativeHumidity for information about this property.
*/

qreal QmlHumidityReading::relativeHumidity() const
{
    return m_relativeHumidity;
}

/*!
    \qmlproperty qreal HumidityReading::absoluteHumidity
    This property holds the absolute humidity in grams per cubic meter (g/m3).

    Please see QHumidityReading::absoluteHumidity for information about this property.
*/

qreal QmlHumidityReading::absoluteHumidity() const
{
    return m_absoluteHumidity;
}

QSensorReading *QmlHumidityReading::reading() const
{
    return m_sensor->reading();
}

void QmlHumidityReading::readingUpdate()
{
    qreal humidity = m_sensor->reading()->relativeHumidity();
    if (m_relativeHumidity != humidity) {
        m_relativeHumidity = humidity;
        Q_EMIT relativeHumidityChanged();
    }
    qreal abs = m_sensor->reading()->absoluteHumidity();
    if (m_absoluteHumidity != abs) {
        m_absoluteHumidity = abs;
        Q_EMIT absoluteHumidityChanged();
    }
}
