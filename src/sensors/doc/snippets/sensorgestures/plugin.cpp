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
