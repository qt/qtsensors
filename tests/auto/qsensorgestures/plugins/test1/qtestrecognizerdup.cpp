// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QStringList>

#include "qtestrecognizerdup.h"
#include "qtestsensorgestureplugindup.h"

QTestRecognizerDup::QTestRecognizerDup(QObject *parent)
    : QSensorGestureRecognizer(parent),
      active(0)
{
}

QTestRecognizerDup::~QTestRecognizerDup()
{
}

bool QTestRecognizerDup::start()
{
    active = true;
    Q_EMIT detected("test2_dup");
    Q_EMIT test2_dup();
    return true;
}

bool QTestRecognizerDup::stop()
{
    active = false;
    return true;
}

bool QTestRecognizerDup::isActive()
{
    return active;
}

void  QTestRecognizerDup::create()
{
    active = false;
}

QString QTestRecognizerDup::id() const
{
    return QString("QtSensors.test.dup");
}


int QTestRecognizerDup::thresholdTime() const
{
    return timerTimeout;
}

void QTestRecognizerDup::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}
