/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
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
#ifndef QHOLSTERSENSOR_H
#define QHOLSTERSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QHolsterReadingPrivate;

class Q_SENSORS_EXPORT QHolsterReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool holstered READ holstered)
    DECLARE_READING(QHolsterReading)
public:
    bool holstered() const;
    void setHolstered(bool holstered);
};

class Q_SENSORS_EXPORT QHolsterFilter : public QSensorFilter
{
public:
    virtual bool filter(QHolsterReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QHolsterSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QHolsterSensor(QObject *parent = Q_NULLPTR);
    ~QHolsterSensor();
    QHolsterReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QHolsterSensor)
};

QT_END_NAMESPACE

#endif
