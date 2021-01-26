/****************************************************************************
**
** Copyright (C) 2016 Alexander Volkov <a.volkov@rusbitech.ru>
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

#ifndef IIOSENSORPROXY_LIGHTSENSOR_H
#define IIOSENSORPROXY_LIGHTSENSOR_H

#include "iiosensorproxysensorbase.h"

#include <qlightsensor.h>

class NetHadessSensorProxyInterface;

class IIOSensorProxyLightSensor : public IIOSensorProxySensorBase
{
    Q_OBJECT
public:
    static char const * const id;

    IIOSensorProxyLightSensor(QSensor *sensor);
    ~IIOSensorProxyLightSensor();

    void start() override;
    void stop() override;

protected:
    void updateProperties(const QVariantMap &changedProperties) override;

private:
    void updateLightLevel(double lux);

    QLightReading m_reading;
    NetHadessSensorProxyInterface *m_sensorProxyInterface;
};

#endif // IIOSENSORPROXY_LIGHTSENSOR_H
