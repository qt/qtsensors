// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "gruesensorimpl.h"
#include <QDebug>
#include <QTimer>

char const * const gruesensorimpl::id("grue.gruesensor");

gruesensorimpl::gruesensorimpl(QSensor *sensor)
    : QSensorBackend(sensor)
    , lightLevel(QAmbientLightReading::Undefined)
{
    // We need a light sensor
    lightSensor = new QAmbientLightSensor(this);
    connect(lightSensor, SIGNAL(readingChanged()), this, SLOT(lightChanged()));
    lightSensor->connectToBackend();

    // We need a timer
    darkTimer = new QTimer(this);
    darkTimer->setInterval(1000);
    connect(darkTimer, SIGNAL(timeout()), this, SLOT(increaseChance()));

    // We use this as our timestamp source
    timer.start();

//! [setReading]
    // Register our reading instance
    setReading<GrueSensorReading>(&m_reading);
//! [setReading]

//! [metadata]
    // Supply metadata
    // We can run as fast as the light sensor does
    setDataRates(lightSensor);
    // Only one output range, 0 to 1 in .1 increments
    addOutputRange(0, 1, 0.1);
    setDescription(QLatin1String("Grue Sensor"));
//! [metadata]
}

void gruesensorimpl::start()
{
//! [start]
    lightSensor->setDataRate(sensor()->dataRate());
    lightSensor->start();
    // If the light sensor doesn't work we don't work either
    if (!lightSensor->isActive())
        sensorStopped();
    if (lightSensor->isBusy())
        sensorBusy();
//! [start]
}

void gruesensorimpl::stop()
{
    lightSensor->stop();
}

void gruesensorimpl::lightChanged()
{
    if (lightLevel == lightSensor->reading()->lightLevel())
        return;

    lightLevel = lightSensor->reading()->lightLevel();

    int chance = 0;
    darkTimer->stop();

    switch (lightSensor->reading()->lightLevel()) {
    case QAmbientLightReading::Dark:
        // It is dark. You are likely to be eaten by a grue.
        chance = 10;
        darkTimer->start();
        break;
    default:
        break;
    }

    // Only send an update if the value has changed.
    if (chance != m_reading.chanceOfBeingEaten() || m_reading.timestamp() == 0) {
        m_reading.setTimestamp(timer.elapsed());
        m_reading.setChanceOfBeingEaten(chance);
        newReadingAvailable();
    }
}

void gruesensorimpl::increaseChance()
{
    // The longer you stay in the dark, the higher your chance of being eaten
    int chance = m_reading.chanceOfBeingEaten() + 10;

    m_reading.setTimestamp(timer.elapsed());
    m_reading.setChanceOfBeingEaten(chance);

    newReadingAvailable();

    // No point in using the timer anymore if we've hit 100... you can't get more
    // likely to be eaten than 100%
    if (chance >= 100)
        darkTimer->stop();
}

