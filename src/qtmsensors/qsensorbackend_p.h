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

#ifndef QTM_QSENSORBACKEND_P_H
#define QTM_QSENSORBACKEND_P_H

#include <QObject>
#include "qtmsensorsglobal.h"

QT_BEGIN_NAMESPACE
QTM_BEGIN_NAMESPACE

class QSensor;
class QSensorReading;

class QTM_SENSORS_EXPORT QSensorBackend : public QObject
{
    Q_OBJECT
public:
    QSensorBackend(QSensor *sensor);
    virtual ~QSensorBackend();

    virtual void start() = 0;
    virtual void stop() = 0;

    // used by the backend to set metadata properties
    void addDataRate(qreal min, qreal max);
    void setDataRates(const QSensor *otherSensor);
    void addOutputRange(qreal min, qreal max, qreal accuracy);
    void setDescription(const QString &description);

    template <typename T>
    T *setReading(T *reading)
    {
        if (!reading)
            reading = new T(this);
        setReadings(reading, new T(this), new T(this));
        return reading;
    }

    QSensorReading *reading() const;
    QSensor *sensor() const { return m_sensor; }

    // used by the backend to inform us of events
    void newReadingAvailable();
    void sensorStopped();
    void sensorBusy();
    void sensorError(int error);

private:
    void setReadings(QSensorReading *device, QSensorReading *filter, QSensorReading *cache);

    QSensor *m_sensor;
    Q_DISABLE_COPY(QSensorBackend)
};

QTM_END_NAMESPACE
QT_END_NAMESPACE

#endif

