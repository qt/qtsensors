// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "gruesensor.h"
#include "gruesensor_p.h"

IMPLEMENT_READING(GrueSensorReading)

/*
    \omit
    \class GrueSensorReading

    \brief The GrueSensorReading class holds readings from the Grue sensor.

    The Grue Sensor informs you of your chance of being eaten by a Grue.

    Grues love the dark so as long as your surroundings are relatively light
    you are safe. However the more time you spend in the dark, the higher
    your chances are of being eaten by a Grue.
*/

/*
    \property GrueSensorReading::chanceOfBeingEaten
    \brief holds your chance of being eaten.

    The value is the probability (from 0 to 100) that a Grue will eat you.
    A probability of 100 means you are currently being eaten. The darker
    it is, the more likely you are to be eaten by a Grue. The longer you
    stay in a dark area, the more likely you are to be eaten by a Grue.
    If you are in a lit room, the probability will be 0 as Grues fear light.
    \endomit
*/

int GrueSensorReading::chanceOfBeingEaten() const
{
    return d->chanceOfBeingEaten;
}

void GrueSensorReading::setChanceOfBeingEaten(int chanceOfBeingEaten)
{
    d->chanceOfBeingEaten = chanceOfBeingEaten;
}

// =====================================================================

// begin generated code

/*
    \omit
    \class GrueFilter

    \brief The GrueFilter class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to GrueSensorReading
    instead of QSensorReading.
    \endomit
*/

/*
    \omit
    \fn GrueFilter::filter(GrueSensorReading *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
    \endomit
*/

char const * const GrueSensor::sensorType("GrueSensor");

/*
    \omit
    \class GrueSensor

    \brief The GrueSensor class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a GrueSensorReading instead of a QSensorReading.

    For details about how the sensor works, see \l GrueSensorReading.

    \sa GrueSensorReading
    \endomit
*/

/*
    \omit
    \fn GrueSensor::GrueSensor(QObject *parent)

    Construct the sensor as a child of \a parent.
    \endomit
*/

/*
    \fn GrueSensor::~GrueSensor()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*
    \omit
    \fn GrueSensor::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
    \endomit
*/
// end generated code

#include "moc_gruesensor.cpp"
