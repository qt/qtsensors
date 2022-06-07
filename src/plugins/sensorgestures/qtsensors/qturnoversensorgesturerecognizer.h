// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTURNOVERSENSORGESTURERECOGNIZER_H
#define QTURNOVERSENSORGESTURERECOGNIZER_H

#include <QtSensors/qsensorgesturerecognizer.h>
#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QTurnoverSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QTurnoverSensorGestureRecognizer(QObject *parent = 0);
    ~QTurnoverSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void turnover();

private slots:
    void orientationReadingChanged(QOrientationReading *reading);
    void proximityChanged(QProximityReading *reading);
    void isRecognized();

private:

    bool isClose;
    bool isFaceDown;
    bool active;

    QList<qreal> zList;

};
QT_END_NAMESPACE
#endif // QTURNOVERSENSORGESTURERECOGNIZER_H
