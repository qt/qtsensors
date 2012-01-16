/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qtwistsensorgesturerecognizer.h"

#define _USE_MATH_DEFINES
#include <QtCore/qmath.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419717
#endif
#ifndef M_PI_2
#define M_PI_2  1.57079632679489661923
#endif

QT_BEGIN_NAMESPACE

// from qsensor2tilt
inline qreal calcPitch(double Ax, double Ay, double Az)
{
    return (float)-atan2(Ax, sqrt(Ay * Ay + Az * Az));
}

inline qreal calcRoll(double Ax, double Ay, double Az)
{
    return (float)atan2(Ay, (sqrt(Ax * Ax + Az * Az)));
}

QTwistSensorGestureRecognizer::QTwistSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent), detecting(0), lastDegree(0)
{
}

QTwistSensorGestureRecognizer::~QTwistSensorGestureRecognizer()
{
}

void QTwistSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum);
    else
        accelRange = 44; //this should never happen

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
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    active = accel->start();
    return active;
}

bool QTwistSensorGestureRecognizer::stop()
{
    accel->stop();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));

    active = accel->isActive();
    return !active;
}

bool QTwistSensorGestureRecognizer::isActive()
{
    return active;
}

#define RESTING_VARIANCE 10
#define THRESHOLD_DEGREES 40

void QTwistSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();

    if (abs(x) < 1)
        return;

    pitch = calcPitch(x, y, z);
    roll = calcRoll(x, y, z);

    qreal degrees = calc(pitch);

    if (xList.count() > 4) {
        if (detecting &&
                abs(lastDegree - degrees) > (accelRange/2)) {
            if (lastX < 0) {
                Q_EMIT twistLeft();
                Q_EMIT detected("twistLeft");
            } else {
                Q_EMIT twistRight();
                Q_EMIT detected("twistRight");
            }
            detecting = false;
            timer->stop();
            lastX = degrees;
        }

        if (!detecting && abs(degrees) > THRESHOLD_DEGREES) {
            detecting = true;
            timer->start();
            lastX = degrees;
        }
    }

    if (xList.count() > 5)
        xList.removeLast();
    xList.insert(0,degrees);
    lastDegree = degrees;
}

void QTwistSensorGestureRecognizer::timeout()
{
    detecting = false;
    lastX = 0;
}

qreal QTwistSensorGestureRecognizer::calc(qreal yrot)
{
    qreal aG = 1 * sin(yrot);
    qreal aK = 1 * cos(yrot);

    yrot = atan2(aG, aK);
    if (yrot > M_PI_2)
        yrot = M_PI - yrot;
    else if (yrot < -M_PI_2)
        yrot = -(M_PI + yrot);

    return yrot * 180 / M_PI;
}

QT_END_NAMESPACE
