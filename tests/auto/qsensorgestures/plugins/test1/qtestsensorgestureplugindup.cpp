// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QTimer>

#include "qtestrecognizerdup.h"
#include "qtest2recognizerdup.h"

#include "qtestsensorgestureplugindup.h"

#include <qsensorgestureplugininterface.h>
#include <qsensorgesturerecognizer.h>
#include <qsensorgesturemanager.h>


QTestSensorGestureDupPlugin::QTestSensorGestureDupPlugin()
{
}

QTestSensorGestureDupPlugin::~QTestSensorGestureDupPlugin()
{
}

/*!
  Describes this gesture's possible gesture signals.
handled through the detected(const QString &) signal.
  */
QStringList QTestSensorGestureDupPlugin::gestureSignals() const
{
    QStringList list;
    for (const QSensorGestureRecognizer* rec : recognizersList)
        list.append(rec->gestureSignals());
    return list;
}

QList <QSensorGestureRecognizer *> QTestSensorGestureDupPlugin::createRecognizers()
{
    QSensorGestureRecognizer *sRec = new QTestRecognizerDup(this);
    recognizersList.append(sRec);

    QSensorGestureRecognizer *sRec2 = new QTest2RecognizerDup(this);
    recognizersList.append(sRec2);

    return recognizersList;
}

QStringList QTestSensorGestureDupPlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.test.dup";
    list << "QtSensors.test.dup";

    return list;
}

QList<QSensorGestureRecognizer*> QTestSensorGestureDupPlugin::recognizers() const
{
    return recognizersList;
}

QString QTestSensorGestureDupPlugin::name() const
{
    return "TestGesturesDup";
}
