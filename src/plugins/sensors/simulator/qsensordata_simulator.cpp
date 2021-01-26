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

#include "qsensordata_simulator_p.h"

#include <QtCore/QDataStream>

namespace QtMobility {

void qt_registerSensorTypes()
{
    qRegisterMetaTypeStreamOperators<QAmbientLightReadingData>("QtMobility::QAmbientLightReadingData");
    qRegisterMetaTypeStreamOperators<QLightReadingData>("QtMobility::QLightReadingData");
    qRegisterMetaTypeStreamOperators<QAccelerometerReadingData>("QtMobility::QAccelerometerReadingData");
    qRegisterMetaTypeStreamOperators<QCompassReadingData>("QtMobility::QCompassReadingData");
    qRegisterMetaTypeStreamOperators<QProximityReadingData>("QtMobility::QProximityReadingData");
    qRegisterMetaTypeStreamOperators<QIRProximityReadingData>("QtMobility::QIRProximityReadingData");
    qRegisterMetaTypeStreamOperators<QMagnetometerReadingData>("QtMobility::QMagnetometerReadingData");
}

QDataStream &operator<<(QDataStream &out, const QAmbientLightReadingData &s)
{
    out << static_cast<qint32>(s.lightLevel) << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QAmbientLightReadingData &s)
{
    qint32 lightLevel;
    in >> lightLevel >> s.timestamp;
    s.lightLevel = static_cast<SimulatorLightLevel>(lightLevel);
    return in;
}

QDataStream &operator<<(QDataStream &out, const QLightReadingData &s)
{
    out << s.lux << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QLightReadingData &s)
{
    in >> s.lux >> s.timestamp;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QAccelerometerReadingData &s)
{
    out << s.x << s.y << s.z << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QAccelerometerReadingData &s)
{
    in >> s.x >> s.y >> s.z >> s.timestamp;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QCompassReadingData &s)
{
    out << s.azimuth << s.calibrationLevel << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QCompassReadingData &s)
{
    in >> s.azimuth >> s.calibrationLevel >> s.timestamp;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QProximityReadingData &s)
{
    out << s.close << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QProximityReadingData &s)
{
    in >> s.close >> s.timestamp;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QIRProximityReadingData &s)
{
    out << s.irProximity << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QIRProximityReadingData &s)
{
    in >> s.irProximity >> s.timestamp;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QMagnetometerReadingData &s)
{
    out << s.x << s.y << s.z << s.calibrationLevel << s.timestamp;
    return out;
}

QDataStream &operator>>(QDataStream &in, QMagnetometerReadingData &s)
{
    in >> s.x >> s.y >> s.z >> s.calibrationLevel >> s.timestamp;
    return in;
}

} // namespace
