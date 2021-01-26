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

