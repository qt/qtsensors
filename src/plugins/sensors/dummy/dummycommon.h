// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef DUMMYCOMMON_H
#define DUMMYCOMMON_H

#include <qsensorbackend.h>
#include <qsensor.h>

class dummycommon : public QSensorBackend
{
public:
    dummycommon(QSensor *sensor);

    void start() override;
    void stop() override;
    virtual void poll() = 0;
    void timerEvent(QTimerEvent * /*event*/) override;

protected:
    quint64 getTimestamp();

private:
    int m_timerid;
};

#endif

