// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GRUESENSOR_H
#define GRUESENSOR_H

#include <qsensor.h>

class GrueSensorReadingPrivate;

class GrueSensorReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(int chanceOfBeingEaten READ chanceOfBeingEaten WRITE setChanceOfBeingEaten)
    DECLARE_READING(GrueSensorReading)
public:
    int chanceOfBeingEaten() const;
    void setChanceOfBeingEaten(int chanceOfBeingEaten);
};

// begin generated code

class GrueFilter : public QSensorFilter
{
public:
    virtual bool filter(GrueSensorReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override { return filter(static_cast<GrueSensorReading*>(reading)); }
};

class GrueSensor : public QSensor
{
    Q_OBJECT
    Q_PROPERTY(GrueSensorReading* reading READ reading)
public:
    explicit GrueSensor(QObject *parent = 0) : QSensor(GrueSensor::sensorType, parent) {}
    virtual ~GrueSensor() {}
    GrueSensorReading *reading() const { return static_cast<GrueSensorReading*>(QSensor::reading()); }
    static char const * const sensorType;
};
// end generated code

#endif
