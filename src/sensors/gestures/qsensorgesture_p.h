// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSENSORGESTURE_P_H
#define QSENSORGESTURE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//
#include <QtSensors/QSensor>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>
#include <QTimer>

#include "qsensorgesture.h"
#include "qsensorgesturemanager.h"
#include <QtCore/private/qmetaobjectbuilder_p.h>

QT_BEGIN_NAMESPACE

class QSensorGesturePrivate : public QObject
{

public:
    QSensorGesturePrivate(QObject *parent = 0);
    ~QSensorGesturePrivate();

    QList<QSensorGestureRecognizer *> m_sensorRecognizers;

    QByteArray metadata;
    QMetaObject* meta;
    bool isActive;
    QStringList localGestureSignals;
    QStringList availableIds;
    QStringList invalidIds;
    bool valid;
};


QT_END_NAMESPACE

#endif // QSENSORGESTURE_P_H
