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

#include "iiosensorproxysensorbase.h"
#include "sensorproxy_interface.h"
#include "properties_interface.h"

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusServiceWatcher>
#include <QtDBus/QDBusConnectionInterface>

#include <time.h>

quint64 IIOSensorProxySensorBase::produceTimestamp()
{
    struct timespec tv;
    int ok;

#ifdef CLOCK_MONOTONIC_RAW
    ok = clock_gettime(CLOCK_MONOTONIC_RAW, &tv);
    if (ok != 0)
#endif
    ok = clock_gettime(CLOCK_MONOTONIC, &tv);
    Q_ASSERT(ok == 0);

    quint64 result = (tv.tv_sec * 1000000ULL) + (tv.tv_nsec * 0.001); // scale to microseconds
    return result;
}

IIOSensorProxySensorBase::IIOSensorProxySensorBase(const QString& dbusPath, const QString dbusIface, QSensor *sensor)
    : QSensorBackend(sensor)
    , m_dbusInterface(dbusIface)
{
    QDBusServiceWatcher *watcher = new QDBusServiceWatcher(serviceName(), QDBusConnection::systemBus(),
                                                           QDBusServiceWatcher::WatchForRegistration |
                                                           QDBusServiceWatcher::WatchForUnregistration, this);
    connect(watcher, SIGNAL(serviceRegistered(QString)),
            this, SLOT(serviceRegistered()));
    connect(watcher, SIGNAL(serviceUnregistered(QString)),
            this, SLOT(serviceUnregistered()));

    m_serviceRunning = QDBusConnection::systemBus().interface()->isServiceRegistered(serviceName());

    m_propertiesInterface = new OrgFreedesktopDBusPropertiesInterface(serviceName(), dbusPath,
                                                                      QDBusConnection::systemBus(), this);
    connect(m_propertiesInterface, SIGNAL(PropertiesChanged(QString,QVariantMap,QStringList)),
            this, SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
}

IIOSensorProxySensorBase::~IIOSensorProxySensorBase()
{
}

QString IIOSensorProxySensorBase::serviceName() const
{
    return QLatin1String("net.hadess.SensorProxy");
}

void IIOSensorProxySensorBase::serviceRegistered()
{
    m_serviceRunning = true;
}

void IIOSensorProxySensorBase::serviceUnregistered()
{
    m_serviceRunning = false;
    sensorStopped();
}

void IIOSensorProxySensorBase::propertiesChanged(const QString &interface,
                                                 const QVariantMap &changedProperties,
                                                 const QStringList &/*invalidatedProperties*/)
{
    if (interface == m_dbusInterface)
        updateProperties(changedProperties);
}
