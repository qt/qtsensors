// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTEMPLATEGESTUREPLUGIN_H
#define QTEMPLATEGESTUREPLUGIN_H

#include <QObject>
#include <QStringList>

#include <qsensorgestureplugininterface.h>

class QTemplateGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface" FILE "plugin.json")
    Q_INTERFACES(QSensorGesturePluginInterface)
public:
    explicit QTemplateGesturePlugin();
    ~QTemplateGesturePlugin();

    QList<QSensorGestureRecognizer *> createRecognizers() override;

    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override { return "TemplateGestures"; }
};

#endif // QTEMPLATEGESTUREPLUGIN_H
