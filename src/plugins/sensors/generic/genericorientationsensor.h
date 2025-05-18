// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef GENERICORIENTATIONSENSOR_H
#define GENERICORIENTATIONSENSOR_H

#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qorientationsensor.h>
#include <QtSensors/qaccelerometer.h>

class genericorientationsensor : public QSensorBackend, public QAccelerometerFilter
{
public:
    static char const * const id;

    genericorientationsensor(QSensor *sensor);

    void start() override;
    void stop() override;

    bool filter(QAccelerometerReading *reading) override;

private:
    QOrientationReading m_reading;
    QAccelerometer *accelerometer;
};

#endif

