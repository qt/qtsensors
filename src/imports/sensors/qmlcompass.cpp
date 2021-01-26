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

#include "qmlcompass.h"
#include <QtSensors/QCompass>

/*!
    \qmltype Compass
    \instantiates QmlCompass
    \ingroup qml-sensors_type
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits Sensor
    \brief The Compass element reports on heading using magnetic north as a reference.

    The Compass element reports on heading using magnetic north as a reference.

    This element wraps the QCompass class. Please see the documentation for
    QCompass for details.

    \sa CompassReading
*/

QmlCompass::QmlCompass(QObject *parent)
    : QmlSensor(parent)
    , m_sensor(new QCompass(this))
{
}

QmlCompass::~QmlCompass()
{
}

QmlSensorReading *QmlCompass::createReading() const
{
    return new QmlCompassReading(m_sensor);
}

QSensor *QmlCompass::sensor() const
{
    return m_sensor;
}

/*!
    \qmltype CompassReading
    \instantiates QmlCompassReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtSensors
    \since QtSensors 5.0
    \inherits SensorReading
    \brief The CompassReading element holds the most recent Compass reading.

    The CompassReading element holds the most recent Compass reading.

    This element wraps the QCompassReading class. Please see the documentation for
    QCompassReading for details.

    This element cannot be directly created.
*/

QmlCompassReading::QmlCompassReading(QCompass *sensor)
    : QmlSensorReading(sensor)
    , m_sensor(sensor)
{
}

QmlCompassReading::~QmlCompassReading()
{
}

/*!
    \qmlproperty qreal CompassReading::azimuth
    This property holds the azimuth of the device.

    Please see QCompassReading::azimuth for information about this property.
*/

qreal QmlCompassReading::azimuth() const
{
    return m_azimuth;
}

/*!
    \qmlproperty qreal CompassReading::calibrationLevel
    This property holds the calibration level of the reading.

    Please see QCompassReading::calibrationLevel for information about this property.
*/

qreal QmlCompassReading::calibrationLevel() const
{
    return m_calibrationLevel;
}

QSensorReading *QmlCompassReading::reading() const
{
    return m_sensor->reading();
}

void QmlCompassReading::readingUpdate()
{
    qreal azm = m_sensor->reading()->azimuth();
    if (m_azimuth != azm) {
        m_azimuth = azm;
        Q_EMIT azimuthChanged();
    }
    qreal calLevel = m_sensor->reading()->calibrationLevel();
    if (m_calibrationLevel != calLevel) {
        m_calibrationLevel = calLevel;
        Q_EMIT calibrationLevelChanged();
    }
}
