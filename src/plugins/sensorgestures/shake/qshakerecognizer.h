// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QSHAKERECOGNIZER_H
#define QSHAKERECOGNIZER_H


#include <QtSensors/QSensor>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>
#include <QDebug>
#include <QTimer>

#include <QtSensors/qsensorgesturerecognizer.h>

 struct AccelData {
    qreal x;
    qreal y;
    qreal z;
};

class QShakeSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT

public:

    QShakeSensorGestureRecognizer(QObject *parent = 0);
    ~QShakeSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

    QTimer *timer;
    int timerTimeout;

Q_SIGNALS:
    void shake();

private slots:
    void accelChanged();
    void timeout();
private:
    QAccelerometer *accel;
    bool active;
    int accelRange;

    AccelData prevData;
    AccelData currentData;

    bool checkForShake(AccelData prevSensorData, AccelData currentSensorData, qreal threshold);
    bool shaking;
    int shakeCount;
    int threshold;

};

#endif // QSHAKERECOGNIZER_H
