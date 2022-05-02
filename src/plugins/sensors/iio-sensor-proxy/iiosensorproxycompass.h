/****************************************************************************
**
** Copyright (C) 2016 Alexander Volkov <a.volkov@rusbitech.ru>
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

#ifndef IIOSENSORPROXY_COMPASS_H
#define IIOSENSORPROXY_COMPASS_H

#include "iiosensorproxysensorbase.h"

#include <qcompass.h>

class NetHadessSensorProxyCompassInterface;

class IIOSensorProxyCompass : public IIOSensorProxySensorBase
{
    Q_OBJECT
public:
    static char const * const id;

    IIOSensorProxyCompass(QSensor *sensor);
    ~IIOSensorProxyCompass();

    void start() override;
    void stop() override;

protected:
    void updateProperties(const QVariantMap &changedProperties) override;

private:
    void updateAzimuth(double azimuth);

    QCompassReading m_reading;
    NetHadessSensorProxyCompassInterface *m_sensorProxyInterface;
};

#endif // IIOSENSORPROXY_COMPASS_H
