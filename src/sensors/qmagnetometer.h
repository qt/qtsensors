/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMAGNETOMETER_H
#define QMAGNETOMETER_H

#include "qsensor.h"

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

QT_MODULE(QtSensors)

class QMagnetometerReadingPrivate;

class Q_SENSORS_EXPORT QMagnetometerReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(qreal z READ z)
    Q_PROPERTY(qreal calibrationLevel READ calibrationLevel)
    DECLARE_READING(QMagnetometerReading)
public:
    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);

    qreal calibrationLevel() const;
    void setCalibrationLevel(qreal calibrationLevel);
};

class Q_SENSORS_EXPORT QMagnetometerFilter : public QSensorFilter
{
public:
    virtual bool filter(QMagnetometerReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QMagnetometerReading*>(reading)); }
};

class Q_SENSORS_EXPORT QMagnetometer : public QSensor
{
    Q_OBJECT
#ifdef Q_QDOC
    Q_PROPERTY(bool returnGeoValues)
#endif
public:
    explicit QMagnetometer(QObject *parent = 0);
    virtual ~QMagnetometer();
    QMagnetometerReading *reading() const { return static_cast<QMagnetometerReading*>(QSensor::reading()); }
    static char const * const type;

private:
    Q_DISABLE_COPY(QMagnetometer)
};

QT_END_NAMESPACE
QT_END_HEADER

#endif

