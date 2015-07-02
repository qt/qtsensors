/****************************************************************************
**
** Copyright (C) 2015 Alexander Volkov <a.volkov@rusbitech.ru>
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
