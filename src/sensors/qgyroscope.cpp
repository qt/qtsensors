/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgyroscope.h"
#include "qgyroscope_p.h"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING(QGyroscopeReading)

/*!
    \class QGyroscopeReading
    \ingroup sensors_reading
    \inmodule QtSensors

    \brief The QGyroscopeReading class represents one reading from the
           gyroscope sensor.

    \section2 QGyroscopeReading Units

    The reading contains 3 values, measured in degrees per second that define
    the movement of the device around the x, y and z axes. Unlike QRotationReading,
    the values represent the current angular velocity rather than a fixed rotation.
    The measurements are in degrees per second.

    \image sensors-coordinates3.jpg
*/

/*!
    \property QGyroscopeReading::x
    \brief the angular velocity around the x axis.

    Measured as degrees per second.
    \sa {QGyroscopeReading Units}
*/

qreal QGyroscopeReading::x() const
{
    return d->x;
}

/*!
    Sets the angular velocity around the x axis to \a x.
*/
void QGyroscopeReading::setX(qreal x)
{
    d->x = x;
}

/*!
    \property QGyroscopeReading::y
    \brief the angular velocity around the y axis.

    Measured as degrees per second.
    \sa {QGyroscopeReading Units}
*/

qreal QGyroscopeReading::y() const
{
    return d->y;
}

/*!
    Sets the angular velocity around the y axis to \a y.
*/
void QGyroscopeReading::setY(qreal y)
{
    d->y = y;
}

/*!
    \property QGyroscopeReading::z
    \brief the angular velocity around the z axis.

    Measured as degrees per second.
    \sa {QGyroscopeReading Units}
*/

qreal QGyroscopeReading::z() const
{
    return d->z;
}

/*!
    Sets the angular velocity around the z axis to \a z.
*/
void QGyroscopeReading::setZ(qreal z)
{
    d->z = z;
}

// =====================================================================

/*!
    \class QGyroscopeFilter
    \ingroup sensors_filter
    \inmodule QtSensors

    \brief The QGyroscopeFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to QGyroscopeReading
    instead of QSensorReading.
*/

/*!
    \fn QGyroscopeFilter::filter(QGyroscopeReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

char const * const QGyroscope::type("QGyroscope");

/*!
    \class QGyroscope
    \ingroup sensors_type
    \inmodule QtSensors

    \brief The QGyroscope class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a QGyroscopeReading instead of a QSensorReading.

    For details about how the sensor works, see \l QGyroscopeReading.

    \sa QGyroscopeReading
*/

/*!
    \fn QGyroscope::QGyroscope(QObject *parent)

    Construct the sensor as a child of \a parent.
*/

/*!
    \fn QGyroscope::~QGyroscope()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*!
    \fn QGyroscope::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

#include "moc_qgyroscope.cpp"
QT_END_NAMESPACE

