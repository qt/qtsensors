/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSENSORGESTUREMANAGER_P_H
#define QSENSORGESTUREMANAGER_P_H

#include <QObject>
#include <QStringList>

#include "qsensorgesture.h"
#include "qsensorgesturerecognizer.h"

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QSensorGestureManagerPrivate;
class Q_SENSORS_EXPORT QSensorGestureManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QSensorGestureManager)

public:
    explicit QSensorGestureManager(QObject *parent = 0);

    ~QSensorGestureManager();

     bool registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer);

    QStringList gestureIds() const;
    QStringList recognizerSignals(const QString &recognizerId) const;

    static QSensorGestureRecognizer *sensorGestureRecognizer(const QString &id);

signals:
    void newSensorGestureAvailable();

};


QT_END_NAMESPACE
QT_END_HEADER

#define REGISTER_STATIC_PLUGIN_V2(pluginname) \
    QT_PREPEND_NAMESPACE(QObject) *qt_plugin_instance_##pluginname() Q_PLUGIN_INSTANCE(pluginname)\
    Q_IMPORT_PLUGIN(pluginname)

#endif // QSENSORGESTUREMANAGER_P_H
