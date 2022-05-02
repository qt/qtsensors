/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef GENERICALSSENSOR_H
#define GENERICALSSENSOR_H

#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qlightsensor.h>
#include <QtSensors/qambientlightsensor.h>

class genericalssensor : public QSensorBackend, public QLightFilter
{
public:
    static char const * const id;

    genericalssensor(QSensor *sensor);

    void start() override;
    void stop() override;

    bool filter(QLightReading *reading) override;

private:
    QAmbientLightReading m_reading;
    QLightSensor *lightSensor;
};

#endif

