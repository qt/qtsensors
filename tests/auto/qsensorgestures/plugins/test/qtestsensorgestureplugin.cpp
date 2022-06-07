// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QTimer>
#include <QTest>

#include "qtestrecognizer.h"
#include "qtest2recognizer.h"

#include "qtestsensorgestureplugin_p.h"

#include <qsensorgestureplugininterface.h>
#include <qsensorgesturerecognizer.h>
#include <qsensorgesturemanager.h>


QTestSensorGesturePlugin::QTestSensorGesturePlugin()
{
}

QTestSensorGesturePlugin::~QTestSensorGesturePlugin()
{
}


///*!
//  Describes this gesture's possible gesture signals.
//handled through the detected(const QString &) signal.
//  */
//QStringList QTestSensorGesturePlugin::gestureSignals() const
//{
//    QStringList list;
//    Q_FOREACH (const QSensorGestureRecognizer* rec, recognizersList) {
//        list.append(rec->gestureSignals());
//    }
//    return list;
//}

QList <QSensorGestureRecognizer *> QTestSensorGesturePlugin::createRecognizers()
{
    QSensorGestureRecognizer *sRec = new QTestRecognizer(this);
    recognizersList.append(sRec);

    QSensorGestureRecognizer *sRec2 = new QTest2Recognizer(this);
    recognizersList.append(sRec2);

    return recognizersList;
}

QStringList QTestSensorGesturePlugin::supportedIds() const
{
    QStringList list;
    list << "QtSensors.test";
    list <<"QtSensors.test2";

    return list;
}

QList<QSensorGestureRecognizer*> QTestSensorGesturePlugin::recognizers() const
{
    return recognizersList;
}

QString QTestSensorGesturePlugin::name() const
{
    return "TestGestures";
}
