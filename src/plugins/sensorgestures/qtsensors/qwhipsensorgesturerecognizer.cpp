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


#include "qwhipsensorgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE

QWhipSensorGestureRecognizer::QWhipSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent), whipIt(0), lastX(0),
    detectedX(0), active(0)
{
}

QWhipSensorGestureRecognizer::~QWhipSensorGestureRecognizer()
{
}

void QWhipSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(750);
}

QString QWhipSensorGestureRecognizer::id() const
{
    return QString("QtSensors.whip");
}

bool QWhipSensorGestureRecognizer::start()
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

bool QWhipSensorGestureRecognizer::stop()
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

bool QWhipSensorGestureRecognizer::isActive()
{
    return active;
}

#define WHIP_THRESHOLD_FACTOR 0.85 //37
#define WHIP_DETECTION_FACTOR 0.15 // 5.85

#define WHIP_DEGREES 25

#define WHIP_Y_DEGREES 15
#define WHIP_DEGREES_BELOW

#define RADIANS_TO_DEGREES 57.2957795


void QWhipSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

void QWhipSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    qreal x = reading->x();
    qreal difference = lastX - x;

    if (qAbs(difference) < 1)
        return;

    qreal y = reading->y();
    qreal z = reading->z();

    qreal roll = qAtan(x / qSqrt(y*y + z*z)) * RADIANS_TO_DEGREES;

    if (whipIt) {

        if (/*orientationReading->orientation() == QOrientationReading::TopUp
                && */ roll > WHIP_Y_DEGREES
                && ((!wasNegative && qAbs(detectedX - x) > accelRange * WHIP_THRESHOLD_FACTOR)
                    || (wasNegative && detectedX - x > (accelRange * WHIP_THRESHOLD_FACTOR))) ) {
            Q_EMIT whip();
            Q_EMIT detected("whip");
            whipIt = false;
            timer->stop();
        }
    } else if (!timer->isActive()
              // && orientationReading->orientation() == QOrientationReading::TopUp
               && roll < WHIP_Y_DEGREES
               && ((difference > accelRange * WHIP_DETECTION_FACTOR)
                || (difference < -accelRange * WHIP_DETECTION_FACTOR))) {
        detectedX = x;
//        start of gesture
        timer->start();
        whipIt = true;
        if (difference > 0)
            wasNegative = false;
        else
            wasNegative = true;
    }
    lastX = x;
}

void QWhipSensorGestureRecognizer::timeout()
{
    whipIt = false;
}

QT_END_NAMESPACE
