// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef SENSORFWIRPROXIMITYSENSOR_H
#define SENSORFWIRPROXIMITYSENSOR_H

#include "sensorfwsensorbase.h"
#include <QtSensors/qirproximitysensor.h>
#include <proximitysensor_i.h>


class SensorfwIrProximitySensor : public SensorfwSensorBase
{
    Q_OBJECT

public:
    static char const * const id;

    SensorfwIrProximitySensor(QSensor *sensor);
protected:
    bool doConnect() override;
    QString sensorName() const override;
    void start() override;
    virtual void init();
private:
    QIRProximityReading m_reading;
    bool m_initDone;
    int rangeMax;

private slots:
    void slotDataAvailable(const Proximity& proximity);
};

#endif
