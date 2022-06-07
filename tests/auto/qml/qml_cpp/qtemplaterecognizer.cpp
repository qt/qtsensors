// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QDebug>
#include <QTimer>

#include "qtemplaterecognizer.h"

QTemplateGestureRecognizer::QTemplateGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
{
}

QTemplateGestureRecognizer::~QTemplateGestureRecognizer()
{

}

void QTemplateGestureRecognizer::create()
{
    connect(&_timer,SIGNAL(timeout()),this,SLOT(timeout()));
    _timer.setInterval(1000);
}

bool QTemplateGestureRecognizer::start()
{
    Q_EMIT detected(id());
    _timer.start();
    return _timer.isActive();
}

bool QTemplateGestureRecognizer::stop()
{
    _timer.stop();
    return true;
}


bool QTemplateGestureRecognizer::isActive()
{
    return _timer.isActive();
}

QString QTemplateGestureRecognizer::id() const
{
    return QString("QtSensors.template");
}

void QTemplateGestureRecognizer::timeout()
{
    Q_EMIT detected(id());
}


QTemplateGestureRecognizer1::QTemplateGestureRecognizer1(QObject *parent)
    : QSensorGestureRecognizer(parent)
{
}

QTemplateGestureRecognizer1::~QTemplateGestureRecognizer1()
{

}

void QTemplateGestureRecognizer1::create()
{
    connect(&_timer,SIGNAL(timeout()),this,SLOT(timeout()));
    _timer.setInterval(500);
}

bool QTemplateGestureRecognizer1::start()
{
    Q_EMIT detected(id());
    _timer.start();
    return _timer.isActive();
}

bool QTemplateGestureRecognizer1::stop()
{
    _timer.stop();
    return true;
}


bool QTemplateGestureRecognizer1::isActive()
{
    return _timer.isActive();
}

QString QTemplateGestureRecognizer1::id() const
{
    return QString("QtSensors.template1");
}

void QTemplateGestureRecognizer1::timeout()
{
    Q_EMIT detected(id());
}
