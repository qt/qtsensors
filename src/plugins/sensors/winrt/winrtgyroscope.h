// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef WINRTGYROSCOPE_H
#define WINRTGYROSCOPE_H

#include <QtSensors/QSensorBackend>
#include <QtCore/QScopedPointer>

QT_USE_NAMESPACE

class WinRtGyroscopePrivate;
class WinRtGyroscope : public QSensorBackend
{
    Q_OBJECT
public:
    WinRtGyroscope(QSensor *sensor);
    ~WinRtGyroscope();

    bool isFeatureSupported(QSensor::Feature feature) const override
    {
        if (feature == QSensor::Feature::AxesOrientation || feature == QSensor::Feature::AccelerationMode)
            return true;
        return false;
    }

    void start() override;
    void stop() override;

private:
    QScopedPointer<WinRtGyroscopePrivate> d_ptr;
    Q_DECLARE_PRIVATE(WinRtGyroscope)
};

#endif // WINRTGYROSCOPE_H
