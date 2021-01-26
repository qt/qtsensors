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


#ifndef SENSORFWGYROSCOPE_H
#define SENSORFWGYROSCOPE_H

#include "sensorfwsensorbase.h"
#include <QtSensors/qgyroscope.h>
#include <datatypes/xyz.h>
#include <gyroscopesensor_i.h>




class SensorfwGyroscope : public SensorfwSensorBase
{
    Q_OBJECT

public:
    static char const * const id;
    SensorfwGyroscope(QSensor *sensor);
protected:
    bool doConnect() override;
    QString sensorName() const override;
    qreal correctionFactor() const override;
    void start() override;
    virtual void init();

private:
    QGyroscopeReading m_reading;
    bool m_initDone;
    static const float MILLI;
private slots:
    void slotDataAvailable(const XYZ& data);
    void slotFrameAvailable(const QVector<XYZ>&);

};


#endif // sensorfwGYROSCOPE_H
