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

#include <QDebug>
#include <QTimer>

#include "qshake2recognizer.h"

QT_BEGIN_NAMESPACE

QShake2SensorGestureRecognizer::QShake2SensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , active(0)
{
    pXaxis = 0;nXaxis = 0;
    pYaxis = 0;nYaxis = 0;
    pZaxis = 0;nZaxis = 0;
    timerTimeout = 750;
}

QShake2SensorGestureRecognizer::~QShake2SensorGestureRecognizer()
{
}

void QShake2SensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum *2) / 9.8; //approx range in g's
    else
        accelRange = 4; //this should never happen

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(timerTimeout);


}

bool QShake2SensorGestureRecognizer::start()
{
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    active = accel->start();

    return active;
}

bool QShake2SensorGestureRecognizer::stop()
{
    accel->stop();
    active = accel->isActive();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    return !active;
}

bool QShake2SensorGestureRecognizer::isActive()
{
    return active;
}

QString QShake2SensorGestureRecognizer::id() const
{
    return QString("QtSensors.shake2");
}

#define NUMBER_SHAKES 3
void QShake2SensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal xdiff =  pXaxis - x;
    qreal y = accel->reading()->y();
    qreal ydiff = pYaxis - y;
    qreal z = accel->reading()->z();
    qreal zdiff =  pZaxis - z;

    if (abs(xdiff) > (5 * accelRange)) {

        if (shakeDirection == QShake2SensorGestureRecognizer::ShakeUndefined && nXaxis == 0) {
            if (xdiff < 0)
                shakeDirection = QShake2SensorGestureRecognizer::ShakeLeft;
            else
                shakeDirection = QShake2SensorGestureRecognizer::ShakeRight;
        }

        nXaxis++;
        if (timer->isActive()) {
            timer->stop();
        }
        timer->start();
    }
    if (abs(ydiff) > (5 * accelRange)) {
        if (nYaxis == 0) {
            if (shakeDirection == QShake2SensorGestureRecognizer::ShakeUndefined && ydiff < 0)
                shakeDirection = QShake2SensorGestureRecognizer::ShakeDown;
            else
                shakeDirection = QShake2SensorGestureRecognizer::ShakeUp;
        }
        nYaxis++;
        if (timer->isActive()) {
            timer->stop();
        }
        timer->start();
    }
    if (abs(zdiff) > (5 * accelRange)) {
            nZaxis++;
            if (timer->isActive()) {
                timer->stop();
            }
            timer->start();
        }

        if (nYaxis + nZaxis + nXaxis >= NUMBER_SHAKES) {

            switch (shakeDirection) {
            case QShake2SensorGestureRecognizer::ShakeLeft:
                Q_EMIT shakeLeft();
                Q_EMIT detected("shakeLeft");
                break;
            case QShake2SensorGestureRecognizer::ShakeRight:
                Q_EMIT shakeRight();
                Q_EMIT detected("shakeRight");
                break;
            case QShake2SensorGestureRecognizer::ShakeUp:
                Q_EMIT shakeUp();
                Q_EMIT detected("shakeUp");
                break;
            case QShake2SensorGestureRecognizer::ShakeDown:
                Q_EMIT shakeDown();
                Q_EMIT detected("shakeDown");
                break;

            };
            if (timer->isActive()) {
                timer->stop();
            }
            timeout();
        }
    pXaxis = x;
    pYaxis = y;
    pZaxis = z;
}

void QShake2SensorGestureRecognizer::timeout()
{
    nXaxis = 0;
    nYaxis = 0;
    nZaxis = 0;
    shakeDirection = QShake2SensorGestureRecognizer::ShakeUndefined;

}

int QShake2SensorGestureRecognizer::thresholdTime() const
{
    return timerTimeout;
}

void QShake2SensorGestureRecognizer::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}

QT_END_NAMESPACE
