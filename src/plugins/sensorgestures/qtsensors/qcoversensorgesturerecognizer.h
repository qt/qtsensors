// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


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
