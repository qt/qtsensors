// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef ANDROIDLIGHT_H
#define ANDROIDLIGHT_H

#include <qlightsensor.h>

#include "sensoreventqueue.h"

class AndroidLight : public SensorEventQueue<QLightReading>
{
public:
    AndroidLight(int type, QSensor *sensor, QObject *parent = nullptr);

protected:
    // SensorEventQueue interface
    void dataReceived(const ASensorEvent &event) override;
};

#endif // ANDROIDLIGHT_H
