// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtSensors/QSensor>

#include "qturnoversensorgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

// turnover and put down i.e. facedown

QTurnoverSensorGestureRecognizer::QTurnoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    isClose(0)
  , isFaceDown(0), active(0)
{
}

QTurnoverSensorGestureRecognizer::~QTurnoverSensorGestureRecognizer()
{
}

void QTurnoverSensorGestureRecognizer::create()
{
}

bool QTurnoverSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Proximity)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
            active = true;
            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(proximityReadingChanged(QProximityReading*)),
                    this,SLOT(proximityChanged(QProximityReading*)));

            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading*)),
                    this,SLOT(orientationReadingChanged(QOrientationReading*)));
        } else {
            QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Proximity);
            active = false;
        }
    } else {
        active = false;
    }
    return active;
}

bool QTurnoverSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Proximity);
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Orientation);

    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(proximityReadingChanged(QProximityReading*)),
            this,SLOT(proximityChanged(QProximityReading*)));
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading*)),
            this,SLOT(orientationReadingChanged(QOrientationReading*)));

    active = false;

    return active;
}

bool QTurnoverSensorGestureRecognizer::isActive()
{
    return active;
}

QString QTurnoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.turnover");
}

void QTurnoverSensorGestureRecognizer::proximityChanged(QProximityReading *reading)
{
    isClose = reading->close();
    if (isClose)
        isRecognized();
}

void QTurnoverSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    switch (reading->orientation()) {
       case  QOrientationReading::FaceDown:
    {
        isFaceDown = true;
        isRecognized();
    }
        break;
    default:
        isFaceDown = false;
        break;
    };
}

void QTurnoverSensorGestureRecognizer::isRecognized()
{
    if (isClose && isFaceDown) {
        Q_EMIT turnover();
        Q_EMIT detected("turnover");
    }
}
QT_END_NAMESPACE

