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
