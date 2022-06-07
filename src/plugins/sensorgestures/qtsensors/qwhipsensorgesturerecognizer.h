// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


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
