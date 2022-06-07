// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <qsensor.h>

void start()
{
//! [Starting a sensor]
// start the sensor
QSensor sensor("QAccelerometer");
sensor.start();

// later
QSensorReading *reading = sensor.reading();
qreal x = reading->property("x").value<qreal>();
qreal y = reading->value(1).value<qreal>();
//! [Starting a sensor]

    Q_UNUSED(x);
    Q_UNUSED(y);
}
