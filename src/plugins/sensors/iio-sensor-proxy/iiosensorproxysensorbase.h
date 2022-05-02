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

#ifndef IIOSENSORPROXY_SENSORBASE_H
#define IIOSENSORPROXY_SENSORBASE_H

#include <qsensorbackend.h>

class OrgFreedesktopDBusPropertiesInterface;

class IIOSensorProxySensorBase : public QSensorBackend
{
    Q_OBJECT
public:
    static char const * const id;

    IIOSensorProxySensorBase(const QString &dbusPath, const QString dbusIface, QSensor *sensor);
    ~IIOSensorProxySensorBase();

    bool isServiceRunning() const { return m_serviceRunning; }
    QString serviceName() const;

protected:
    static quint64 produceTimestamp();
    virtual void updateProperties(const QVariantMap &changedProperties) = 0;

private slots:
    void serviceRegistered();
    void serviceUnregistered();
    void propertiesChanged(const QString &interface, const QVariantMap &changedProperties,
                           const QStringList &invalidatedProperties);

private:
    bool m_serviceRunning;
    OrgFreedesktopDBusPropertiesInterface *m_propertiesInterface;
    QString m_dbusInterface;
};

#endif // IIOSENSORPROXY_SENSORBASE_H
