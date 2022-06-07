// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTESTSENSORGESTUREDUPPLUGIN_H
#define QTESTSENSORGESTUREDUPPLUGIN_H

#include <QObject>
#include <qsensorgestureplugininterface.h>

class QTestSensorGestureDupPlugin :  public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface")
    Q_INTERFACES(QSensorGesturePluginInterface)

public:
    explicit QTestSensorGestureDupPlugin();
    ~QTestSensorGestureDupPlugin();


    QList<QSensorGestureRecognizer *> createRecognizers() override;

    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override;

    QList<QSensorGestureRecognizer*> recognizers() const;

    QList<QSensorGestureRecognizer*> recognizersList;

};



#endif // QTESTSENSORGESTUREDUPPLUGIN_H
