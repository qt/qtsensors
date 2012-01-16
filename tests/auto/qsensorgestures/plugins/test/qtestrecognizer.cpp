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
    QTimer::singleShot(10,this, SLOT(timeout()));
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
