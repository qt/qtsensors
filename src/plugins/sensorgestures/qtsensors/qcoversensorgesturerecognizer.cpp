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

#include "qcoversensorgesturerecognizer.h"
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

QCoverSensorGestureRecognizer::QCoverSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent),
  orientationReading(0), proximityReading(0),lastProx(0), active(0), detecting(0)
{
}

QCoverSensorGestureRecognizer::~QCoverSensorGestureRecognizer()
{
}

void QCoverSensorGestureRecognizer::create()
{
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
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::IrProximity)) {
        if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Orientation)) {
            active = true;
            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(irProximityReadingChanged(QIRProximityReading *)),
                    this,SLOT(proximityChanged(QIRProximityReading *)));

            connect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading *)),
                    this,SLOT(orientationReadingChanged(QOrientationReading *)));
        } else {
            QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::IrProximity);
            active = false;
        }
    } else {
        active = false;
    }
    return active;
}

bool QCoverSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::IrProximity);
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Orientation);

    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(irProximityReadingChanged(QIRProximityReading *)),
            this,SLOT(proximityChanged(QIRProximityReading *)));
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(orientationReadingChanged(QOrientationReading *)),
            this,SLOT(orientationReadingChanged(QOrientationReading *)));

    active = false;

    return active;
}

bool QCoverSensorGestureRecognizer::isActive()
{
    return active;
}

void QCoverSensorGestureRecognizer::proximityChanged(QIRProximityReading *reading)
{
    if (orientationReading == 0)
        return;

    proximityReading = reading->reflectance();
    const qreal difference =  lastProx - proximityReading;

    if (qAbs(difference) < .15) {
        return;
    }
    // look at case of face up->face down->face up.
    if (orientationReading->orientation() ==  QOrientationReading::FaceUp
            && proximityReading > .55) {
        if (!timer->isActive()) {
            timer->start();
            detecting = true;
        }
    }
    if (proximityReading < .55) {
        if (timer->isActive()) {
            timer->stop();
            detecting = false;
        }
    }
    lastProx = proximityReading;
}

void QCoverSensorGestureRecognizer::orientationReadingChanged(QOrientationReading *reading)
{
    orientationReading = reading;
}

void QCoverSensorGestureRecognizer::timeout()
{
    if ((orientationReading->orientation() == QOrientationReading::FaceUp)
            && proximityReading > 0.55) {
        Q_EMIT cover();
        Q_EMIT detected("cover");
        detecting = false;
    }
    lastProx = proximityReading;
}

QT_END_NAMESPACE
