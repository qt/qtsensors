// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


#ifndef QWFLICKSENSORGESTURERECOGNIZER_H
#define QWFLICKSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>
#include <QtSensors/QAccelerometer>
#include <QtSensors/QOrientationSensor>
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

struct twistAccelData {
    qreal x;
    qreal y;
    qreal z;
};

class QTwistSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QTwistSensorGestureRecognizer(QObject *parent = 0);
    ~QTwistSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void twistLeft();
    void twistRight();

private slots:
    void accelChanged(QAccelerometerReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void checkTwist();

private:

    QOrientationReading *orientationReading;
    bool active;
    bool detecting;
    QList <twistAccelData> dataList;
    bool checking;
    void reset();
    bool checkOrientation();
    int increaseCount;
    int decreaseCount;
    qreal lastAngle;
    QList <QOrientationReading::Orientation> orientationList;
    qreal detectedAngle;
};
QT_END_NAMESPACE
#endif // QWFLICKSENSORGESTURERECOGNIZER_H
