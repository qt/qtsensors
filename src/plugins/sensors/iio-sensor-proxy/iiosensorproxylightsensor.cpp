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

#include "iiosensorproxylightsensor.h"
#include "sensorproxy_interface.h"

#include <QtDBus/QDBusPendingReply>

char const * const IIOSensorProxyLightSensor::id("iio-sensor-proxy.lightsensor");

static inline QString dbusPath() { return QStringLiteral("/net/hadess/SensorProxy"); }

IIOSensorProxyLightSensor::IIOSensorProxyLightSensor(QSensor *sensor)
    : IIOSensorProxySensorBase(dbusPath(), NetHadessSensorProxyInterface::staticInterfaceName(), sensor)
{
    setReading<QLightReading>(&m_reading);
    m_sensorProxyInterface = new NetHadessSensorProxyInterface(serviceName(), dbusPath(),
                                                               QDBusConnection::systemBus(), this);
}

IIOSensorProxyLightSensor::~IIOSensorProxyLightSensor()
{
}

void IIOSensorProxyLightSensor::start()
{
    if (isServiceRunning()) {
        if (m_sensorProxyInterface->hasAmbientLight()
            && m_sensorProxyInterface->lightLevelUnit() == QLatin1String("lux")) {
            QDBusPendingReply<> reply = m_sensorProxyInterface->ClaimLight();
            reply.waitForFinished();
            if (!reply.isError()) {
                updateLightLevel(m_sensorProxyInterface->lightLevel());
                return;
            }
        }
    }
    sensorStopped();
}

void IIOSensorProxyLightSensor::stop()
{
    if (isServiceRunning()) {
        QDBusPendingReply<> reply = m_sensorProxyInterface->ReleaseLight();
        reply.waitForFinished();
    }
    sensorStopped();
}

void IIOSensorProxyLightSensor::updateProperties(const QVariantMap &changedProperties)
{
    if (changedProperties.contains("LightLevel")) {
        double lux = changedProperties.value("LightLevel").toDouble();
        updateLightLevel(lux);
    }
}

void IIOSensorProxyLightSensor::updateLightLevel(double lux)
{
    m_reading.setLux(lux);
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}
