/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
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
#include "bborientationsensor.h"

class BbOrientationReadingPrivate
{
public:
    BbOrientationReadingPrivate()
        : rotation(0)
    {
    }

    int rotation;
};

BbOrientationReading::BbOrientationReading(QObject *parent)
    : QOrientationReading(parent),
      d(new BbOrientationReadingPrivate)
{
}

BbOrientationReading::~BbOrientationReading()
{
}

void BbOrientationReading::copyValuesFrom(QSensorReading *other)
{
    QOrientationReading::copyValuesFrom(other);
    const BbOrientationReading * const reading = qobject_cast<const BbOrientationReading *>(other);
    if (reading)
        d->rotation = reading->rotation();
}

int BbOrientationReading::rotation() const
{
    return d->rotation;
}

void BbOrientationReading::setRotation(int rotation)
{
    d->rotation = rotation;
}

BbOrientationSensor::BbOrientationSensor(QSensor *sensor)
    : BbSensorBackend<BbOrientationReading>(devicePath(), SENSOR_TYPE_ORIENTATION, sensor)
{
    setDescription(QLatin1String("Device orientation"));
}

QString BbOrientationSensor::devicePath()
{
    return QLatin1String("/dev/sensor/orientation");
}

void BbOrientationSensor::start()
{
    BbSensorBackend<BbOrientationReading>::start();

    // Orientation rarely changes, so enable skiping of duplicates
    sensor_devctl_skipdupevent_u deviceSkip;
    deviceSkip.tx.enable = 1;
    const int result = devctl(deviceFile().handle(), DCMD_SENSOR_SKIPDUPEVENT, &deviceSkip,
                              sizeof(deviceSkip), NULL);
    if (result != EOK)
        perror("Enabling duplicate skipping for orientation sensor failed");
}

void BbOrientationSensor::additionalDeviceInit()
{
    // When querying the OS service for the range, it gives us the angles, which we don't need.
    // So set the possible enum values of QOrientationReading::Orientation as the output range here.
    // By returning false in addDefaultRange(), we skip setting the range from the OS service in the
    // base class.
    addOutputRange(0, 6, 1);
}

bool BbOrientationSensor::addDefaultRange()
{
    return false;
}

bool BbOrientationSensor::updateReadingFromEvent(const sensor_event_t &event, BbOrientationReading *reading)
{
    QOrientationReading::Orientation qtOrientation = QOrientationReading::Undefined;
    const QByteArray face(event.orientation.face);
    if (face == "FACE_UP") qtOrientation = QOrientationReading::FaceUp;
    else if (face == "TOP_UP") qtOrientation = QOrientationReading::TopUp;
    else if (face == "RIGHT_UP") qtOrientation = QOrientationReading::RightUp;
    else if (face == "LEFT_UP") qtOrientation = QOrientationReading::LeftUp;
    else if (face == "BOTTOM_UP") qtOrientation = QOrientationReading::TopDown;
    else if (face == "FACE_DOWN") qtOrientation = QOrientationReading::FaceDown;

    reading->setOrientation(qtOrientation);
    reading->setRotation(event.orientation.screen);
    return true;
}
