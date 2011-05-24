/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
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

#include "qcompass.h"
#include "qcompass_p.h"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING(QCompassReading)

/*!
    \class QCompassReading
    \ingroup sensors_reading
    \inmodule QtSensors
    \since 1.0

    \brief The QCompassReading class represents one reading from a
           compass.

    \section2 QCompassReading Units
    The compass returns the azimuth of the device as degrees from
    magnetic north in a clockwise direction based on the top of the UI.
    There is also a value to indicate the calibration status of the device.
    If the device is not calibrated the azimuth may not be accurate.

    Digital compasses are susceptible to magnetic interference and may need
    calibration after being placed near anything that emits a magnetic force.
    Accuracy of the compass can be affected by any ferrous materials that are nearby.

    The calibration status of the device is measured as a number from 0 to 1.
    A value of 1 is the highest level that the device can support and 0 is
    the worst.
    \sa {http://wiki.forum.nokia.com/index.php/CS001671_-_Calibrating_the_magnetometer_sensor}{CS001671 - Calibrating the magnetometer sensor}
*/

/*!
    \property QCompassReading::azimuth
    \brief the azimuth of the device.

    Measured in degrees from magnetic north in a clockwise direction based
    the top of the UI.
    \sa {QCompassReading Units}
*/

qreal QCompassReading::azimuth() const
{
    return d->azimuth;
}

/*!
    Sets the \a azimuth of the device.

    \sa {QCompassReading Units}
*/
void QCompassReading::setAzimuth(qreal azimuth)
{
    d->azimuth = azimuth;
}

/*!
    \property QCompassReading::calibrationLevel
    \brief the calibration level of the reading.

    Measured as a value from 0 to 1 with higher values being better.
    \sa {QCompassReading Units}, {http://wiki.forum.nokia.com/index.php/CS001671_-_Calibrating_the_magnetometer_sensor}{CS001671 - Calibrating the magnetometer sensor}
*/

qreal QCompassReading::calibrationLevel() const
{
    return d->calibrationLevel;
}

/*!
    Sets the calibration level of the reading to \a calibrationLevel.
*/
void QCompassReading::setCalibrationLevel(qreal calibrationLevel)
{
    d->calibrationLevel = calibrationLevel;
}

// =====================================================================

/*!
    \class QCompassFilter
    \ingroup sensors_filter
    \inmodule QtSensors

    \brief The QCompassFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to QCompassReading
    instead of QSensorReading.
*/

/*!
    \fn QCompassFilter::filter(QCompassReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

char const * const QCompass::type("QCompass");

/*!
    \class QCompass
    \ingroup sensors_type
    \inmodule QtSensors

    \brief The QCompass class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a QCompassReading instead of a QSensorReading.

    For details about how the sensor works, see \l QCompassReading.

    \sa QCompassReading
*/

/*!
    \fn QCompass::QCompass(QObject *parent)

    Construct the sensor as a child of \a parent.
*/

/*!
    \fn QCompass::~QCompass()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*!
    \fn QCompass::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

#include "moc_qcompass.cpp"
QT_END_NAMESPACE

