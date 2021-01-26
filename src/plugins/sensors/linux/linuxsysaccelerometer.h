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

#ifndef LINUXSYSACCELEROMETER_H
#define LINUXSYSACCELEROMETER_H

#include <qsensorbackend.h>
#include <qaccelerometer.h>
#include <QtCore/QFile>


class LinuxSysAccelerometer : public QSensorBackend
{
public:
    static char const * const id;

    LinuxSysAccelerometer(QSensor *sensor);
    ~LinuxSysAccelerometer();

    void start() override;
    void stop() override;
    void poll();
    void timerEvent(QTimerEvent * /*event*/) override;

private:
    QAccelerometerReading m_reading;
    int m_timerid;

    bool openFile();
    void closeFile();
    QString path;
    QFile file;
    float divisor;
    QString delimiter;
};

#endif // LINUXSYSACCELEROMETER_H

