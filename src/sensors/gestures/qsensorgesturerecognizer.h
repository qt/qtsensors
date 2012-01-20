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

#ifndef QSENSORGESTURERECOGNIZER_H
#define QSENSORGESTURERECOGNIZER_H

#include <QDebug>
#include <QTimer>
#include <QStringList>

#include "qsensorgesture.h"

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QSensorGestureRecognizerPrivate;
class Q_SENSORS_EXPORT QSensorGestureRecognizer : public QObject
{
    Q_OBJECT
public:
    QSensorGestureRecognizer(QObject *parent = 0);
    virtual ~QSensorGestureRecognizer();

    virtual QString id() const = 0;

    virtual bool isActive() = 0;

    void startBackend();
    void stopBackend();
    void createBackend();

    QStringList gestureSignals() const;

Q_SIGNALS:
    void detected(const QString &);

protected:
    virtual void create() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

private:
        QSensorGestureRecognizerPrivate * d_ptr;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif // QSENSORGESTURERECOGNIZER_H
