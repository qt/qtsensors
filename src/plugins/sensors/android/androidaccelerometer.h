/****************************************************************************
**
** Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
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
******************************************************************************/

#ifndef ANDROIDACCELEROMETER_H
#define ANDROIDACCELEROMETER_H

#include <qaccelerometer.h>

#include "sensoreventqueue.h"

class AndroidAccelerometer : public SensorEventQueue<QAccelerometerReading>
{
    Q_OBJECT
public:
    enum AccelerationModes {
        Accelerometer = 1,
        Gravity = 2,
        LinearAcceleration = 4,
        AllModes = (Accelerometer | Gravity | LinearAcceleration)
    };
public:
    AndroidAccelerometer(int accelerationModes, QSensor *sensor, QObject *parent = nullptr);
    // QSensorBackend interface
    bool isFeatureSupported(QSensor::Feature feature) const override;

protected:
    // SensorEventQueue interface
    void dataReceived(const ASensorEvent &event) override;

private:
    void applyAccelerationMode(QAccelerometer::AccelerationMode accelerationMode);

private:
    int m_accelerationModes;

};

#endif // ANDROIDACCELEROMETER_H
