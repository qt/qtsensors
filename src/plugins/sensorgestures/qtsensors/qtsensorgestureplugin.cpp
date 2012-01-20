/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
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
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtPlugin>
#include <QStringList>
#include <QObject>
#include <QFile>
#include <QDateTime>
#include "qtsensorgestureplugin.h"

#include <qsensorgestureplugininterface.h>

#include "qcoversensorgesturerecognizer.h"
#include "qtwistsensorgesturerecognizer.h"
#include "qdoubletapsensorgesturerecognizer.h"
#include "qhoversensorgesturerecognizer.h"
#include "qpickupsensorgesturerecognizer.h"
#include "qshake2recognizer.h"
#include "qturnoversensorgesturerecognizer.h"
#include "qwhipsensorgesturerecognizer.h"


QT_BEGIN_NAMESPACE

QTextStream *out = 0;
void logOutput(QtMsgType type, const char *msg)
{
    if (QString(msg).contains("setWindowProperty") ||
            QString(msg).contains("getSurface"))
        return;

    QString debugdate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    switch (type)
    {
    case QtDebugMsg:
        debugdate += "[D]";
        break;
    case QtWarningMsg:
        debugdate += "[W]";
        break;
    case QtCriticalMsg:
        debugdate += "[C]";
        break;
    case QtFatalMsg:
        debugdate += "[F]";
    }
    (*out) << debugdate << " " << msg << endl;

    if (QtFatalMsg == type)
    {
        abort();
    }
}


QtSensorGesturePlugin::QtSensorGesturePlugin()
{
    QString fileName = "/tmp/log";
        QFile *log = new QFile(fileName);
        if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            out = new QTextStream(log);
            qInstallMsgHandler(logOutput);
        } else {
            qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
        }

        qDebug() << Q_FUNC_INFO;
}

QtSensorGesturePlugin::~QtSensorGesturePlugin()
{
}

QStringList QtSensorGesturePlugin::supportedIds() const
{
    qDebug() << Q_FUNC_INFO;

    QStringList list;
    list << "QtSensors.cover";
    list << "QtSensors.doubletap";
    list << "QtSensors.hover";
    list << "QtSensors.pickup";
    list << "QtSensors.shake2";
    list << "QtSensors.turnover";
    list << "QtSensors.twist";
    list << "QtSensors.whip";
    return list;
}

QList <QSensorGestureRecognizer *> QtSensorGesturePlugin::createRecognizers()
{
    qDebug() << Q_FUNC_INFO;
    QList <QSensorGestureRecognizer *> recognizers;

//    QSensorGestureRecognizer *sRec1 = new QCirclesSensorGestureRecognizer(this);
//    recognizers.append(sRec1);

    QSensorGestureRecognizer *sRec2 = new QCoverSensorGestureRecognizer(this);
    recognizers.append(sRec2);

    QSensorGestureRecognizer *sRec3 = new QDoubleTapSensorGestureRecognizer(this);
    recognizers.append(sRec3);

    QSensorGestureRecognizer *sRec4 = new QHoverSensorGestureRecognizer(this);
    recognizers.append(sRec4);

    QSensorGestureRecognizer *sRec5 = new QPickupSensorGestureRecognizer(this);
    recognizers.append(sRec5);

    QSensorGestureRecognizer *sRec6 = new QShake2SensorGestureRecognizer(this);
    recognizers.append(sRec6);

    QSensorGestureRecognizer *sRec7 = new QTurnoverSensorGestureRecognizer(this);
    recognizers.append(sRec7);

    QSensorGestureRecognizer *sRec8 = new QWhipSensorGestureRecognizer(this);
    recognizers.append(sRec8);

    QSensorGestureRecognizer *sRec9 = new QTwistSensorGestureRecognizer(this);
    recognizers.append(sRec9);

    return recognizers;
}

Q_EXPORT_PLUGIN2(qtsensorgestures_plugin, QtSensorGesturePlugin)

QT_END_NAMESPACE
