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


#ifndef QWHIPSENSORGESTURERECOGNIZER_H
#define QWHIPSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QWhipSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QWhipSensorGestureRecognizer(QObject *parent = 0);
    ~QWhipSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void whip();

private slots:
    void accelChanged(QAccelerometerReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void timeout();

private:
    QOrientationReading *orientationReading;
    qreal accelRange;
    bool active;

    qreal lastX;
    qreal lastY;
    qreal lastZ;

    bool detecting;
    bool whipOk;

    QList<bool> whipMap;

    void checkForWhip();

    QList <bool> negativeList;

    QList<qreal> zList;

    quint64 lastTimestamp;

    bool timerActive;
    quint64 lapsedTime;

};

QT_END_NAMESPACE
#endif // QWHIPSENSORGESTURERECOGNIZER_H
