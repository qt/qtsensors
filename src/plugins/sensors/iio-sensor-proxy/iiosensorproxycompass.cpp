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

#include "iiosensorproxycompass.h"
#include "compass_interface.h"

#include <QtDBus/QDBusPendingReply>

char const * const IIOSensorProxyCompass::id("iio-sensor-proxy.compass");

static inline QString dbusPath() { return QStringLiteral("/net/hadess/SensorProxy/Compass"); }

IIOSensorProxyCompass::IIOSensorProxyCompass(QSensor *sensor)
    : IIOSensorProxySensorBase(dbusPath(), NetHadessSensorProxyCompassInterface::staticInterfaceName(), sensor)
{
    setReading<QCompassReading>(&m_reading);
    m_sensorProxyInterface = new NetHadessSensorProxyCompassInterface(serviceName(), dbusPath(),
                                                                      QDBusConnection::systemBus(), this);
}

IIOSensorProxyCompass::~IIOSensorProxyCompass()
{
}

void IIOSensorProxyCompass::start()
{
    if (isServiceRunning()) {
        if (m_sensorProxyInterface->hasCompass()) {
            QDBusPendingReply<> reply = m_sensorProxyInterface->ClaimCompass();
            reply.waitForFinished();
            if (!reply.isError()) {
                double azimuth = m_sensorProxyInterface->compassHeading();
                updateAzimuth(azimuth);
                return;
            }
        }
    }
    sensorStopped();
}

void IIOSensorProxyCompass::stop()
{
    if (isServiceRunning()) {
        QDBusPendingReply<> reply = m_sensorProxyInterface->ReleaseCompass();
        reply.waitForFinished();
    }
    sensorStopped();
}

void IIOSensorProxyCompass::updateProperties(const QVariantMap &changedProperties)
{
    if (changedProperties.contains("CompassHeading")) {
        double azimuth = changedProperties.value("CompassHeading").toDouble();
        updateAzimuth(azimuth);
    }
}

void IIOSensorProxyCompass::updateAzimuth(double azimuth)
{
    m_reading.setAzimuth(azimuth);
    m_reading.setTimestamp(produceTimestamp());
    newReadingAvailable();
}
