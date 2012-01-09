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


#include "qhoversensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

QHoverSensorGestureRecognizer::QHoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    hoverOk(0), lastLightReading(0), detecting(0)
{
}

QHoverSensorGestureRecognizer::~QHoverSensorGestureRecognizer()
{
}

void QHoverSensorGestureRecognizer::create()
{
    light = new QLightSensor(this);
    light->connectToBackend();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(1000);

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(timeout2()));
    timer2->setSingleShot(true);
    timer2->setInterval(3000);
}

QString QHoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.hover");
}

bool QHoverSensorGestureRecognizer::start()
{
    connect(light,SIGNAL(readingChanged()), this,SLOT(lightChanged()));
    light->start();
    return light->isActive();
}

bool QHoverSensorGestureRecognizer::stop()
{
   light->stop();
   disconnect(light,SIGNAL(readingChanged()),this,SLOT(lightChanged()));
   return light->isActive();
}

bool QHoverSensorGestureRecognizer::isActive()
{
    return light->isActive();
}

void QHoverSensorGestureRecognizer::lightChanged()
{
    qreal lightReading = light->reading()->lux();

    int difference = 100 - (lightReading/lastLightReading) * 100;

    if (difference == 0) {
        return;
    }

    if (!detecting && difference > 19) {
//        if (lightReading < lastLightReading ) {
        detecting = true;
        timer->start();
        timer2->start();
    } else if (hoverOk && detecting && difference < -24) {
        // went light again after 1 seconds
//            qDebug() << "hover";
            Q_EMIT hover();
            Q_EMIT detected("hover");
            hoverOk = false;
            detecting = false;
    }
    lastLightReading = lightReading;
}

void QHoverSensorGestureRecognizer::timeout()
{
    hoverOk = true;
}


void QHoverSensorGestureRecognizer::timeout2()
{
    detecting = false;
}
QT_END_NAMESPACE
