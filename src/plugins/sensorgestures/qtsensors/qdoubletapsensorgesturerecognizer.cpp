// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtSensors/QTapSensor>
#include "qdoubletapsensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

QDoubleTapSensorGestureRecognizer::QDoubleTapSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent)
  , active(0)
{
}

QDoubleTapSensorGestureRecognizer::~QDoubleTapSensorGestureRecognizer()
{
}

void QDoubleTapSensorGestureRecognizer::create()
{
}


QString QDoubleTapSensorGestureRecognizer::id() const
{
    return QString("QtSensors.doubletap");
}

bool QDoubleTapSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Tap)) {
        active = true;
        connect(QtSensorGestureSensorHandler::instance(),SIGNAL(dTabReadingChanged(QTapReading*)),
                this,SLOT(tapChanged(QTapReading*)));
    } else {
        active = false;
    }
    return active;
}

bool QDoubleTapSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Tap);
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(dTabReadingChanged(QTapReading*)),
            this,SLOT(tapChanged(QTapReading*)));
    active = false;
    return active;
}

bool QDoubleTapSensorGestureRecognizer::isActive()
{
    return active;
}

void QDoubleTapSensorGestureRecognizer::tapChanged(QTapReading *reading)
{
    if (reading->isDoubleTap()) {
        Q_EMIT doubletap();
        Q_EMIT detected("doubletap");
    }
}


QT_END_NAMESPACE
