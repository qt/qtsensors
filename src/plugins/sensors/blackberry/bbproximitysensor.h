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
#ifndef BBPROXIMITYSENSOR_H
#define BBPROXIMITYSENSOR_H

#include "bbsensorbackend.h"
#include <qproximitysensor.h>

class BbProximityReadingPrivate;

// We extend QProximityReading with two new properties
class BbProximityReading : public QProximityReading
{
    Q_OBJECT

    // Distance in cm
    Q_PROPERTY(qreal distance READ distance)

    // Same as in QIRProximityReading
    Q_PROPERTY(qreal reflectance READ reflectance)

public:
    explicit BbProximityReading(QObject *parent = 0);
    ~BbProximityReading();
    void copyValuesFrom(QSensorReading *other);
    qreal distance() const;
    void setDistance(qreal distance);
    qreal reflectance() const;
    void setReflectance(qreal reflectance);

private:
    QScopedPointer<BbProximityReadingPrivate> d;
};

class BbProximitySensor : public BbSensorBackend<BbProximityReading>
{
    Q_OBJECT

public:
    explicit BbProximitySensor(QSensor *sensor);

    static QString devicePath();

protected:
    bool updateReadingFromEvent(const sensor_event_t &event, BbProximityReading *reading) Q_DECL_OVERRIDE;
};

#endif
