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
