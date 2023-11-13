// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef ANDROIDPRESSURE_H
#define ANDROIDPRESSURE_H

#include <qpressuresensor.h>

#include "sensoreventqueue.h"

class AndroidPressure : public SensorEventQueue<QPressureReading>
{
public:
    AndroidPressure(int type, QSensor *sensor, QObject *parent = nullptr);

protected:
    // SensorEventQueue interface
    void dataReceived(const ASensorEvent &event) override;
};

#endif // ANDROIDPRESSURE_H
