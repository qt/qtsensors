// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSENSORGESTURERECOGNIZER_H
#define QSENSORGESTURERECOGNIZER_H

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QStringList>

#include <QtSensors/qsensorgesture.h>

QT_BEGIN_NAMESPACE

class QSensorGestureRecognizerPrivate;
class Q_SENSORS_EXPORT QSensorGestureRecognizer : public QObject
{
    Q_OBJECT
public:
    explicit QSensorGestureRecognizer(QObject *parent = nullptr);
    virtual ~QSensorGestureRecognizer();

    virtual QString id() const = 0;

    virtual bool isActive() = 0;

    void startBackend();
    void stopBackend();
    void createBackend();

    QStringList gestureSignals() const;

Q_SIGNALS:
    void detected(const QString &);

protected:
    virtual void create() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

private:
        QSensorGestureRecognizerPrivate * d_ptr;
};

QT_END_NAMESPACE

#endif // QSENSORGESTURERECOGNIZER_H
