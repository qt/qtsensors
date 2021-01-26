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
