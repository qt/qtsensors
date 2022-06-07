// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qcoversensorgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

QCoverSensorGestureRecognizer::QCoverSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent),
      orientationReading(0),
      proximityReading(0),
      timer(0),
      active(0),
      detecting(0)
{
}

QCoverSensorGestureRecognizer::~QCoverSensorGestureRecognizer()
{
}

void QCoverSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(750);
}

QString QCoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.cover");
}

bool QCoverSensorGestureRecognizer::start()
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

bool QCoverSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Proximity);
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Orientation);

    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(proximityReadingChanged(QProximityReading*)),
               this,SLOT(proximityChanged(QProximityReading*)));
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading*)),
               this,SLOT(orientationReadingChanged(QOrientationReading*)));

    active = false;
    timer->stop();
    return active;
}

bool QCoverSensorGestureRecognizer::isActive()
{
    return active;
}

void QCoverSensorGestureRecognizer::proximityChanged(QProximityReading *reading)
{
    if (orientationReading == 0)
        return;

    proximityReading = reading->close();

    // look at case of face up->face down->face up.
    if (orientationReading->orientation() ==  QOrientationReading::FaceUp
            && proximityReading) {
        if (!timer->isActive()) {
            timer->start();
            detecting = true;
        }
    }
}

void QCoverSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

void QCoverSensorGestureRecognizer::timeout()
{
    if ((orientationReading->orientation() == QOrientationReading::FaceUp)
            && proximityReading) {
        Q_EMIT cover();
        Q_EMIT detected("cover");
        detecting = false;
    }
}

QT_END_NAMESPACE
