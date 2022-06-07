// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QDebug>

#include "qtsensorgesturesensorhandler.h"

QtSensorGestureSensorHandler::QtSensorGestureSensorHandler(QObject *parent) :
    QObject(parent),
    accel(0), orientation(0), proximity(0), irProx(0),tapSensor(0)
{
}

QtSensorGestureSensorHandler* QtSensorGestureSensorHandler::instance()
{
    static QtSensorGestureSensorHandler *instance = 0;
    if (!instance) {
        instance = new QtSensorGestureSensorHandler;
    }
    return instance;
}

void QtSensorGestureSensorHandler::accelChanged()
{
    Q_EMIT accelReadingChanged(accel->reading());
}

void QtSensorGestureSensorHandler::orientationChanged()
{
    Q_EMIT orientationReadingChanged(orientation->reading());
}

void QtSensorGestureSensorHandler::proximityChanged()
{
    Q_EMIT proximityReadingChanged(proximity->reading());
}

void QtSensorGestureSensorHandler::irProximityChanged()
{
    Q_EMIT irProximityReadingChanged(irProx->reading());
}

void QtSensorGestureSensorHandler::doubletap()
{
    Q_EMIT dTabReadingChanged(tapSensor->reading());
}

bool QtSensorGestureSensorHandler::startSensor(SensorGestureSensors sensor)
{
    bool ok = true;
    switch (sensor) {
    case Accel:
        //accel
        if (accel == 0x0) {
            accel = new QAccelerometer(this);
            ok = accel->connectToBackend();
            accel->setDataRate(100);
            qoutputrangelist outputranges = accel->outputRanges();

            if (outputranges.count() > 0)
                accelRange = (int)(outputranges.at(0).maximum);//39
            else
                accelRange = 39; //this should never happen
            connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
        }
        if (ok && !accel->isActive())
            accel->start();
        break;
    case Orientation:
        //orientation
        if (orientation == 0x0) {
            orientation = new QOrientationSensor(this);
            ok = orientation->connectToBackend();
            orientation->setDataRate(50);
            connect(orientation,SIGNAL(readingChanged()),this,SLOT(orientationChanged()));
        }
        if (ok && !orientation->isActive())
            orientation->start();
        break;
    case Proximity:
        //proximity
        if (proximity == 0x0) {
            proximity = new QProximitySensor(this);
            ok = proximity->connectToBackend();
            connect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
        }
        if (ok && !proximity->isActive())
            proximity->start();
        break;
    case IrProximity:
        //irproximity
        if (irProx == 0x0) {
            irProx = new QIRProximitySensor(this);
            irProx->setDataRate(50);
            ok = irProx->connectToBackend();
            connect(irProx,SIGNAL(readingChanged()),this,SLOT(irProximityChanged()));
        }
        if (ok && !irProx->isActive())
            irProx->start();
        break;
    case Tap:
        //dtap
        if (tapSensor == 0x0) {
            tapSensor = new QTapSensor(this);
            ok = tapSensor->connectToBackend();
            connect(tapSensor,SIGNAL(readingChanged()),this,SLOT(doubletap()));
        }
        if (ok && !tapSensor->isActive())
            tapSensor->start();
        break;
    };
    int val = usedSensorsMap.value(sensor);
    usedSensorsMap.insert(sensor,++val);

    return ok;
}

void QtSensorGestureSensorHandler::stopSensor(SensorGestureSensors sensor)
{
    //  qDebug() << __FUNCTION__ << sensor;
    if (usedSensorsMap.value(sensor) == 0)
        return;
    int val = usedSensorsMap.value(sensor);
    usedSensorsMap.insert(sensor,--val);
    switch (sensor) {
    case Accel:
        //accel
        if (usedSensorsMap.value(sensor) == 0) {
            accel->stop();
        }
        break;
    case Orientation:
        if (usedSensorsMap.value(sensor) == 0) {
            orientation->stop();
        }
        //orientation
        break;
    case Proximity:
        if (usedSensorsMap.value(sensor) == 0) {
            proximity->stop();
        }
        //proximity
        break;
    case IrProximity:
        if (usedSensorsMap.value(sensor) == 0) {
            irProx->stop();
        }
        //irproximity
        break;
    case Tap:
        if (usedSensorsMap.value(sensor) == 0) {
            tapSensor->stop();
        }
        //dtap
        break;
    };
}
