// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef DUMMYACCELEROMETER_H
#define DUMMYACCELEROMETER_H

#include "dummycommon.h"
#include <qaccelerometer.h>

class dummyaccelerometer : public dummycommon
{
public:
    static char const * const id;

    dummyaccelerometer(QSensor *sensor);

    void poll() override;
private:
    QAccelerometerReading m_reading;
};

#endif

