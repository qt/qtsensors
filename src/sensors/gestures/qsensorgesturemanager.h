// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSENSORGESTUREMANAGER_P_H
#define QSENSORGESTUREMANAGER_P_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include <QtSensors/qsensorgesture.h>
#include <QtSensors/qsensorgesturerecognizer.h>

QT_BEGIN_NAMESPACE

class QSensorGestureManagerPrivate;
class Q_SENSORS_EXPORT QSensorGestureManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QSensorGestureManager)

public:
    explicit QSensorGestureManager(QObject *parent = nullptr);

    ~QSensorGestureManager();

     bool registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer);

    QStringList gestureIds() const;
    QStringList recognizerSignals(const QString &recognizerId) const;

    static QSensorGestureRecognizer *sensorGestureRecognizer(const QString &id);

Q_SIGNALS:
    void newSensorGestureAvailable();

};


QT_END_NAMESPACE

#endif // QSENSORGESTUREMANAGER_P_H
