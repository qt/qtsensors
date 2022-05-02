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

#ifndef QSENSORGESTUREPLUGININTERFACE_H
#define QSENSORGESTUREPLUGININTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QtGlobal>
#include <QtCore/qplugin.h>
#include <QtSensors/qsensorgesture.h>
#include <QtSensors/qsensorgesturerecognizer.h>

QT_BEGIN_NAMESPACE

class QSensorGestureRecognizer;

class Q_SENSORS_EXPORT QSensorGesturePluginInterface
{
public:
    QSensorGesturePluginInterface();
    virtual ~QSensorGesturePluginInterface();
    virtual QList <QSensorGestureRecognizer *> createRecognizers() = 0;
    virtual QStringList supportedIds() const = 0;
    virtual QString name() const = 0;
};

Q_DECLARE_INTERFACE(QSensorGesturePluginInterface, "org.qt-project.QSensorGesturePluginInterface")

QT_END_NAMESPACE

#endif // QSENSORGESTUREPLUGININTERFACE_H
