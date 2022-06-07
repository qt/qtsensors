// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


#ifndef QSLAMSENSORGESTURERECOGNIZER_H
#define QSLAMSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>
#include <QtSensors/QOrientationSensor>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerReading>
#include <QtSensors/QOrientationReading>
QT_BEGIN_NAMESPACE

class QSlamSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QSlamSensorGestureRecognizer(QObject *parent = 0);
    ~QSlamSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void slam();

private slots:
    void accelChanged(QAccelerometerReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void doSlam();

private:

    QAccelerometer *accel;
    QOrientationReading *orientationReading;
    int accelRange;
    bool active;

    bool wasNegative;
    qreal lastX;
    qreal lastY;
    qreal lastZ;
    qreal detectedX;

    bool detecting;

    qreal accelX;
    qreal roll;
    QList<qreal> restingList;
    bool resting;

    bool hasBeenResting();
    quint64 lastTimestamp;
    quint64 lapsedTime;
    bool timerActive;
};

QT_END_NAMESPACE
#endif // QSLAMSENSORGESTURERECOGNIZER_H
