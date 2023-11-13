// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef IOSCompass_H
#define IOSCompass_H

#import <CoreLocation/CLLocationManager.h>

#include <qsensorbackend.h>
#include <qcompass.h>

QT_BEGIN_NAMESPACE

class IOSCompass : public QSensorBackend
{
public:
    static char const * const id;

    explicit IOSCompass(QSensor *sensor);
    ~IOSCompass();

    void start() override;
    void stop() override;

    void headingChanged(qreal heading, quint64 timestamp, qreal calibrationLevel);

private:
    CLLocationManager *m_locationManager;
    QCompassReading m_reading;
};
QT_END_NAMESPACE

#endif // IOSCompass_H

