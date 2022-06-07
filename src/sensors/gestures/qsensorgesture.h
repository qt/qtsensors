// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSENSORGESTURE_H
#define QSENSORGESTURE_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtSensors/qsensorsglobal.h>

#include <QtCore/QList>
#include <QtCore/QMap>

#include <QtCore/qmetatype.h>

QT_BEGIN_NAMESPACE

class QSensorGesturePrivate;

class Q_SENSORS_EXPORT QSensorGesture : public QObject
{
    //Do not use Q_OBJECT here
public:
    explicit QSensorGesture(const QStringList &ids, QObject *parent = nullptr);
    ~QSensorGesture();

    bool isActive();

    QStringList validIds() const;
    QStringList invalidIds() const;

    QStringList gestureSignals() const;

    void startDetection();
    void stopDetection();

    // Pretend to be a Q_OBJECT
    const QMetaObject *metaObject() const override;
    int qt_metacall(QMetaObject::Call, int, void **) override;

private:
    QSensorGesturePrivate * d_ptr;

Q_SIGNALS:
    // these signals are created at runtime, along with
    // gesture recognizer specific signals.
     void detected(QString);
};

QT_END_NAMESPACE


#endif // QSENSORGESTURE_H
