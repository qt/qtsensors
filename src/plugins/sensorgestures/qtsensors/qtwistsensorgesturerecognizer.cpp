/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qtwistsensorgesturerecognizer.h"

#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE

#define RADIANS_TO_DEGREES 57.2957795

QTwistSensorGestureRecognizer::QTwistSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , orientationReading(0)
    , accelRange(0)
    , lastRoll(0)
    , active(0)
    , pitch(0)
    , detecting(0)
    , lastDegree(0)
    , lastX(0)
    , lastY(0)
    , lastZ()
{
}

QTwistSensorGestureRecognizer::~QTwistSensorGestureRecognizer()
{
}

void QTwistSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(500);
}

QString QTwistSensorGestureRecognizer::id() const
{
    return QString("QtSensors.twist");
}

bool QTwistSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Accel)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
            accelRange = QtSensorGestureSensorHandler::instance()->accelRange;
            active = true;
            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading *)),
                    this,SLOT(orientationReadingChanged(QOrientationReading *)));

            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(accelReadingChanged(QAccelerometerReading *)),
                    this,SLOT(accelChanged(QAccelerometerReading *)));
        } else {
            QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Accel);
            active = false;
        }
    } else {
        active = false;
    }
    return active;
}

bool QTwistSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Accel);
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Orientation);
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading *)),
            this,SLOT(orientationReadingChanged(QOrientationReading *)));

    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(accelReadingChanged(QAccelerometerReading *)),
            this,SLOT(accelChanged(QAccelerometerReading *)));
    active = false;
    return active;
}

bool QTwistSensorGestureRecognizer::isActive()
{
    return active;
}

#define RESTING_VARIANCE 25
#define THRESHOLD_DEGREES 50

void QTwistSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

void QTwistSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    qreal x = reading->x();
    qreal y = reading->y();
    qreal z = reading->z();

    qreal diffX = lastX - x;
    qreal diffY = lastY - y;
    pitch = qAtan(y / qSqrt(x*x + z*z)) * RADIANS_TO_DEGREES;

    qreal degrees = qAtan(x / qSqrt(y*y + z*z)) * RADIANS_TO_DEGREES;

    if (orientationReading == 0)
        return;

    if (rollList.count() > 4) {
        if (detecting
                && isShake()) {
            // if shake-like:
            detecting = false;
            timer->stop();
            lastRoll = degrees;
        }
        if (detecting
                && qAbs(degrees) < RESTING_VARIANCE
                && qAbs(pitch) < RESTING_VARIANCE
                && (qAbs(lastRoll + degrees) > (degrees / 2))
                ) {
            if (lastRoll > 0 ) {
                Q_EMIT twistLeft();
                Q_EMIT detected("twistLeft");
            } else {
                Q_EMIT twistRight();
                Q_EMIT detected("twistRight");
            }
            // don't give two signals for same gestures
                detecting = false;
                timer->stop();
                lastRoll = degrees;
        }

        if (orientationReading->orientation() == QOrientationReading::FaceUp
                && !detecting && qAbs(degrees) > THRESHOLD_DEGREES
                && pitch < RESTING_VARIANCE) {

            detecting = true;
            timer->start();
            lastRoll = degrees;
            lastOrientation = orientationReading->orientation();
        }

        if (detecting && (orientationReading->orientation() == QOrientationReading::TopUp
                || orientationReading->orientation() == QOrientationReading::TopDown)) {

            detecting = false;
            timer->stop();
            lastRoll = degrees;
        }
    }

    if (negativeList.count() > 5)
        negativeList.removeLast();

    if ((((x < 0 && lastX > 0) || (x > 0 && lastX < 0)) && qAbs(diffX) > (accelRange * 0.5))
            || (((y < 0 && lastY > 0) || (y > 0 && lastY < 0)) && qAbs(diffY) > (accelRange * 0.5))) {
        negativeList.insert(0,true);
    } else {
        negativeList.insert(0,false);
    }

    if (rollList.count() > 5)
        rollList.removeLast();
    rollList.insert(0,degrees);
    lastDegree = degrees;
    lastX = x; lastY = y;
}

void QTwistSensorGestureRecognizer::timeout()
{
    detecting = false;
    lastRoll = 0;
    lastOrientation = QOrientationReading::Undefined;
}

bool QTwistSensorGestureRecognizer::isShake()
{
    for (int i = 0; i < negativeList.count() - 1; i++) {
        if (negativeList.at(i)) {
            return true;
        }
    }
    return false;
}



QT_END_NAMESPACE
