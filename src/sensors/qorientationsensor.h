/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef QORIENTATIONSENSOR_H
#define QORIENTATIONSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QOrientationReadingPrivate;

class Q_SENSORS_EXPORT QOrientationReading : public QSensorReading
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(Orientation orientation READ orientation)
    DECLARE_READING(QOrientationReading)
public:
    enum Orientation {
        Undefined = 0,
        TopUp,
        TopDown,
        LeftUp,
        RightUp,
        FaceUp,
        FaceDown
    };

    Orientation orientation() const;
    void setOrientation(Orientation orientation);
};

class Q_SENSORS_EXPORT QOrientationFilter : public QSensorFilter
{
public:
    virtual bool filter(QOrientationReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QOrientationSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QOrientationSensor(QObject *parent = Q_NULLPTR);
    virtual ~QOrientationSensor();
    QOrientationReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QOrientationSensor)
};

QT_END_NAMESPACE

#endif

