// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtPlugin>
#include <QStringList>
#include <QObject>

#include "qshakesensorgestureplugin.h"

#include <QtSensors/qsensorgestureplugininterface.h>

#include "qshakerecognizer.h"


QShakeSensorGesturePlugin::QShakeSensorGesturePlugin()
{
}

QShakeSensorGesturePlugin::~QShakeSensorGesturePlugin()
{
}

QStringList QShakeSensorGesturePlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.shake";
    return list;
}

QList <QSensorGestureRecognizer *> QShakeSensorGesturePlugin::createRecognizers()
{
    QList <QSensorGestureRecognizer *> recognizers;

    QSensorGestureRecognizer *sRec = new QShakeSensorGestureRecognizer(this);
    recognizers.append(sRec);

    return recognizers;
}
