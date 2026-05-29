// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSROTATIONSENSORBACKEND_H
#define OHOSROTATIONSENSORBACKEND_H

#include <QtSensors/qrotationsensor.h>
#include <ohossensorbackendbase.h>
#include <ohossensorsmanager.h>

class OhosRotationSensorBackend : public OhosSensorBackendBase<QRotationReading>
{
public:
    OhosRotationSensorBackend(QSensor *sensor);

protected:
    void processSensorData(const OhosSensorData &sensorData) override;
};

#endif
