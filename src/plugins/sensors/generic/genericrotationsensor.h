/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef GENERICROTATIONSENSOR_H
#define GENERICROTATIONSENSOR_H

#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qrotationsensor.h>
#include <QtSensors/qaccelerometer.h>
#include <QtSensors/qmagnetometer.h>

class genericrotationsensor : public QSensorBackend, public QSensorFilter
{
public:
    static char const * const id;

    genericrotationsensor(QSensor *sensor);

    void start() override;
    void stop() override;

    bool filter(QSensorReading *reading) override;

private:
    QRotationReading m_reading;
    QAccelerometer *accelerometer;
};

#endif

