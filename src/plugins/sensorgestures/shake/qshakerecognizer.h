/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

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
