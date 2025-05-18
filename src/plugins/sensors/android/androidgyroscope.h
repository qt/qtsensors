// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef ANDROIDGYROSCOPE_H
#define ANDROIDGYROSCOPE_H

#include <qgyroscope.h>

#include "sensoreventqueue.h"

class AndroidGyroscope : public SensorEventQueue<QGyroscopeReading>
{
public:
    AndroidGyroscope(int type, QSensor *sensor, QObject *parent = nullptr);

protected:
    // SensorEventQueue interface
    void dataReceived(const ASensorEvent &event) override;
};

#endif // ANDROIDGYROSCOPE_H
