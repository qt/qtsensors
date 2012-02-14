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
#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE

QSlamSensorGestureRecognizer::QSlamSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
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
    accel = new QAccelerometer(this);
    accel->connectToBackend();

    orientation = new QOrientationSensor(this);
    orientation->connectToBackend();

    timer = new QTimer(this);

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum *2);//39
    else
        accelRange = 40; //this should never happen

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(1000);
}


QString QSlamSensorGestureRecognizer::id() const
{
    return QString("QtSensors.slam");
}

bool QSlamSensorGestureRecognizer::start()
{
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    accel->setDataRate(10);
    active = accel->start();
    orientation->start();

    return active;
}

bool QSlamSensorGestureRecognizer::stop()
{
    accel->stop();
    orientation->stop();
    active = accel->isActive();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    return !active;
}

bool QSlamSensorGestureRecognizer::isActive()
{

    return active;
}

#define SLAM_FACTOR -20.0

void QSlamSensorGestureRecognizer::accelChanged()
{
    qreal z = accel->reading()->z();

//// very hacky
    QOrientationReading::Orientation currentOrientation = orientation->reading()->orientation();

    if (currentOrientation == QOrientationReading::FaceUp) {
        z = z - 9.8;
    }

    qreal diffZ = lastZ - z;

    if (detecting && slamMap.count() > 5 && slamMap.at(5) == true) {
        checkForSlam();
    }

    if (slamMap.count() > 5)
        slamMap.removeLast();

    if (z < SLAM_FACTOR) {
        slamMap.insert(0,true);
        if (!detecting && !timer->isActive()) {
            timer->start();
            detecting = true;
        }
    } else {
        slamMap.insert(0,false);
    }
    lastZ = z;
}

void QSlamSensorGestureRecognizer::timeout()
{
    detecting = false;
    slamMap.clear();
}

void QSlamSensorGestureRecognizer:: checkForSlam()
{
    slamOk = false;

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
        Q_EMIT slam();
        Q_EMIT detected("slam");
        detecting = false;
        slamMap.clear();
        timer->stop();
    }
}

QT_END_NAMESPACE
