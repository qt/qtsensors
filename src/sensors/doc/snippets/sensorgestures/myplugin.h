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
