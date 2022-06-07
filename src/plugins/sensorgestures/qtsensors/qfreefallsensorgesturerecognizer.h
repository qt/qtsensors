// Copyright (C) 2016 Lorn Potter
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only



#ifndef QFREEFALLSENSORGESTURERECOGNIZER_H
#define QFREEFALLSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QFreefallSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QFreefallSensorGestureRecognizer(QObject *parent = 0);
    ~QFreefallSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void freefall();
    void landed();

private slots:
    void accelChanged(QAccelerometerReading *reading);

private:

    bool active;
    bool detecting;
    QList <qreal> freefallList;

};
QT_END_NAMESPACE
#endif // QPICKUPSENSORGESTURERECOGNIZER_H
