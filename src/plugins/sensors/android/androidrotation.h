// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef ANDROIDROTATION_H
#define ANDROIDROTATION_H

#include <qrotationsensor.h>

#include "sensoreventqueue.h"

class AndroidRotation : public SensorEventQueue<QRotationReading>
{
public:
    AndroidRotation(int type, QSensor *sensor, QObject *parent = nullptr);

protected:
    // SensorEventQueue interface
    void dataReceived(const ASensorEvent &event) override;
};

#endif // ANDROIDROTATION_H
