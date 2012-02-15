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

#include "qshakerecognizer.h"

QShakeSensorGestureRecognizer::QShakeSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , active(0)
{
}

QShakeSensorGestureRecognizer::~QShakeSensorGestureRecognizer()
{
}

void QShakeSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum *2) / 9.8; //approx range in g's
    else
        accelRange = 4; //this should never happen

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
#define THRESHOLD 25

void QShakeSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();
    qreal y = accel->reading()->y();
    qreal z = accel->reading()->z();

    currentData.x = x;
    currentData.y = y;
    currentData.z = z;

    if ((qAbs(currentData.x - prevData.x)
          || qAbs(currentData.y - prevData.y)
          || qAbs(currentData.z - prevData.z)) < 1)
        return;


    if (!shaking && checkForShake(prevData, currentData, THRESHOLD) &&
        shakeCount >= NUMBER_SHAKES) {
        shaking = true;
        shakeCount = 0;

        Q_EMIT shake();
        Q_EMIT detected("shake");

    } else if (checkForShake(prevData, currentData, THRESHOLD)) {
        shakeCount++;
    } else if (!checkForShake(prevData, currentData, 200)) {
        shakeCount = 0;
        shaking = false;
    }

    prevData.x = currentData.x;
    prevData.y = currentData.y;
    prevData.z = currentData.z;
}


bool QShakeSensorGestureRecognizer::checkForShake(AccelData prevSensorData, AccelData currentSensorData, qreal threshold)
{
    double deltaX = qAbs(prevSensorData.x - currentSensorData.x);
    double deltaY = qAbs(prevSensorData.y - currentSensorData.y);
    double deltaZ = qAbs(prevSensorData.z - currentSensorData.z);

    return (deltaX > threshold && deltaY > threshold) ||
         (deltaX > threshold && deltaZ > threshold) ||
         (deltaY > threshold && deltaZ > threshold);
}

