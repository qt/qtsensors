// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "qtest2recognizer.h"

#include "qtestsensorgestureplugin_p.h"

QTest2Recognizer::QTest2Recognizer(QObject *parent)
    : QSensorGestureRecognizer(parent),
    active(0)
{
}

QTest2Recognizer::~QTest2Recognizer()
{
}

bool QTest2Recognizer::start()
{
    Q_EMIT test2();

    Q_EMIT detected("test2");

    Q_EMIT test3(true);
    active = true;

    return true;
}

bool QTest2Recognizer::stop()
{
    active = false;
    return true;
}

bool QTest2Recognizer::isActive()
{
    return active;
}


void QTest2Recognizer::create()
{
    active = false;
}

QString QTest2Recognizer::id() const
{
    return QString("QtSensors.test2");
}

int QTest2Recognizer::thresholdTime() const
{
    return timerTimeout;
}

void QTest2Recognizer::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}

