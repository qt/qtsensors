/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "linuxsysaccelerometer.h"
#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include <QtCore/QStringList>

#include <time.h>
#include <errno.h>

char const * const LinuxSysAccelerometer::id("linuxsys.accelerometer");

// This plugin reads the accelerometer from a sys interface.

// test machine (laptop):
// QT_ACCEL_FILEPATH=/sys/devices/platform/lis3lv02d/position
// QT_ACCEL_DATADIVISOR=7
// QT_ACCEL_DELIMITER=,

quint64 produceTimestamp()
{
    struct timespec tv;
    int ok;

#ifdef CLOCK_MONOTONIC_RAW
    ok = clock_gettime(CLOCK_MONOTONIC_RAW, &tv);
    if (ok != 0)
#endif
    ok = clock_gettime(CLOCK_MONOTONIC, &tv);
    Q_ASSERT(ok == 0);

    quint64 result = (tv.tv_sec * 1000000ULL) + (tv.tv_nsec * 0.001); // scale to microseconds
    return result;
}

// TODO get output template from env and apply
// Currently this assumes the output is like:
// (x,y,z) or x,y,z

LinuxSysAccelerometer::LinuxSysAccelerometer(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_timerid(0)
    , path(QString())
    , divisor(0)
    , delimiter(QString())
{
    setReading<QAccelerometerReading>(&m_reading);
    addDataRate(1, 100); // 100Hz
    addOutputRange(-22.418, 22.418, 0.17651); // 2G
// not sure how to retrieve proper range

    path = QString::fromLatin1(qgetenv("QT_ACCEL_FILEPATH"));
    bool ok;
    divisor = QString::fromLatin1(qgetenv("QT_ACCEL_DATADIVISOR")).toInt(&ok);
    if (divisor == 0 || !ok) {
        divisor = 1;
    }
    delimiter = QString::fromLatin1(qgetenv("QT_ACCEL_DELIMITER"));
    file.setFileName(path);
}

LinuxSysAccelerometer::~LinuxSysAccelerometer()
{
}

void LinuxSysAccelerometer::start()
{
    if (m_timerid)
        return;

    if (!openFile())
        return;

    int dataRate = sensor()->dataRate();
    if (dataRate == 0) {
        if (sensor()->availableDataRates().count())
            dataRate = sensor()->availableDataRates().first().second;
        else
            dataRate = 1;
    }

    int interval = 1000 / dataRate;

    if (interval)
        m_timerid = startTimer(interval);
}

void LinuxSysAccelerometer::stop()
{
    if (m_timerid) {
        killTimer(m_timerid);
        m_timerid = 0;
    }
    closeFile();
}

void LinuxSysAccelerometer::poll()
{
    if (!file.isOpen())
        return;

    file.seek(0);
    QString str = file.readLine();
    if (str.isEmpty()) {
        return;
    }
    str = str.simplified();

    if (!str.at(0).isNumber() && str.at(0) != '-') {
        str.remove(0,1);
    }

    if (!str.at(str.size()-1).isNumber()) {
        str.chop(1);
    }

    QStringList accelDataList = str.split(delimiter);

    m_reading.setTimestamp(produceTimestamp());
    m_reading.setX(-accelDataList.at(0).toFloat() / divisor);
    m_reading.setY(-accelDataList.at(1).toFloat() / divisor);
    m_reading.setZ(-accelDataList.at(2).toFloat() / divisor);

    newReadingAvailable();
}

void LinuxSysAccelerometer::timerEvent(QTimerEvent * /*event*/)
{
    poll();
}

bool LinuxSysAccelerometer::openFile()
{
    if (!path.isEmpty()
            && !file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file" << strerror(errno);
        return false;
    }
    return true;
}

void LinuxSysAccelerometer::closeFile()
{
    file.close();
}


