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

QWhipSensorGestureRecognizer::QWhipSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent),
    orientationReading(0),
    accelRange(0),
    active(0),
    lastX(0),
    lastY(0),
    lastZ(0),
    detecting(0),
    whipOk(0){
}

QWhipSensorGestureRecognizer::~QWhipSensorGestureRecognizer()
{
}

void QWhipSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(850);
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

void QWhipSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

#define WHIP_FACTOR -11.0
#define WHIP_WIGGLE_FACTOR 0.35

void QWhipSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    const qreal x = reading->x();
    const qreal y = reading->y();
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

    if (orientationReading == 0)
        return;
    //// very hacky
    if (orientationReading->orientation() == QOrientationReading::FaceUp) {
        z = z - 9.8;
    }

    const qreal diffX = lastX - x;
    const qreal diffY = lastY - y;

    if (detecting && whipMap.count() > 5 && whipMap.at(5) == true) {
        checkForWhip();
    }

    if (whipMap.count() > 5)
        whipMap.removeLast();
//qDebug() << z << qAbs(diffX) << qAbs(lastX)  << qAbs(x) ;

    if (z < WHIP_FACTOR
            && qAbs(diffX) > -(accelRange * .1285)//-5.0115
            && qAbs(lastX) < 7
            && qAbs(x) < 7) {
        whipMap.insert(0,true);
        if (!detecting && !timer->isActive()) {
            timer->start();
            detecting = true;
//            qDebug() << "start detecting";
        }
    } else {
        whipMap.insert(0,false);
    }
    lastZ = z;

    if (negativeList.count() > 5)
        negativeList.removeLast();

    if ((((x < 0 && lastX > 0) || (x > 0 && lastX < 0))
         && qAbs(diffX) > (accelRange   * 0.7)) //27.3
            || (((y < 0 && lastY > 0) || (y > 0 && lastY < 0))
            && qAbs(diffY) > (accelRange * 0.7))) {
        negativeList.insert(0,true);
    } else {
        negativeList.insert(0,false);
    }

    lastX = x; lastY = y;

}

void QWhipSensorGestureRecognizer::timeout()
{
    detecting = false;
}


void QWhipSensorGestureRecognizer::checkForWhip()
{
 //   qDebug() << __FUNCTION__;

    whipOk = false;

    qreal averageZ = 0;
    Q_FOREACH (qreal az, zList) {
        averageZ += az;
    }
    averageZ /= zList.count();
 //   qDebug() << qAbs(averageZ) << zList << whipMap;

    if (qAbs(averageZ) < 5.0)
        return;

    for (int i = 0; i < 3; i++) {
        if (!whipMap.at(i)) {
            whipOk = true;
        } else {
            detecting = false;
            whipOk = false;
            timer->stop();

            return;
        }
    }

    if (whipOk) {
        bool ok = true;
        for (int i = 0; i < negativeList.count() - 1; i++) {
            if (negativeList.at(i)) {
                ok = false;
            }
        }

        if (ok) {
            Q_EMIT whip();
            Q_EMIT detected("whip");
        }
        detecting = false;
        whipMap.clear();
        timer->stop();
    }
}
QT_END_NAMESPACE
