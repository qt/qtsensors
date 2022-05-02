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


#ifndef QCOVERSENSORGESTURERECOGNIZER_H
#define QCOVERSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>
#include <QTimer>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QCoverSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QCoverSensorGestureRecognizer(QObject *parent = 0);
    ~QCoverSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void cover();

private slots:
    void proximityChanged(QProximityReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void timeout();

private:

    QOrientationReading *orientationReading;
    bool proximityReading;

    QTimer *timer;
    bool active;
    bool detecting;
};

QT_END_NAMESPACE
#endif // QCOVERSENSORGESTURERECOGNIZER_H
