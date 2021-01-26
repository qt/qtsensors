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
