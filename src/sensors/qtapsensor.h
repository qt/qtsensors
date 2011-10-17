/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTAPSENSOR_H
#define QTAPSENSOR_H

#include "qsensor.h"

QT_BEGIN_NAMESPACE

class QTapReadingPrivate;

class Q_SENSORS_EXPORT_TEMP QTapReading : public QSensorReading
{
    Q_OBJECT
    Q_ENUMS(TapDirection)
    Q_PROPERTY(TapDirection tapDirection READ tapDirection)
    Q_PROPERTY(bool doubleTap READ isDoubleTap)
    DECLARE_READING(QTapReading)
public:
    enum TapDirection {
        Undefined = 0,
        X      = 0x0001,
        Y      = 0x0002,
        Z      = 0x0004,
        X_Pos  = 0x0011,
        Y_Pos  = 0x0022,
        Z_Pos  = 0x0044,
        X_Neg  = 0x0101,
        Y_Neg  = 0x0202,
        Z_Neg  = 0x0404,
        X_Both = 0x0111,
        Y_Both = 0x0222,
        Z_Both = 0x0444
    };

    TapDirection tapDirection() const;
    void setTapDirection(TapDirection tapDirection);

    bool isDoubleTap() const;
    void setDoubleTap(bool doubleTap);
};

class Q_SENSORS_EXPORT_TEMP QTapFilter : public QSensorFilter
{
public:
    virtual bool filter(QTapReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QTapReading*>(reading)); }
};

class Q_SENSORS_EXPORT_TEMP QTapSensor : public QSensor
{
    Q_OBJECT
#ifdef Q_QDOC
    Q_PROPERTY(bool returnDoubleTapEvents)
#endif
public:
    explicit QTapSensor(QObject *parent = 0) : QSensor(QTapSensor::type, parent) {}
    virtual ~QTapSensor() {}
    QTapReading *reading() const { return static_cast<QTapReading*>(QSensor::reading()); }
    static char const * const type;
};

QT_END_NAMESPACE

#endif

