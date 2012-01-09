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


#include "qcoversensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

QCoverSensorGestureRecognizer::QCoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    lastProx(0)
{
}

QCoverSensorGestureRecognizer::~QCoverSensorGestureRecognizer()
{
}

void QCoverSensorGestureRecognizer::create()
{
    proximity = new QProximitySensor(this);
    proximity->connectToBackend();

    orientation = new QOrientationSensor(this);
    orientation->connectToBackend();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(1000);
}

QString QCoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.cover");
}

bool QCoverSensorGestureRecognizer::start()
{
    connect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
    proximity->start();
    orientation->start();
    return proximity->isActive();
}

bool QCoverSensorGestureRecognizer::stop()
{
    proximity->stop();
    orientation->stop();
    disconnect(proximity,SIGNAL(readingChanged()),this,SLOT(proximityChanged()));
    return proximity->isActive();
}

bool QCoverSensorGestureRecognizer::isActive()
{
    return proximity->isActive();
}

void QCoverSensorGestureRecognizer::proximityChanged()
{
    if ((orientation->reading()->orientation() ==  QOrientationReading::FaceDown
            || orientation->reading()->orientation() ==  QOrientationReading::FaceUp)
            && proximity->reading()->close())
        timer->start();
}

void QCoverSensorGestureRecognizer::timeout()
{

    if ((orientation->reading()->orientation() ==  QOrientationReading::FaceUp)
            && proximity->reading()->close()) {
        Q_EMIT cover();
        Q_EMIT detected("cover");
    }
    lastProx = proximity->reading()->close();
}

QT_END_NAMESPACE
