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

#include <QObject>
#include <qaccelerometer.h>
#include <qmagnetometer.h>
#include <qorientationsensor.h>

class MyObject : public QObject
{
    void create();
};

void MyObject::create()
{
//! [Creating a sensor]
// On the heap (deleted when this object is deleted)
QAccelerometer *sensor = new QAccelerometer(this);

// On the stack (deleted when the current scope ends)
QOrientationSensor orient_sensor;
//! [Creating a sensor]

    Q_UNUSED(sensor);
    Q_UNUSED(orient_sensor);

{
//! [2]
QMagnetometer *magnetometer = new QMagnetometer(this);
//! [2]
Q_UNUSED(magnetometer);
}

{
//! [3]
QSensor *magnetometer = new QSensor(QMagnetometer::sensorType, this);
//! [3]
Q_UNUSED(magnetometer);
}

}

