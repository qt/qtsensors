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

#include <QDebug>
#include <QTimer>

#include "qshake2recognizer.h"
#include <math.h>


QT_BEGIN_NAMESPACE

QShake2SensorGestureRecognizer::QShake2SensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , active(0),shaking(0), shakeCount(0),
      shakeDirection(QShake2SensorGestureRecognizer::ShakeUndefined)
{
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
#define THRESHOLD 25

void QShake2SensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();

    currentData.x = x;
    currentData.y = y;
    currentData.z = z;

    if ( (abs(currentData.x - prevData.x)
          || abs(currentData.y - prevData.y)
          || abs(currentData.z - prevData.z)) < 1)
        return;

    if (!shaking && checkForShake(prevData, currentData, THRESHOLD) &&
        shakeCount >= NUMBER_SHAKES) {
        shaking = true;
        shakeCount = 0;

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
        default:
            break;
        };

    } else if (checkForShake(prevData, currentData, THRESHOLD)) {

        if (shakeCount == 0 && shakeDirection == QShake2SensorGestureRecognizer::ShakeUndefined) {

            int xdiff = currentData.x - prevData.x;
            int ydiff = currentData.y - prevData.y;

            int max = qMax(abs(ydiff), abs(xdiff));

            if (max == abs(xdiff)) {
                if (isNegative(xdiff))
                    shakeDirection = QShake2SensorGestureRecognizer::ShakeLeft;
                else
                    shakeDirection = QShake2SensorGestureRecognizer::ShakeRight;

            } else if (max == abs(ydiff)) {
                if (isNegative(ydiff))
                    shakeDirection = QShake2SensorGestureRecognizer::ShakeDown;
                else
                    shakeDirection = QShake2SensorGestureRecognizer::ShakeUp;
            }
        }
        shakeCount++;
        timer->start();

    }

    prevData.x = currentData.x;
    prevData.y = currentData.y;
    prevData.z = currentData.z;

}

void QShake2SensorGestureRecognizer::timeout()
{
    shakeCount = 0;
    shaking = false;
    shakeDirection = QShake2SensorGestureRecognizer::ShakeUndefined;

}
bool QShake2SensorGestureRecognizer::checkForShake(ShakeData prevSensorData, ShakeData currentSensorData, qreal threshold)
{
    double deltaX = qAbs(prevSensorData.x - currentSensorData.x);
    double deltaY = qAbs(prevSensorData.y - currentSensorData.y);
    double deltaZ = qAbs(prevSensorData.z - currentSensorData.z);

    return (deltaX > threshold
            || deltaY > threshold
            || deltaZ > threshold);
}

bool QShake2SensorGestureRecognizer::isNegative(qreal num)
{
    if (num < 0)
        return true;
    return false;
}



QT_END_NAMESPACE
