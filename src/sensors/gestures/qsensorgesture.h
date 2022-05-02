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
