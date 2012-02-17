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

#include "qpickupsensorgesturerecognizer.h"

#include <QtCore/qmath.h>

#define RADIANS_TO_DEGREES 57.2957795

QT_BEGIN_NAMESPACE

QPickupSensorGestureRecognizer::QPickupSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),atRest(1),okToSignal(1),
    lastpitch(0), detecting(0)
{
}

QPickupSensorGestureRecognizer::~QPickupSensorGestureRecognizer()
{
}

void QPickupSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(500);

}

QString QPickupSensorGestureRecognizer::id() const
{
    return QString("QtSensors.pickup");
}

bool QPickupSensorGestureRecognizer::start()
{
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    accel->start();

    active = accel->isActive();
    return active;
}

bool QPickupSensorGestureRecognizer::stop()
{
    accel->stop();
    active = accel->isActive();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    return !active;
}

bool QPickupSensorGestureRecognizer::isActive()
{
    return active;
}

#define PICKUP_BOTTOM_THRESHOLD 30
#define PICKUP_TOP_THRESHOLD 60

void QPickupSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();
    qreal xdiff =  pXaxis - x;
    qreal ydiff = pYaxis - y;
    qreal zdiff =  pZaxis - z;

    pitch = qAtan(y / qSqrt(x*x + z*z)) * RADIANS_TO_DEGREES;

    if (qAbs(xdiff) < 0.7 && qAbs(ydiff) < .7 && qAbs(zdiff) < .7) {
        atRest = true;
    } else {
        atRest = false;
    }

    if (!atRest && (lastpitch - pitch < -PICKUP_BOTTOM_THRESHOLD)) {
        detecting = true;
        if (!timer->isActive()) {
            timer->start();
        }
        lastpitch = pitch;
    }

    pXaxis = x;
    pYaxis = y;
    pZaxis = z;
    if (atRest && !detecting)
        lastpitch = pitch;
}

void QPickupSensorGestureRecognizer::timeout()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();

    qreal roll = qAtan(x / qSqrt(y*y + z*z)) * RADIANS_TO_DEGREES;
    if ((roll > -6 && roll < 6)
            && (pitch < PICKUP_TOP_THRESHOLD && pitch > PICKUP_BOTTOM_THRESHOLD)
            && (y > 5.0 && y < 8.9)
            && (z > 5.0 && z < 7.9)) {
        Q_EMIT pickup();
        Q_EMIT detected("pickup");

        okToSignal = false;
    }
    detecting = false;
}

QT_END_NAMESPACE
