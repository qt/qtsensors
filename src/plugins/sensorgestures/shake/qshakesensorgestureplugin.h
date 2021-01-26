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

#ifndef QSHAKESENSORGESTUREPLUGIN_H
#define QSHAKESENSORGESTUREPLUGIN_H

#include <QObject>
#include <QStringList>

#include <QtSensors/qsensorgestureplugininterface.h>

class QShakeSensorGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface")
    Q_INTERFACES(QSensorGesturePluginInterface)

public:
    explicit QShakeSensorGesturePlugin();
    ~QShakeSensorGesturePlugin();

    QList <QSensorGestureRecognizer *> createRecognizers() override;

    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override { return "ShakeGestures"; }
};

#endif // QSHAKESENSORGESTUREPLUGIN_H
