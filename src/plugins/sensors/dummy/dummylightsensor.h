// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef DUMMYLIGHTSENSOR_H
#define DUMMYLIGHTSENSOR_H

#include "dummycommon.h"
#include <qambientlightsensor.h>

class dummylightsensor : public dummycommon
{
public:
    static char const * const id;

    dummylightsensor(QSensor *sensor);

    void poll() override;
private:
    QAmbientLightReading m_reading;
};

#endif

