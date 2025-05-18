// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef WINRTORIENTATIONSENSOR_H
#define WINRTORIENTATIONSENSOR_H

#include <QtSensors/QSensorBackend>
#include <QtCore/QScopedPointer>

QT_USE_NAMESPACE

class WinRtOrientationSensorPrivate;
class WinRtOrientationSensor : public QSensorBackend
{
    Q_OBJECT
public:
    WinRtOrientationSensor(QSensor *sensor);
    ~WinRtOrientationSensor();

    void start() override;
    void stop() override;

private:
    QScopedPointer<WinRtOrientationSensorPrivate> d_ptr;
    Q_DECLARE_PRIVATE(WinRtOrientationSensor)
};

#endif // WINRTORIENTATIONSENSOR_H
