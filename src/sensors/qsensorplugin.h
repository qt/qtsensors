/****************************************************************************
**
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

#ifndef QSENSORPLUGIN_H
#define QSENSORPLUGIN_H

#include <QtSensors/qsensorsglobal.h>

#include <QtCore/qplugin.h>

QT_BEGIN_NAMESPACE

class Q_SENSORS_EXPORT QSensorPluginInterface
{
public:
    virtual void registerSensors() = 0;
protected:
    virtual ~QSensorPluginInterface();
};

class Q_SENSORS_EXPORT QSensorChangesInterface
{
public:
    virtual void sensorsChanged() = 0;
protected:
    virtual ~QSensorChangesInterface();
};

Q_DECLARE_INTERFACE(QSensorPluginInterface, "com.qt-project.Qt.QSensorPluginInterface/1.0")
Q_DECLARE_INTERFACE(QSensorChangesInterface, "com.qt-project.Qt.QSensorChangesInterface/5.0")

QT_END_NAMESPACE

#endif

