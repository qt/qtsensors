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

#include <QtSensors/QSensor>

#include "qturnoversensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

// turnover and put down i.e. facedown

QTurnoverSensorGestureRecognizer::QTurnoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    isClose(0)
  , isFaceDown(0)
{
}

QTurnoverSensorGestureRecognizer::~QTurnoverSensorGestureRecognizer()
{
}

void QTurnoverSensorGestureRecognizer::create()
{
    orientation = new QOrientationSensor(this);
    orientation->connectToBackend();
    proximity = new QProximitySensor(this);
    proximity->connectToBackend();


}

bool QTurnoverSensorGestureRecognizer::start()
{
    connect(orientation,SIGNAL(readingChanged()),this,SLOT(orientationChanged()));
    connect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
    active = (orientation->start() && proximity->start());
    return active;
}

bool QTurnoverSensorGestureRecognizer::stop()
{
    orientation->stop();
    proximity->stop();
    active = (orientation->isActive() && proximity->isActive());
    disconnect(orientation,SIGNAL(readingChanged()),this,SLOT(orientationChanged()));
    disconnect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
    return !active;
}

bool QTurnoverSensorGestureRecognizer::isActive()
{
    return active;
}

QString QTurnoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.turnover");
}

void QTurnoverSensorGestureRecognizer::proximityChanged()
{
    isClose = proximity->reading()->close();
    isRecognized();
}

void QTurnoverSensorGestureRecognizer::orientationChanged()
{
    switch (orientation->reading()->orientation()) {
       case  QOrientationReading::FaceDown:
    {
        isFaceDown = true;
        isRecognized();
    }
        break;
    default:
        isFaceDown = false;
        break;
    };
}

void QTurnoverSensorGestureRecognizer::isRecognized()
{
    if (isClose && isFaceDown) {
        Q_EMIT turnover();
        Q_EMIT detected("turnover");
    }
}
QT_END_NAMESPACE

