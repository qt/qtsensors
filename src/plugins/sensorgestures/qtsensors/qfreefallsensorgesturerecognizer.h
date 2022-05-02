/****************************************************************************
**
** Copyright (C) 2016 Lorn Potter
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
