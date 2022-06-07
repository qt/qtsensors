// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QDOUBLETAPSENSORGESTURERECOGNIZER_H
#define QDOUBLETAPSENSORGESTURERECOGNIZER_H

#include <QtSensors/QSensor>

#include <QtSensors/qsensorgesturerecognizer.h>
#include <QtSensors/QTapSensor>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QDoubleTapSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QDoubleTapSensorGestureRecognizer(QObject *parent = 0);
    ~QDoubleTapSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void doubletap();

private slots:
    void tapChanged(QTapReading *reading);

private:
    QTapSensor *tapSensor;
    bool active;

};
QT_END_NAMESPACE
#endif // QDOUBLETAPSENSORGESTURERECOGNIZER_H
