/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#include "simulatorgesturescommon_p.h"

#include <QtSimulator/version.h>
#include <QtSimulator/QtSimulator>

#include <QDebug>
#include <QStringList>

using namespace Simulator;


Q_GLOBAL_STATIC(QString, qtSensorGestureData)

SensorGesturesConnection::SensorGesturesConnection(QObject *parent)
    : QObject(parent)
{
    mConnection = new Connection(Connection::Client, QLatin1String("QtSimulator_Mobility_ServerName1.3.0.0"),
                                 0xbeef+1, Version(1,0,0,0), this);
    mWorker = mConnection->connectToServer(Connection::simulatorHostName(true), 0xbeef+1);

    if (!mWorker) {
        qWarning() << "Could not connect to server";
        return;
    }

    mWorker->addReceiver(this);
    mWorker->call("setRequestsSensorGestures");
}

SensorGesturesConnection::~SensorGesturesConnection()
{
    mWorker->call("setSensorGestures", QStringList());
    delete mWorker;
}

void SensorGesturesConnection::setSensorGestureData(const QString &data)
{
    QString gesture = data;
    if (data.contains(QLatin1String("detected"))) {
            gesture.remove(QLatin1String("detected("));
            gesture.remove(QLatin1String(")"));
    }
    *qtSensorGestureData() = gesture;
}

void SensorGesturesConnection::newSensorGestureDetected()
{
    emit sensorGestureDetected();
}

void SensorGesturesConnection::newSensorGestures(const QStringList &gestures)
{
    if (!mWorker) return;

    Q_FOREACH (const QString &gest, gestures) {
        if (!gest.contains(QLatin1String("detected"))) {
            QString tmp = gest.left(gest.length()-2);
            if (!allGestures.contains(tmp)) {
                allGestures.append(tmp);
            }
        }
    }

    mWorker->call("setSensorGestures", allGestures);
}

void SensorGesturesConnection::removeSensorGestures(const QStringList &gestures)
{
    Q_FOREACH (const QString &gest, gestures) {
        QString tmp = gest.left(gest.length()-2);
        if (allGestures.contains(tmp)) {
            allGestures.removeOne(tmp);
        }
    }
    mWorker->call("setSensorGestures", allGestures);
}

QString get_qtSensorGestureData()
{
    return *qtSensorGestureData();
}

