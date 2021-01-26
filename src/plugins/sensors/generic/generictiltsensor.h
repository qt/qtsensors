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

#ifndef GENERICTILTSENSOR_H
#define GENERICTILTSENSOR_H

#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qtiltsensor.h>
#include <QtSensors/qaccelerometer.h>

QT_BEGIN_NAMESPACE

class GenericTiltSensor : public QSensorBackend, public QAccelerometerFilter
{
    Q_OBJECT
public:

    static char const * const id;

    GenericTiltSensor(QSensor *sensor);

    void start() override;
    void stop() override;

    Q_INVOKABLE void calibrate();

    bool filter(QAccelerometerReading *reading) override;

    bool isFeatureSupported(QSensor::Feature feature) const override;

private:
    QTiltReading m_reading;
    QAccelerometer *accelerometer;
    qreal radAccuracy;
    qreal pitch;
    qreal roll;
    qreal calibratedPitch;
    qreal calibratedRoll;
    qreal xRotation;
    qreal yRotation;
};

QT_END_NAMESPACE

#endif

