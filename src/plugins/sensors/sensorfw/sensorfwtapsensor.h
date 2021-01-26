/****************************************************************************
**
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
#ifndef SENSORFWTAPSENSOR_H
#define SENSORFWTAPSENSOR_H

#include "sensorfwsensorbase.h"
#include <QtSensors/qtapsensor.h>

#include <tapsensor_i.h>
#include <datatypes/tap.h>



class SensorfwTapSensor : public SensorfwSensorBase
{
    Q_OBJECT

public:
    static char const * const id;
    SensorfwTapSensor(QSensor *sensor);
protected:
    bool doConnect() override;
    void start() override;
    QString sensorName() const override;
    virtual void init();
private:
    QTapReading m_reading;
    bool m_initDone;
    bool m_isDoubleTapSensor;
    bool m_isOnceStarted;
private slots:
    void slotDataAvailable(const Tap&);
};

#endif
