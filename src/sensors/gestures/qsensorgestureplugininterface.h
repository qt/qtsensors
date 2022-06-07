// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

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
