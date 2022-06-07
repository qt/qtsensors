// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef QCOUNTERGESTUREPLUGIN_H
#define QCOUNTERGESTUREPLUGIN_H

#include <QObject>
#include <QStringList>

#include <qsensorgestureplugininterface.h>

class QCounterGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface")
    Q_INTERFACES(QSensorGesturePluginInterface)

public:
    explicit QCounterGesturePlugin();
    ~QCounterGesturePlugin();

    QList<QSensorGestureRecognizer *> createRecognizers() override;

    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override { return "CounterGestures"; }
};

#endif // QCOUNTERGESTUREPLUGIN_H
