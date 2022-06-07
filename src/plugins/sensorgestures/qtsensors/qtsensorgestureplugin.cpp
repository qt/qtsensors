// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtPlugin>
#include <QStringList>
#include <QObject>

#include "qtsensorgestureplugin.h"

#include <QtSensors/qsensorgestureplugininterface.h>

#include "qcoversensorgesturerecognizer.h"
#include "qtwistsensorgesturerecognizer.h"
#include "qdoubletapsensorgesturerecognizer.h"
#include "qhoversensorgesturerecognizer.h"
#include "qpickupsensorgesturerecognizer.h"
#include "qshake2recognizer.h"
#include "qslamgesturerecognizer.h"
#include "qturnoversensorgesturerecognizer.h"
#include "qwhipsensorgesturerecognizer.h"
#include "qfreefallsensorgesturerecognizer.h"


QT_BEGIN_NAMESPACE


QtSensorGesturePlugin::QtSensorGesturePlugin()
{
}

QtSensorGesturePlugin::~QtSensorGesturePlugin()
{
}

QStringList QtSensorGesturePlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.cover";
    list << "QtSensors.doubletap";
    list << "QtSensors.hover";
    list << "QtSensors.freefall";
    list << "QtSensors.pickup";
    list << "QtSensors.shake2";
    list << "QtSensors.slam";
    list << "QtSensors.turnover";
    list << "QtSensors.twist";
    list << "QtSensors.whip";
    return list;
}

QList <QSensorGestureRecognizer *> QtSensorGesturePlugin::createRecognizers()
{
    QList <QSensorGestureRecognizer *> recognizers;

    recognizers.append(new QCoverSensorGestureRecognizer(this));

    recognizers.append(new QDoubleTapSensorGestureRecognizer(this));

    recognizers.append(new QHoverSensorGestureRecognizer(this));

    recognizers.append(new QPickupSensorGestureRecognizer(this));

    recognizers.append(new QShake2SensorGestureRecognizer(this));

    recognizers.append(new QSlamSensorGestureRecognizer(this));

    recognizers.append(new QTurnoverSensorGestureRecognizer(this));

    recognizers.append(new QWhipSensorGestureRecognizer(this));

    recognizers.append(new QTwistSensorGestureRecognizer(this));

    recognizers.append(new QFreefallSensorGestureRecognizer(this));
    return recognizers;
}

QT_END_NAMESPACE
