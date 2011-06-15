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

#include "qsensordata_simulator_p.h"

#include <QtCore/QDataStream>

void qt_registerSensorTypes()
{
    qRegisterMetaTypeStreamOperators<QAmbientLightReadingData>("QtMobility::QAmbientLightReadingData");
    qRegisterMetaTypeStreamOperators<QLightReadingData>("QtMobility::QLightReadingData");
    qRegisterMetaTypeStreamOperators<QAccelerometerReadingData>("QtMobility::QAccelerometerReadingData");
    qRegisterMetaTypeStreamOperators<QCompassReadingData>("QtMobility::QCompassReadingData");
    qRegisterMetaTypeStreamOperators<QProximityReadingData>("QtMobility::QProximityReadingData");
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
    s.lightLevel = static_cast<QAmbientLightReading::LightLevel>(lightLevel);
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
