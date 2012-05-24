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
    , active(0)
    , detecting(0)
    , checking(0)
{
}

QTwistSensorGestureRecognizer::~QTwistSensorGestureRecognizer()
{
}

void QTwistSensorGestureRecognizer::create()
{
}

QString QTwistSensorGestureRecognizer::id() const
{
    return QString("QtSensors.twist");
}

bool QTwistSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Accel)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
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
    detecting = false;
    checking = false;
    dataList.clear();
    return active;
}

bool QTwistSensorGestureRecognizer::isActive()
{
    return active;
}

void QTwistSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
    checkOrientation();
}

bool QTwistSensorGestureRecognizer::checkOrientation()
{
    if (orientationReading->orientation() == QOrientationReading::TopUp
            || orientationReading->orientation() == QOrientationReading::TopDown
            || orientationReading->orientation() == QOrientationReading::FaceDown) {
        reset();
        return false;
    }
    return true;
}


void QTwistSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    if (orientationReading == 0)
        return;

    const qreal x = reading->x();
    const qreal y = reading->y();
    const qreal z = reading->z();

    if (!detecting && !checking&& dataList.count() > 21)
        dataList.removeLast();

    twistAccelData data;
    data.x = x;
    data.y = y;
    data.z = z;
    if (qAbs(x) > 1)
        dataList.append(data);
    if (qAbs(z) > 15.0) {
        reset();
    }
    if (detecting
            && dataList.count() > 5
            && z > 9.0
            && qAbs(x) < 2) {
        //possible pickup
        if (!checking)
            checkTwist();
    }

    if (!detecting && z < 0 && checkOrientation()) {
        detecting = true;
    }
}

void QTwistSensorGestureRecognizer::checkTwist()
{
    checking = true;
    int lastx = 0;
    bool ok = false;
    bool spinpoint = false;
    qreal degrees = 0;
    for (int i = 0; i < dataList.count(); i++) {
        twistAccelData curData = dataList.at(i);

        if (!spinpoint && qAbs(curData.x) < 1)
            continue;
        if (curData.z >= 0 ) {
            if (!spinpoint && (curData.x > lastx ||  curData.x < lastx)) {
                ok = true;
            } else if (spinpoint && (curData.x < lastx || curData.x > lastx)) {
                ok = true;
            } else {
                ok = false;
            }
        } else if (!spinpoint && curData.z < 0) {
            spinpoint = true;
            degrees = qAtan(curData.x / qSqrt(curData.y*curData.y + curData.z*curData.z)) * RADIANS_TO_DEGREES;
        } else if (spinpoint && curData.z > 9) {
            break;
        }

        lastx = curData.x;
    }

    if (ok) {
        if (degrees > 0) {
            Q_EMIT twistLeft();
            Q_EMIT detected("twistLeft");
        } else {
            Q_EMIT twistRight();
            Q_EMIT detected("twistRight");
        }
    }
    reset();
}

void QTwistSensorGestureRecognizer::reset()
{
    detecting = false;
    checking = false;
    dataList.clear();
}



QT_END_NAMESPACE
