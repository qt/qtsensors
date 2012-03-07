/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QSENSOR2PROXIMITY_H
#define QSENSOR2PROXIMITY_H

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <qproximitysensor.h>
#include "qsensor2common.h"

QT_BEGIN_NAMESPACE

class QSensor2Proximity : public qsensor2common, public QProximityFilter
{
    Q_OBJECT
    Q_PROPERTY(bool near READ near NOTIFY nearChanged)

public:
    QSensor2Proximity(QObject* parent = 0);
    virtual ~QSensor2Proximity();

Q_SIGNALS:
    void nearChanged();

private:
    // Override of QProximityFilter::filter(QProximityReading*)
    bool filter(QProximityReading *reading);
    bool near();

private:
    QSensor *sensor() { return _proximity; }
    QProximitySensor* _proximity;
    bool _near;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QSensor2Proximity)

#endif // QSENSOR2PROXIMITY_H
