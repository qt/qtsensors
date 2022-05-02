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

#ifndef SENSORFWORIENTATIONSENSOR_H
#define SENSORFWORIENTATIONSENSOR_H

#include "sensorfwsensorbase.h"
#include <QtSensors/qorientationsensor.h>

#include <orientationsensor_i.h>



class SensorfwOrientationSensor : public SensorfwSensorBase
{
    Q_OBJECT

public:
    static char const * const id;
    SensorfwOrientationSensor(QSensor *sensor);
protected:
    bool doConnect() override;
    QString sensorName() const override;
    void start() override;
    virtual void init();
private:
    QOrientationReading m_reading;
    static QOrientationReading::Orientation getOrientation(int orientation);
    bool m_initDone;

private slots:
    void slotDataAvailable(const Unsigned& orientation);
};

#endif
