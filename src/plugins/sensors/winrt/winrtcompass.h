// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef WINRTCOMPASS_H
#define WINRTCOMPASS_H

#include <QtSensors/QSensorBackend>
#include <QtCore/QScopedPointer>

QT_USE_NAMESPACE

class WinRtCompassPrivate;
class WinRtCompass : public QSensorBackend
{
    Q_OBJECT
public:
    WinRtCompass(QSensor *sensor);
    ~WinRtCompass();

    void start() override;
    void stop() override;

private:
    QScopedPointer<WinRtCompassPrivate> d_ptr;
    Q_DECLARE_PRIVATE(WinRtCompass)
};

#endif // WINRTCOMPASS_H
