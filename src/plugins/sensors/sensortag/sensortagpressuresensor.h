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

#ifndef SENSORTAGPRESSURESENSOR_H
#define SENSORTAGPRESSURESENSOR_H

#include "sensortagbase.h"
#include <QObject>
#include <QPressureReading>

class SensorTagPressureSensor : public SensorTagBase
{
    Q_OBJECT
public:
    SensorTagPressureSensor(QSensor *sensor);
    static char const * const id;

protected:
    void start() override;
    void stop() override;

private slots:
    void pressureChanged(qreal value);
private:
    QPressureReading m_reading;
};

#endif // SENSORTAGPRESSURESENSOR_H
