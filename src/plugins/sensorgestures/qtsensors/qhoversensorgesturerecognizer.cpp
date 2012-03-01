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


#include "qhoversensorgesturerecognizer.h"
#include <math.h>

QT_BEGIN_NAMESPACE

QHoverSensorGestureRecognizer::QHoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
    hoverOk(0), lastLightReading(0), detecting(0), active(0)
{
}

QHoverSensorGestureRecognizer::~QHoverSensorGestureRecognizer()
{
}

void QHoverSensorGestureRecognizer::create()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(1000);

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(timeout2()));
    timer2->setSingleShot(true);
    timer2->setInterval(5000);
}

QString QHoverSensorGestureRecognizer::id() const
{
    return QString("QtSensors.hover");
}

bool QHoverSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::IrProximity)) {
        active = true;
        connect(QtSensorGestureSensorHandler::instance(),SIGNAL(irProximityReadingChanged(QIRProximityReading *)),
                this,SLOT(irProximityReadingChanged(QIRProximityReading *)));
    } else {
        active = false;
    }
    return active;
}

bool QHoverSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::IrProximity);
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(irProximityReadingChanged(QIRProximityReading *)),
            this,SLOT(irProximityReadingChanged(QIRProximityReading *)));
    active = false;
    return active;
}

bool QHoverSensorGestureRecognizer::isActive()
{
    return active;
}

void QHoverSensorGestureRecognizer::irProximityReadingChanged(QIRProximityReading *reading)
{
    reflectance = reading->reflectance();

    if (reflectance > .51) {
        hoverOk = false;
        detecting = false;
        return;
    }

    if (!detecting && (reflectance > .35 && reflectance < .50)) {
        detecting = true;
        timer->start();
        timer2->start();
        detectedHigh = reflectance;

    } else if (hoverOk && detecting
               && reflectance < .33
           //    && detectedHigh
               ) {
        // went light again after 1 seconds
        Q_EMIT hover();
        Q_EMIT detected("hover");
        hoverOk = false;
        detecting = false;
    }
    if (reflectance > .60)
        detecting = false;
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
