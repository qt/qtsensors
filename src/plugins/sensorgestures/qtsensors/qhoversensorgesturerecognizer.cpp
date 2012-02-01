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
    proximity = new QProximitySensor(this);
    proximity->connectToBackend();

    irProx = new QIRProximitySensor(this);
    irProx->connectToBackend();

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
    connect(irProx,SIGNAL(readingChanged()), this,SLOT(proxyChanged()));
    proximity->start();
    irProx->start();
    return irProx->isActive();
}

bool QHoverSensorGestureRecognizer::stop()
{
    proximity->stop();
    irProx->stop();
    disconnect(irProx,SIGNAL(readingChanged()),this,SLOT(proxyChanged()));
    return irProx->isActive();
}

bool QHoverSensorGestureRecognizer::isActive()
{
    return irProx->isActive();
}

void QHoverSensorGestureRecognizer::proxyChanged()
{
    if (proximity->reading()->close()) {
        hoverOk = false;
        detecting = false;
        return;
    }

    int refl = irProx->reading()->reflectance() * 100;

    if (!detecting && (refl > 20 && refl < 35)) {
        detecting = true;
        timer->start();
        timer2->start();

    } else if (hoverOk && detecting
               && refl == 0) {
        // went light again after 1 seconds
            Q_EMIT hover();
            Q_EMIT detected("hover");
            hoverOk = false;
            detecting = false;
    }
    if (refl == 0)
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
