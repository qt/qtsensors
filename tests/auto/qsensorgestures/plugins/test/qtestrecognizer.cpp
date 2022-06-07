// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QStringList>
#include <QTimer>

#include "qtestrecognizer.h"
#include "qtestsensorgestureplugin_p.h"


QTestRecognizer::QTestRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent),
      active(0)
{
    timeout();
}

QTestRecognizer::~QTestRecognizer()
{
}

void QTestRecognizer::timeout()
{
    Q_EMIT detected("tested");
    Q_EMIT tested();
    QTimer::singleShot(100, this, SLOT(timeout()));
}


bool QTestRecognizer::start()
{
    Q_EMIT detected("tested");
    Q_EMIT tested();
    active = true;
    return true;
}

bool QTestRecognizer::stop()
{
    active = false;
    return true;
}

bool QTestRecognizer::isActive()
{
    return active;
}

void  QTestRecognizer::create()
{
    active = false;
}

QString QTestRecognizer::id() const
{
    return QString("QtSensors.test");
}


int QTestRecognizer::thresholdTime() const
{
    return timerTimeout;
}

void QTestRecognizer::setThresholdTime(int msec)
{
    timer->setInterval(msec);
}
