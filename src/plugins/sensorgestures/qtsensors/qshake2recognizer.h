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

#ifndef QSHAKERECOGNIZER_H
#define QSHAKERECOGNIZER_H


#include <QtSensors/QSensor>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>

#include <QDebug>
#include <QTimer>

#include <qsensorgesturerecognizer.h>
QT_BEGIN_NAMESPACE

class QShake2SensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT

public:

    enum ShakeDirection {
        ShakeUndefined = 0,
        ShakeLeft,
        ShakeRight,
        ShakeUp,
        ShakeDown
    };

    QShake2SensorGestureRecognizer(QObject *parent = 0);
    ~QShake2SensorGestureRecognizer();

    void create();

    QString id() const;
    bool start();
    bool stop();
    bool isActive();

    int thresholdTime() const;
    void setThresholdTime(int msec);

Q_SIGNALS:
    void shakeLeft();
    void shakeRight();
    void shakeUp();
    void shakeDown();

private slots:
    void accelChanged();
    void timeout();

private:
    QAccelerometer *accel;

    qreal pXaxis;
    qreal nXaxis;

    qreal pYaxis;
    qreal nYaxis;

    qreal pZaxis;
    qreal nZaxis;

    bool detectingState;
    QTimer *timer;
    int timerTimeout;
    bool active;
    int accelRange;

    ShakeDirection shakeDirection;


};
QT_END_NAMESPACE
#endif // QSHAKERECOGNIZER_H
