/****************************************************************************
**
** Copyright (C) 2017 Lorn Potter
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef SENSORTAGACCELEROMETER_H
#define SENSORTAGACCELEROMETER_H

#include "sensortagbase.h"
#include <QtSensors/qaccelerometer.h>

class SensorTagAccelerometer : public SensorTagBase
{
    Q_OBJECT

public:
    static char const * const id;
    SensorTagAccelerometer(QSensor *sensor);
protected:
    void start() override;
    void stop() override;
    virtual void init();

private:
    QAccelerometerReading m_reading;
    bool m_initDone = false;

private slots:
    void slotDataAvailable(const QAccelerometerReading &data);
};

#endif
// SENSORTAGACCELEROMETER_H
