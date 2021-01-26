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

#include "linuxsysaccelerometer.h"

#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>

#include <QtCore/QFile>
#include <QtCore/QDebug>

class LinuxSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    void registerSensors() override
    {
        QString path = QString::fromLatin1(qgetenv("QT_ACCEL_FILEPATH"));
        if (!path.isEmpty() && !QSensorManager::isBackendRegistered(QAccelerometer::type, LinuxSysAccelerometer::id))
            QSensorManager::registerBackend(QAccelerometer::type, LinuxSysAccelerometer::id, this);
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == LinuxSysAccelerometer::id)
            return new LinuxSysAccelerometer(sensor);

        return 0;
    }
};

#include "main.moc"

