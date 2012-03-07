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

#include "qslamgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE

QSlamSensorGestureRecognizer::QSlamSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    orientationReading(0),
    accelRange(0),
    active(0),
    lastX(0),
    lastY(0),
    lastZ(0),
    detecting(0),
    slamOk(0)
{
}

QSlamSensorGestureRecognizer::~QSlamSensorGestureRecognizer()
{
}

void QSlamSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(1250);
}


QString QSlamSensorGestureRecognizer::id() const
{
    return QString("QtSensors.slam");
}

bool QSlamSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Accel)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
            active = true;
            accelRange = QtSensorGestureSensorHandler::instance()->accelRange;
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

bool QSlamSensorGestureRecognizer::stop()
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

bool QSlamSensorGestureRecognizer::isActive()
{

    return active;
}

void QSlamSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

#define SLAM_FACTOR -16.0
#define SLAM_WIGGLE_FACTOR 0.95

void QSlamSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    qreal x = reading->x();
    qreal y = reading->y();
    qreal z = reading->z();

    if (zList.count() > 4)
        zList.removeLast();

    qreal averageZ = 0;
    Q_FOREACH (qreal az, zList) {
        averageZ += az;
    }
    averageZ += z;
    averageZ /= zList.count() + 1;

    zList.insert(0,qAbs(averageZ));

    //// very hacky
    if (orientationReading == 0)
        return;
    if (orientationReading->orientation() == QOrientationReading::FaceUp) {
        z = z - 9.8;
    }

    qreal diffX = lastX - x;
    qreal diffY = lastY - y;

    if (detecting && slamMap.count() > 5 && slamMap.at(5) == true) {
        checkForSlam();
    }

    if (slamMap.count() > 5)
        slamMap.removeLast();
    if (z < SLAM_FACTOR
            && qAbs(diffX) < (accelRange  * SLAM_WIGGLE_FACTOR)
            && qAbs(diffY) < (accelRange  * SLAM_WIGGLE_FACTOR)) {
        slamMap.insert(0,true);
        if (!detecting && !timer->isActive()) {
            timer->start();
            detecting = true;
        }
    } else {
        slamMap.insert(0,false);
    }
    lastZ = z;

    if (negativeList.count() > 5)
        negativeList.removeLast();

    if ((((x < 0 && lastX > 0) || (x > 0 && lastX < 0))
         && qAbs(diffX) > (accelRange   * 0.7))
            || (((y < 0 && lastY > 0) || (y > 0 && lastY < 0))
            && qAbs(diffY) > (accelRange * 0.7))) {
        negativeList.insert(0,true);
    } else {
        negativeList.insert(0,false);
    }

    lastX = x; lastY = y;

}

void QSlamSensorGestureRecognizer::timeout()
{
    detecting = false;
    slamMap.clear();
}

void QSlamSensorGestureRecognizer:: checkForSlam()
{
    slamOk = false;

    qreal averageZ = 0;
    Q_FOREACH (qreal az, zList) {
        averageZ += az;
    }
    averageZ /= zList.count();

    if (qAbs(averageZ) < 6.0)
        return;

    for (int i = 0; i < slamMap.count() - 1; i++) {
        if (!slamMap.at(i)) {
            slamOk = true;
        } else {
            detecting = false;
            slamOk = false;
            timer->stop();

            return;
        }
    }
    if (slamOk) {
        bool ok = true;
        for (int i = 0; i < negativeList.count() - 1; i++) {
            if (negativeList.at(i)) {
                ok = false;
            }
        }

        if (ok) {
            Q_EMIT slam();
            Q_EMIT detected("slam");
        }
        detecting = false;
        slamMap.clear();
        timer->stop();
    }
}

QT_END_NAMESPACE
