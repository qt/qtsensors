// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTESTSENSORGESTUREPLUGIN_P_H
#define QTESTSENSORGESTUREPLUGIN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QObject>
#include <qsensorgestureplugininterface.h>

class QTestSensorGesturePlugin : public QObject, public QSensorGesturePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QSensorGesturePluginInterface")
    Q_INTERFACES(QSensorGesturePluginInterface)

public:
    explicit QTestSensorGesturePlugin();
    ~QTestSensorGesturePlugin();

    QList<QSensorGestureRecognizer *> createRecognizers() override;

//    QStringList gestureSignals() const;
    QStringList supportedIds() const override;
    QString name() const override;

    QList<QSensorGestureRecognizer*> recognizers() const;

    QList<QSensorGestureRecognizer*> recognizersList;

};



#endif // QTESTSENSORGESTUREPLUGIN_H
