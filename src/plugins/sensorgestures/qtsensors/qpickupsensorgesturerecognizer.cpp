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

#define _USE_MATH_DEFINES
#include <QtCore/qmath.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419717
#endif
#ifndef M_PI_2
#define M_PI_2  1.57079632679489661923
#endif

QT_BEGIN_NAMESPACE

inline qreal calcPitch(double Ax, double Ay, double Az)
{
    return (float)-qAtan2(Ax, qSqrt(Ay * Ay + Az * Az));
}
inline qreal calcRoll(double Ax, double Ay, double Az)
{
    return (float)qAtan2(Ay, (qSqrt(Ax * Ax + Az * Az)));
}

QPickupSensorGestureRecognizer::QPickupSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),atRest(1),okToSignal(1),
    lastRoll(0)
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

#define PICKUP_BOTTOM_THRESHOLD 15
#define PICKUP_TOP_THRESHOLD 60

void QPickupSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();
    qreal xdiff =  pXaxis - x;
    qreal ydiff = pYaxis - y;
    qreal zdiff =  pZaxis - z;

    roll = calc(calcRoll(x, y, z));

    if (xdiff < 0.7 && ydiff < .7 && zdiff < .7) {
        atRest = true;
    } else {
        atRest = false;
    }
    if (roll > PICKUP_BOTTOM_THRESHOLD
            && (qAbs(lastRoll - roll) > PICKUP_BOTTOM_THRESHOLD)) {
        okToSignal = true;
        detectedRoll = roll;
    }
    if (atRest
            && okToSignal
            && (roll < PICKUP_TOP_THRESHOLD && roll > PICKUP_BOTTOM_THRESHOLD)) {
        if (!timer->isActive()) {
            timer->start();
        }
    }

    // initial at ~0, z = 9.8
    // at 'focus' when y == 6 to 8 && z == 5 to 7

    pXaxis = x;
    pYaxis = y;
    pZaxis = z;
    lastRoll = roll;
}

void QPickupSensorGestureRecognizer::timeout()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();

    qreal pitch = calc(calcPitch(x, y, z));

    if (atRest
            && (pitch > -6 && pitch < 6)
            && (roll < PICKUP_TOP_THRESHOLD && roll > PICKUP_BOTTOM_THRESHOLD)
            && (y > 5.0 && y < 8.9)
            && (z > 5.0 && z < 7.9)) {
        Q_EMIT pickup();
        Q_EMIT detected("pickup");

        okToSignal = false;
    }
}

qreal QPickupSensorGestureRecognizer::calc(qreal yrot)
{
    qreal aG = 1 * sin(yrot);
    qreal aK = 1 * cos(yrot);

    yrot = qAtan2(aG, aK);
    if (yrot > M_PI_2)
        yrot = M_PI - yrot;
    else if (yrot < -M_PI_2)
        yrot = -(M_PI + yrot);

    return yrot * 180 / M_PI;
}

QT_END_NAMESPACE
