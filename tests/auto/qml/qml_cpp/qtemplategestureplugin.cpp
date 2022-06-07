// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QtPlugin>
#include <QStringList>
#include <QObject>

#include "qtemplategestureplugin.h"
#include <qsensorgestureplugininterface.h>
#include <qsensorgesturemanager.h>
#include "qtemplaterecognizer.h"


QTemplateGesturePlugin::QTemplateGesturePlugin()
{
}

QTemplateGesturePlugin::~QTemplateGesturePlugin()
{
}

QStringList QTemplateGesturePlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.template" << "QtSensors.template1";
    return list;
}


QList <QSensorGestureRecognizer *>  QTemplateGesturePlugin::createRecognizers()
{
    QList <QSensorGestureRecognizer *> recognizers;

    QSensorGestureRecognizer *sRec = new QTemplateGestureRecognizer(this);
    recognizers.append(sRec);
    sRec = new QTemplateGestureRecognizer1(this);
    recognizers.append(sRec);

    return recognizers;
}
