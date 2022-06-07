// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GRUESENSORIMPL_H
#define GRUESENSORIMPL_H

#include <qsensorbackend.h>
#include "gruesensor.h"
#include <qambientlightsensor.h>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class gruesensorimpl : public QSensorBackend
{
    Q_OBJECT
public:
    static char const * const id;

    gruesensorimpl(QSensor *sensor);

    void start() override;
    void stop() override;

private Q_SLOTS:
    void lightChanged();
    void increaseChance();

private:
    GrueSensorReading m_reading;
    QAmbientLightSensor *lightSensor;
    QTimer *darkTimer;
    QElapsedTimer timer;
    QAmbientLightReading::LightLevel lightLevel;
};

#endif

