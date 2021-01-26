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

#ifndef IOSPROXIMITYSENSOR_H
#define IOSPROXIMITYSENSOR_H

#include <qsensorbackend.h>
#include <qproximitysensor.h>

@class ProximitySensorCallback;

QT_BEGIN_NAMESPACE

class IOSProximitySensor : public QSensorBackend
{
public:
    static char const * const id;

    explicit IOSProximitySensor(QSensor *sensor);
    ~IOSProximitySensor();

    void start() override;
    void stop() override;

    void proximityChanged(bool close);
    static bool available();

private:
    ProximitySensorCallback *m_proximitySensorCallback;
    QProximityReading m_reading;

    static int s_startCount;
};
QT_END_NAMESPACE

#endif // IOSPROXIMITYSENSOR_H

