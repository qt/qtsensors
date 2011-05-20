/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QROTATIONSENSOR_H
#define QROTATIONSENSOR_H

#include "qsensor.h"

QT_BEGIN_NAMESPACE

class QRotationReadingPrivate;

class Q_SENSORS_EXPORT QRotationReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(qreal z READ z)
    DECLARE_READING(QRotationReading)
public:
    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);
};

class Q_SENSORS_EXPORT QRotationFilter : public QSensorFilter
{
public:
    virtual bool filter(QRotationReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QRotationReading*>(reading)); }
};

class Q_SENSORS_EXPORT QRotationSensor : public QSensor
{
    Q_OBJECT
#ifdef Q_QDOC
    Q_PROPERTY(bool hasZ)
#endif
public:
    explicit QRotationSensor(QObject *parent = 0) : QSensor(QRotationSensor::type, parent) {}
    virtual ~QRotationSensor() {}
    QRotationReading *reading() const { return static_cast<QRotationReading*>(QSensor::reading()); }
    static char const * const type;
};

QT_END_NAMESPACE

#endif

