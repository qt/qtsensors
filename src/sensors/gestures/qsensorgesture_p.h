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
