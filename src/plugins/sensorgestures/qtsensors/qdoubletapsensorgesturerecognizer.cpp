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
