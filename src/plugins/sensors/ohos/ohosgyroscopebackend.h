// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSGYROSCOPEBACKEND_H
#define OHOSGYROSCOPEBACKEND_H

#include <QtSensors/qgyroscope.h>
#include <ohossensorbackendbase.h>
#include <ohossensorsmanager.h>

class OhosGyroscopeBackend : public OhosSensorBackendBase<QGyroscopeReading>
{
public:
    OhosGyroscopeBackend(QSensor *sensor);

protected:
    void processSensorData(const OhosSensorData &sensorData) override;
};

#endif
