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

#ifndef QSHAKERECOGNIZER_H
#define QSHAKERECOGNIZER_H

#include <QDebug>

#include <QtSensors/qsensorgesturerecognizer.h>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

struct ShakeData {
   qreal x;
   qreal y;
   qreal z;
};

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

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

    int timerTimeout;


Q_SIGNALS:
    void shakeLeft();
    void shakeRight();
    void shakeUp();
    void shakeDown();

private slots:
    void accelChanged(QAccelerometerReading *reading);
    void timeout();


private:
    QAccelerometerReading *accelReading;

    bool active;

    ShakeDirection shakeDirection;

    ShakeData prevData;
    ShakeData currentData;

    bool checkForShake(ShakeData prevSensorData, ShakeData currentSensorData, qreal threshold);
    bool shaking;
    int shakeCount;
    int threshold;

    bool isNegative(qreal num);
    qreal lapsedTime;
    quint64 lastTimestamp;
    bool timerActive;
};
QT_END_NAMESPACE
#endif // QSHAKERECOGNIZER_H
