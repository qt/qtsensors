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
#include "qmlaltimeter.h"
#include <QtSensors/QAltimeter>

/*!
    \qmltype Altimeter
    \instantiates QmlAltimeter
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits Sensor
    \brief The Altimeter element reports on altitude.

    The Altimeter element reports on altitude.

    This element wraps the QAltimeter class. Please see the documentation for
    QAltimeter for details.

    \sa AltimeterReading
*/

QmlAltimeter::QmlAltimeter(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QAltimeter(this))
{
}

QmlAltimeter::~QmlAltimeter()
{
}

QmlSensorReading *QmlAltimeter::createReading() const
{
    return new QmlAltimeterReading(m_sensor);
}

QSensor *QmlAltimeter::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype AltimeterReading
    \instantiates QmlAltimeterReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.1
    \inherits SensorReading
    \brief The AltimeterReading element holds the most recent Altimeter reading.

    The AltimeterReading element holds the most recent Altimeter reading.

    This element wraps the QAltimeterReading class. Please see the documentation for
    QAltimeterReading for details.

    This element cannot be directly created.
*/

QmlAltimeterReading::QmlAltimeterReading(QAltimeter *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
    , m_altitude(0)
{
}

QmlAltimeterReading::~QmlAltimeterReading()
{
}

/*!
    \qmlproperty qreal AltimeterReading::altitude
    This property holds the altitude of the device.

    Please see QAltimeterReading::altitude for information about this property.
*/

qreal QmlAltimeterReading::altitude() const
{
    return m_altitude;
}

QSensorReading *QmlAltimeterReading::reading() const
{
    return m_sensor->reading();
}

void QmlAltimeterReading::readingUpdate()
{
    qreal altitude = m_sensor->reading()->altitude();
    if (m_altitude != altitude) {
        m_altitude = altitude;
        Q_EMIT altitudeChanged();
    }
}
