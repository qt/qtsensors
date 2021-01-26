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
#ifndef QALTIMETER_H
#define QALTIMETER_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QAltimeterReadingPrivate;

class Q_SENSORS_EXPORT QAltimeterReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal altitude READ altitude)
    DECLARE_READING(QAltimeterReading)
public:
    qreal altitude() const;
    void setAltitude(qreal altitude);
};

class Q_SENSORS_EXPORT QAltimeterFilter : public QSensorFilter
{
public:
    virtual bool filter(QAltimeterReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QAltimeter : public QSensor
{
    Q_OBJECT
public:
    explicit QAltimeter(QObject *parent = Q_NULLPTR);
    ~QAltimeter();
    QAltimeterReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QAltimeter)
};

QT_END_NAMESPACE

#endif
