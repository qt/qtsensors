// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QObject>
#include <qsensorgestureplugininterface.h>
#include <qsensorgesturerecognizer.h>

class MySensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
 public:

    MySensorGestureRecognizer(QObject *parent = 0);
    ~MySensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
// all signals will get exported to QSensorGesture
    void mySignal();
};

class MySensorGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "com.Nokia.QSensorGesturePluginInterface" FILE "plugin.json")
    Q_INTERFACES(QSensorGesturePluginInterface)
public:

    explicit MySensorGesturePlugin();
    ~MySensorGesturePlugin();

    QList<QSensorGestureRecognizer *> createRecognizers() override;
    QStringList supportedIds() const override;
    QString name() const override { return "MyGestures"; }
};

#endif
