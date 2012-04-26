/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
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

QString get_qtSensorGestureData()
{
    return *qtSensorGestureData();
}

