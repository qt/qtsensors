// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only


#ifndef QHOVERSENSORGESTURERECOGNIZER_H
#define QHOVERSENSORGESTURERECOGNIZER_H

#include <QtSensors/QSensorGestureRecognizer>

#include "qtsensorgesturesensorhandler.h"


QT_BEGIN_NAMESPACE

class QHoverSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QHoverSensorGestureRecognizer(QObject *parent = 0);
    ~QHoverSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void hover();

private slots:
    void orientationReadingChanged(QOrientationReading *reading);
    void irProximityReadingChanged(QIRProximityReading *reading);
    void timeout();
    void timeout2();
private:
    QOrientationReading *orientationReading;
    qreal reflectance;
    bool hoverOk;
    bool detecting;

    qreal detectedHigh;
    bool active;
    qreal initialReflectance;
    bool checkForHovering();
    bool useHack;

    quint64 lastTimestamp;

    bool timer2Active;
    quint64 lapsedTime2;

};
QT_END_NAMESPACE
#endif // QHOVERSENSORGESTURERECOGNIZER_H
