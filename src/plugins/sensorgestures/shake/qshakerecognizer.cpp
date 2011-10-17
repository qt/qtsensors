/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QDebug>
#include <QTimer>

#include "qshakerecognizer.h"

QShakeSensorGestureRecognizer::QShakeSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , active(0)
{
    pXaxis = 0;nXaxis = 0;
    pYaxis = 0;nYaxis = 0;
    pZaxis = 0;nZaxis = 0;
    timerTimeout = 1500;
}

QShakeSensorGestureRecognizer::~QShakeSensorGestureRecognizer()
{
}

void QShakeSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(timerTimeout);

    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));

}

bool QShakeSensorGestureRecognizer::start()
{
    active = accel->start();

    return active;
}

bool QShakeSensorGestureRecognizer::stop()
{
    accel->stop();
    active = accel->isActive();
    return !active;
}


bool QShakeSensorGestureRecognizer::isActive()
{
    return active;
}

QString QShakeSensorGestureRecognizer::id() const
{
    return QString("QtSensors.shake");
}


#define NUMBER_SHAKES 3
void QShakeSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal z = accel->reading()->z();
    qreal xdiff =  pXaxis - x;

    if (abs(xdiff) > 10) {
        nXaxis++;
        if (timer->isActive()) {
            timer->stop();
        }
        timer->start();
    }
    if (nXaxis >= NUMBER_SHAKES) {

        Q_EMIT shake();
        Q_EMIT detected("shake");

        if (timer->isActive()) {
            timer->stop();
        }
        timeout();
    }

    //    if (abs(zdiff) > 10) {
    //        nZaxis++;
    //        if (timer->isActive()) {
    //            timer->stop();
    //        }
    //        timer->start();
    //    }

    //    if (nZaxis >= NUMBER_SHAKES) {
    //        Q_EMIT detected("ShakeZ");
    //        Q_EMITshake();
    //        if (timer->isActive()) {
    //            timer->stop();
    //        }
    //        timeout();
    //    }
    pXaxis = x;
    pZaxis = z;
}

void QShakeSensorGestureRecognizer::timeout()
{
    nXaxis = 0;
    nYaxis = 0;
    nZaxis = 0;
}

int QShakeSensorGestureRecognizer::thresholdTime() const
{
    return timerTimeout;
}

void QShakeSensorGestureRecognizer::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}
