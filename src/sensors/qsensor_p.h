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

#ifndef QSENSOR_P_H
#define QSENSOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qsensor.h"

#include "private/qobject_p.h"

QT_BEGIN_NAMESPACE

typedef QList<QSensorFilter*> QFilterList;

class QSensorPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QSensor)
public:
    QSensorPrivate()
        : identifier()
        , type()
        , outputRange(-1)
        , dataRate(0)
        , backend(0)
        , active(false)
        , busy(false)
        , device_reading(0)
        , filter_reading(0)
        , cache_reading(0)
        , error(0)
        , alwaysOn(false)
        , skipDuplicates(false)
        , axesOrientationMode(QSensor::AxesOrientationMode::FixedOrientation)
        , currentOrientation(0)
        , userOrientation(0)
        , bufferSize(1)
        , maxBufferSize(1)
        , efficientBufferSize(1)
    {
    }

    void init(const QByteArray &sensorType);

    // meta-data
    QByteArray identifier;
    QByteArray type;

    QString description;

    qoutputrangelist outputRanges;
    int outputRange;

    // policy
    qrangelist availableDataRates;
    int dataRate;

    QSensorBackend *backend;
    QFilterList filters;
    bool active;
    bool busy;
    QSensorReading *device_reading;
    QSensorReading *filter_reading;
    QSensorReading *cache_reading;

    int error;

    bool alwaysOn;
    bool skipDuplicates;

    QSensor::AxesOrientationMode axesOrientationMode;
    int currentOrientation;
    int userOrientation;

    int bufferSize;
    int maxBufferSize;
    int efficientBufferSize;
};

class QSensorReadingPrivate
{
public:
    QSensorReadingPrivate()
        : timestamp(0)
    {
    }

    // sensor data cache
    quint64 timestamp;
};

QT_END_NAMESPACE

#endif

