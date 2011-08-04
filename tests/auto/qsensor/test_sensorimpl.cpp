/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "test_sensorimpl.h"
#include <QDebug>

const char *testsensorimpl::id("test sensor impl");

static testsensorimpl *exclusiveHandle = 0;

testsensorimpl::testsensorimpl(QSensor *sensor)
    : QSensorBackend(sensor)
{
    setReading<TestSensorReading>(&m_reading);
    setDescription("sensor description");
    addOutputRange(0, 1, 0.5);
    addOutputRange(0, 2, 1);
    QString doThis = sensor->property("doThis").toString();
    if (doThis == "rates(0)") {
        setDataRates(0);
    } else if (doThis == "rates(nodef)") {
        TestSensor *acc = new TestSensor(this);
        setDataRates(acc);
        delete acc;
    } else if (doThis == "rates") {
        TestSensor *acc = new TestSensor(this);
        acc->connectToBackend();
        setDataRates(acc);
        delete acc;
    } else {
        addDataRate(100, 100);
    }
    reading();
}

testsensorimpl::~testsensorimpl()
{
    Q_ASSERT(exclusiveHandle != this);
}

void testsensorimpl::start()
{
    QVariant _exclusive = sensor()->property("exclusive");
    bool exclusive = _exclusive.isValid()?_exclusive.toBool():false;
    if (exclusive) {
        if (!exclusiveHandle) {
            exclusiveHandle = this;
        } else {
            // Hook up the busyChanged signal
            connect(exclusiveHandle, SIGNAL(emitBusyChanged()), sensor(), SIGNAL(busyChanged()));
            sensorBusy(); // report the busy condition
            return;
        }
    }

    QString doThis = sensor()->property("doThis").toString();
    if (doThis == "stop")
        sensorStopped();
    else if (doThis == "error")
        sensorError(1);
    else if (doThis == "setOne") {
        m_reading.setTimestamp(1);
        m_reading.setTest(1);
        newReadingAvailable();
    } else {
        m_reading.setTimestamp(2);
        m_reading.setTest(2);
        newReadingAvailable();
    }
}

void testsensorimpl::stop()
{
    QVariant _exclusive = sensor()->property("exclusive");
    bool exclusive = _exclusive.isValid()?_exclusive.toBool():false;
    if (exclusive && exclusiveHandle == this) {
        exclusiveHandle = 0;
        emit emitBusyChanged(); // notify any waiting instances that they can try to grab the sensor now
    }
}

