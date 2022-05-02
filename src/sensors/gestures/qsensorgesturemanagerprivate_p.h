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

#ifndef QSENSORGESTUREMANAGERPRIVATE_P_H
#define QSENSORGESTUREMANAGERPRIVATE_P_H

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
#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QSharedPointer>
#include <QPluginLoader>

#include "qsensorgesture.h"
#include "qsensorgesturerecognizer.h"

QT_BEGIN_NAMESPACE

class QFactoryLoader;

class QSensorGestureManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QSensorGestureManagerPrivate(QObject *parent = 0);
    ~QSensorGestureManagerPrivate();

    QMap<QString, QSensorGestureRecognizer *> registeredSensorGestures;

    QList <QObject *> plugins;

    QFactoryLoader *loader;
    void loadPlugins();
    bool loadRecognizer(const QString &id);

    QSensorGestureRecognizer *sensorGestureRecognizer(const QString &id);

    bool registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer);
    QStringList gestureIds();
    QStringList knownIds;
    void initPlugin(QObject *o);

    static QSensorGestureManagerPrivate * instance();
Q_SIGNALS:
        void newSensorGestureAvailable();
};

QT_END_NAMESPACE

#endif // QSENSORGESTUREMANAGERPRIVATE_P_H
