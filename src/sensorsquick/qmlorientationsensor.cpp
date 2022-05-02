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

#include "qmlorientationsensor_p.h"
#include <QtSensors/QOrientationSensor>

/*!
    \qmltype OrientationSensor
    \instantiates QmlOrientationSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The OrientationSensor element reports device orientation.

    The OrientationSensor element reports device orientation.

    This element wraps the QOrientationSensor class. Please see the documentation for
    QOrientationSensor for details.

    \sa OrientationReading
*/

QmlOrientationSensor::QmlOrientationSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QOrientationSensor(this))
{
}

QmlOrientationSensor::~QmlOrientationSensor()
{
}

QmlSensorReading *QmlOrientationSensor::createReading() const
{
    return new QmlOrientationSensorReading(m_sensor);
}

QSensor *QmlOrientationSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype OrientationReading
    \instantiates QmlOrientationSensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The OrientationReading element holds the most recent OrientationSensor reading.

    The OrientationReading element holds the most recent OrientationSensor reading.

    This element wraps the QOrientationReading class. Please see the documentation for
    QOrientationReading for details.

    This element cannot be directly created.
*/

QmlOrientationSensorReading::QmlOrientationSensorReading(QOrientationSensor *sensor)
    : m_sensor(sensor)
{
}

QmlOrientationSensorReading::~QmlOrientationSensorReading()
{
}

/*!
    \qmlproperty Orientation OrientationReading::orientation
    This property holds the orientation of the device.

    Please see QOrientationReading::orientation for information about this property.

    Note that Orientation constants are exposed through the OrientationReading class.
    \code
        OrientationSensor {
            onReadingChanged: {
                if (reading.orientation == OrientationReading.TopUp)
                    // do something
            }
        }
    \endcode
*/

QOrientationReading::Orientation QmlOrientationSensorReading::orientation() const
{
    return m_orientation;
}

QBindable<QOrientationReading::Orientation> QmlOrientationSensorReading::bindableOrientation() const
{
    return &m_orientation;
}

QSensorReading *QmlOrientationSensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlOrientationSensorReading::readingUpdate()
{
    m_orientation = m_sensor->reading()->orientation();
}
