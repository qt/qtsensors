// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QDebug>
#include <QTimer>

#include "qcounterrecognizer.h"

QCounterGestureRecognizer::QCounterGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
{
}

QCounterGestureRecognizer::~QCounterGestureRecognizer()
{

}

void QCounterGestureRecognizer::create()
{
    connect(&_timer,SIGNAL(timeout()),this,SLOT(timeout()));
    _timer.setInterval(1000);
}

bool QCounterGestureRecognizer::start()
{
    Q_EMIT detected(id());
    _timer.start();
    return _timer.isActive();
}

bool QCounterGestureRecognizer::stop()
{
    _timer.stop();
    return true;
}


bool QCounterGestureRecognizer::isActive()
{
    return _timer.isActive();
}

QString QCounterGestureRecognizer::id() const
{
    return QString("QtSensors.SecondCounter");
}

void QCounterGestureRecognizer::timeout()
{
    Q_EMIT detected(id());
}
