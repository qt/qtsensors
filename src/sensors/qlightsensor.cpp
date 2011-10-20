/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "qlightsensor.h"
#include "qlightsensor_p.h"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING(QLightReading)

/*!
    \class QLightReading
    \ingroup sensors_reading


    \brief The QLightReading class represents one reading from the
           light sensor.

    \section2 QLightReading Units
    The light sensor returns the intensity of the light in lux.
*/

/*!
    \property QLightReading::lux
    \brief the light level.

    Measured as lux.
    \sa {QLightReading Units}
*/

qreal QLightReading::lux() const
{
    return d->lux;
}

/*!
    Sets the light level to \a lux.
*/
void QLightReading::setLux(qreal lux)
{
    d->lux = lux;
}

// =====================================================================

/*!
    \class QLightFilter
    \ingroup sensors_filter

    \brief The QLightFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to QLightReading
    instead of QSensorReading.
*/

/*!
    \fn QLightFilter::filter(QLightReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

char const * const QLightSensor::type("QLightSensor");

/*!
    \class QLightSensor
    \ingroup sensors_type

    \brief The QLightSensor class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a QLightReading instead of a QSensorReading.

    For details about how the sensor works, see \l QLightReading.

    \sa QLightReading
*/

/*!
    \fn QLightSensor::QLightSensor(QObject *parent)

    Construct the sensor as a child of \a parent.
*/

/*!
    \fn QLightSensor::~QLightSensor()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*!
    \fn QLightSensor::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

/*!
    \property QLightSensor::fieldOfView
    \brief a value indicating the field of view.

    This is an angle that represents the field of view of the sensor.
*/

#include "moc_qlightsensor.cpp"
QT_END_NAMESPACE

