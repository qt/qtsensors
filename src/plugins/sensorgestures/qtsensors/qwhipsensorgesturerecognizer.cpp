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


#include "qwhipsensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

QWhipSensorGestureRecognizer::QWhipSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent), whipIt(0)
{
}

QWhipSensorGestureRecognizer::~QWhipSensorGestureRecognizer()
{
}

void QWhipSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum *2);
    else
        accelRange = 44; //this should never happen
qDebug() << accelRange;
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
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    active = accel->start();

    return active;
}

bool QWhipSensorGestureRecognizer::stop()
{
    accel->stop();
    active = accel->isActive();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    return !active;
}

bool QWhipSensorGestureRecognizer::isActive()
{
    return active;
}

void QWhipSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();

    if (whipIt) {
        qreal difference = lastX - x;
//        qDebug() << Q_FUNC_INFO << x << difference << wasNegative;

        if ((!wasNegative && difference > accelRange * .75) //58
                || (wasNegative && difference < -accelRange * .75)) {

//            qDebug() << Q_FUNC_INFO << "WHIP";
            Q_EMIT whip();
            Q_EMIT detected("whip");
            whipIt = false;
        }
//    } else if ((lastX - x) > (accelRange/2) || // 39
//               (x - lastX) < -(accelRange/2)) {
    } else if (x > (accelRange/3.3) || // 23
               x < -(accelRange/3.3)) {
        //start of gesture
//        qDebug() << Q_FUNC_INFO << "start detection";
        timer->start();
        whipIt = true;
        lastX = x;
        if (lastX > 0)
            wasNegative = false;
        else
            wasNegative = true;
    }
}

void QWhipSensorGestureRecognizer::timeout()
{
//    qDebug() << Q_FUNC_INFO;
    whipIt = false;
}

QT_END_NAMESPACE
