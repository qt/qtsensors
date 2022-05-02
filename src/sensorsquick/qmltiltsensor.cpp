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

#include "qmltiltsensor_p.h"
#include <QtSensors/qtiltsensor.h>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

/*!
    \qmltype TiltSensor
    \instantiates QmlTiltSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The TiltSensor element reports tilt events
           along the X and Y axes.

    The TiltSensor element reports tilt events along the X and Y axes.

    This element wraps the QTiltSensor class. Please see the documentation for
    QTiltSensor for details.

    \sa TiltReading
*/

QmlTiltSensor::QmlTiltSensor(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QTiltSensor(this))
{
}

QmlTiltSensor::~QmlTiltSensor()
{
}

QmlSensorReading *QmlTiltSensor::createReading() const
{
    return new QmlTiltSensorReading(m_sensor);
}

QSensor *QmlTiltSensor::sensor() const
{
    return m_sensor;
}

/*!
    \qmlmethod TiltSensor::calibrate()
    Calibrate the tilt sensor.

    Please see QTiltSensor::calibrate() for information about this property.
*/
void QmlTiltSensor::calibrate()
{
    m_sensor->calibrate();
}

/*!
    \qmltype TiltReading
    \instantiates QmlTiltSensorReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The TiltReading element holds the most recent TiltSensor reading.

    The TiltReading element holds the most recent TiltSensor reading.

    This element wraps the QTiltReading class. Please see the documentation for
    QTiltReading for details.

    This element cannot be directly created.
*/

QmlTiltSensorReading::QmlTiltSensorReading(QTiltSensor *sensor)
    : m_sensor(sensor)
{
}

QmlTiltSensorReading::~QmlTiltSensorReading()
{
}

/*!
    \qmlproperty qreal TiltReading::yRotation
    This property holds the amount of tilt on the Y axis.

    Please see QTiltReading::yRotation for information about this property.
*/

qreal QmlTiltSensorReading::yRotation() const
{
    return m_yRotation;
}

QBindable<qreal> QmlTiltSensorReading::bindableYRotation() const
{
    return &m_yRotation;
}

/*!
    \qmlproperty qreal TiltReading::xRotation
    This property holds the amount of tilt on the X axis.

    Please see QTiltReading::xRotation for information about this property.
*/

qreal QmlTiltSensorReading::xRotation() const
{
    return m_xRotation;
}

QBindable<qreal> QmlTiltSensorReading::bindableXRotation() const
{
    return &m_xRotation;
}

QSensorReading *QmlTiltSensorReading::reading() const
{
    return m_sensor->reading();
}

void QmlTiltSensorReading::readingUpdate()
{
    m_yRotation = m_sensor->reading()->yRotation();
    m_xRotation = m_sensor->reading()->xRotation();
}
