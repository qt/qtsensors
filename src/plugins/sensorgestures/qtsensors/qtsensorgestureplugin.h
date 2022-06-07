// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTSENSORGESTURESPLUGIN_H
#define QTSENSORGESTURESPLUGIN_H

#include <QObject>
#include <QStringList>

#include <QtSensors/qsensorgestureplugininterface.h>

QT_BEGIN_NAMESPACE

class QtSensorGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface")
    Q_INTERFACES(QSensorGesturePluginInterface)

public:
    explicit QtSensorGesturePlugin();
    ~QtSensorGesturePlugin();
    QList <QSensorGestureRecognizer *> createRecognizers() override;

    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override { return "QtSensorGestures"; }

};

QT_END_NAMESPACE
#endif // QTSENSORGESTURESPLUGIN_H
