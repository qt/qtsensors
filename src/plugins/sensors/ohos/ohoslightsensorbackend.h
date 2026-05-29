// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSLIGHTBACKEND_H
#define OHOSLIGHTBACKEND_H

#include <QtSensors/qlightsensor.h>
#include <ohossensorbackendbase.h>
#include <ohossensorsmanager.h>

class OhosLightSensorBackend : public OhosSensorBackendBase<QLightReading>
{
public:
    OhosLightSensorBackend(QSensor *sensor);

protected:
    void processSensorData(const OhosSensorData &sensorData) override;
};

#endif
