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
#ifndef BBORIENTATIONSENSOR_H
#define BBORIENTATIONSENSOR_H

#include "bbsensorbackend.h"
#include <qorientationsensor.h>

class BbOrientationReadingPrivate;

// We extend QOrientationReading with the "rotation" property
class BbOrientationReading : public QOrientationReading
{
    Q_OBJECT

    // Screen Rotation in degrees - 0, 90, 180 or 270
    Q_PROPERTY(int rotation READ rotation)
public:
    explicit BbOrientationReading(QObject *parent = 0);
    ~BbOrientationReading();
    void copyValuesFrom(QSensorReading *other);
    int rotation() const;
    void setRotation(int rotation);

private:
    QScopedPointer<BbOrientationReadingPrivate> d;
};

class BbOrientationSensor : public BbSensorBackend<BbOrientationReading>
{
    Q_OBJECT

public:
    explicit BbOrientationSensor(QSensor *sensor);

    static QString devicePath();

    void start();
    void additionalDeviceInit();
    bool addDefaultRange();

protected:
    bool updateReadingFromEvent(const sensor_event_t &event, BbOrientationReading *reading);
};

#endif
