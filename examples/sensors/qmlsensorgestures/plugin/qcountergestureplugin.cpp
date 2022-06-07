// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtPlugin>
#include <QStringList>
#include <QObject>

#include "qcountergestureplugin.h"
#include <qsensorgestureplugininterface.h>
#include <qsensorgesturemanager.h>
#include "qcounterrecognizer.h"


QCounterGesturePlugin::QCounterGesturePlugin()
{
}

QCounterGesturePlugin::~QCounterGesturePlugin()
{
}

QStringList QCounterGesturePlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.SecondCounter";
    return list;
}


QList <QSensorGestureRecognizer *>  QCounterGesturePlugin::createRecognizers()
{
    QList <QSensorGestureRecognizer *> recognizers;

    QSensorGestureRecognizer *sRec = new QCounterGestureRecognizer(this);
    recognizers.append(sRec);

    return recognizers;
}
