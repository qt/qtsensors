// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef SENSORFWPROXIMITYSENSOR_H
#define SENSORFWPROXIMITYSENSOR_H

#include "sensorfwsensorbase.h"
#include <QtSensors/qproximitysensor.h>

#include <proximitysensor_i.h>



class SensorfwProximitySensor : public SensorfwSensorBase
{
    Q_OBJECT

public:
    static char const * const id;
    SensorfwProximitySensor(QSensor *sensor);
protected:
    bool doConnect() override;
    QString sensorName() const override;
    void start() override;
    virtual void init();

private:
    QProximityReading m_reading;
    bool m_initDone;
    bool m_exClose;
    bool firstRun;

private slots:
    void slotReflectanceDataAvailable(const Proximity& data);
};

#endif
