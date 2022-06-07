// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


#ifndef QPICKUPSENSORGESTURERECOGNIZER_H
#define QPICKUPSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QPickupSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QPickupSensorGestureRecognizer(QObject *parent = 0);
    ~QPickupSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void pickup();

private slots:
    void accelChanged(QAccelerometerReading *reading);

    void timeout();
private:
    QAccelerometerReading *accelReading;

    bool active;
    qreal pXaxis;
    qreal pYaxis;
    qreal pZaxis;

    qreal lastpitch;
    bool detecting;

    QList <qreal> pitchList;
    QList <qreal> rollList;

    void clear();
};
QT_END_NAMESPACE
#endif // QPICKUPSENSORGESTURERECOGNIZER_H
