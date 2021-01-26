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

#ifndef QSENSORDATA_SIMULATOR_P_H
#define QSENSORDATA_SIMULATOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QMetaType>
#include <QtCore/QDateTime>

namespace QtMobility {

enum SimulatorLightLevel {
    Undefined = 0,
    Dark,
    Twilight,
    Light,
    Bright,
    Sunny
};

struct QAmbientLightReadingData
{
    SimulatorLightLevel lightLevel;
    QDateTime timestamp;
};

struct QLightReadingData
{
    double lux;
    QDateTime timestamp;
};

struct QAccelerometerReadingData
{
    double x;
    double y;
    double z;
    QDateTime timestamp;
};

struct QMagnetometerReadingData
{
    double x;
    double y;
    double z;
    double calibrationLevel;
    QDateTime timestamp;
};

struct QCompassReadingData
{
    double azimuth;
    double calibrationLevel;
    QDateTime timestamp;
};

struct QProximityReadingData
{
    bool close;
    QDateTime timestamp;
};

struct QIRProximityReadingData
{
    double irProximity;
    QDateTime timestamp;
};

void qt_registerSensorTypes();

}

Q_DECLARE_METATYPE(QtMobility::QAmbientLightReadingData)
Q_DECLARE_METATYPE(QtMobility::QLightReadingData)
Q_DECLARE_METATYPE(QtMobility::QAccelerometerReadingData)
Q_DECLARE_METATYPE(QtMobility::QMagnetometerReadingData)
Q_DECLARE_METATYPE(QtMobility::QCompassReadingData)
Q_DECLARE_METATYPE(QtMobility::QProximityReadingData)
Q_DECLARE_METATYPE(QtMobility::QIRProximityReadingData)

#endif // QSENSORDATA_SIMULATOR_P_H
