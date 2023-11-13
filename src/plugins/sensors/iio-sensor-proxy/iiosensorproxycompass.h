// Copyright (C) 2016 Alexander Volkov <a.volkov@rusbitech.ru>
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

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
