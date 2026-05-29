// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSACCELEROMETERBACKEND_H
#define OHOSACCELEROMETERBACKEND_H

#include <QtSensors/qaccelerometer.h>
#include <ohossensorbackendbase.h>
#include <ohossensorsmanager.h>

class OhosAccelerometerBackend : public OhosSensorBackendBase<QAccelerometerReading>
{
public:
    OhosAccelerometerBackend(QSensor *sensor);

protected:
    void processSensorData(const OhosSensorData &sensorData) override;
};

#endif
