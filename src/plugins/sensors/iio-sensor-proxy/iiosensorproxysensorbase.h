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
