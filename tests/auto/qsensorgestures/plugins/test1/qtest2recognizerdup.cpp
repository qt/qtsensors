// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "qtest2recognizerdup.h"

#include "qtestsensorgestureplugindup.h"

QTest2RecognizerDup::QTest2RecognizerDup(QObject *parent)
    : QSensorGestureRecognizer(parent),
    active(0)
{
}

QTest2RecognizerDup::~QTest2RecognizerDup()
{
}

bool QTest2RecognizerDup::start()
{
    Q_EMIT test2_dup();

    active = true;

    return true;
}

bool QTest2RecognizerDup::stop()
{
    active = false;
    return true;
}

bool QTest2RecognizerDup::isActive()
{
    return active;
}


void QTest2RecognizerDup::create()
{
    active = false;
}

QString QTest2RecognizerDup::id() const
{
    return QString("QtSensors.test.dup");
}

int QTest2RecognizerDup::thresholdTime() const
{
    return timerTimeout;
}

void QTest2RecognizerDup::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}

