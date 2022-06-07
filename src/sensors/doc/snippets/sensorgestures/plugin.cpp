// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "myplugin.h"

#include <qsensorgestureplugininterface.h>
#include <qsensorgesturemanager.h>

//! [Plugin]

MySensorGestureRecognizer::MySensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
{
}

MySensorGestureRecognizer::~MySensorGestureRecognizer()
{
}

bool MySensorGestureRecognizer::start()
{
    Q_EMIT mySignal();
    return true;
}

bool MySensorGestureRecognizer::stop()
{
    return true;
}

bool MySensorGestureRecognizer::isActive()
{
    return true;
}

void  MySensorGestureRecognizer::create()
{
}

QString MySensorGestureRecognizer::id() const
{
    return QString("QtSensors.mygestures");
}


MySensorGesturePlugin::MySensorGesturePlugin(){}
MySensorGesturePlugin::~MySensorGesturePlugin(){}

QList <QSensorGestureRecognizer *>  MySensorGesturePlugin::createRecognizers()
{
    QList <QSensorGestureRecognizer *>  recognizers;
    MySensorGestureRecognizer *recognizer = new MySensorGestureRecognizer(this);
    recognizers.append(recognizer);

    return recognizers;
}

QStringList MySensorGesturePlugin::supportedIds() const
{
       return QStringList() << "QtSensors.mygestures";
}

//! [Plugin]
