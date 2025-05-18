// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef WINRTACCELEROMETER_H
#define WINRTACCELEROMETER_H

#include <QtSensors/QSensorBackend>
#include <QtCore/QScopedPointer>

QT_USE_NAMESPACE

class WinRtAccelerometerPrivate;
class WinRtAccelerometer : public QSensorBackend
{
    Q_OBJECT
public:
    WinRtAccelerometer(QSensor *sensor);
    ~WinRtAccelerometer();

    void start() override;
    void stop() override;

private:
    QScopedPointer<WinRtAccelerometerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(WinRtAccelerometer)
};

#endif // WINRTACCELEROMETER_H
