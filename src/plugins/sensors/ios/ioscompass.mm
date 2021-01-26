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

#import <CoreLocation/CLHeading.h>
#import <CoreLocation/CLLocationManagerDelegate.h>
#include <QtCore/qglobal.h>

#include "ioscompass.h"

char const * const IOSCompass::id("ios.compass");

QT_BEGIN_NAMESPACE

@interface locationDelegate : NSObject <CLLocationManagerDelegate>
{
    IOSCompass *m_iosCompass;
}
@end

@implementation locationDelegate

- (id)initWithQIOSCompass:(IOSCompass*)iosCompass
{
    self = [super init];
    if (self) {
        m_iosCompass = iosCompass;
    }
    return self;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    Q_UNUSED(manager);
    // Convert NSDate to microseconds:
    quint64 timestamp = quint64(newHeading.timestamp.timeIntervalSinceReferenceDate * 1e6);
    double accuracy = newHeading.headingAccuracy;
    // Accuracy is the maximum number of degrees the reading can be off. The QtSensors scale
    // goes from 1 to 0, with 1 being the best (0 degrees off), and 0 worst (360 degrees off):
    qreal calibrationLevel = (accuracy < 0) ? 0 : qMax(0., 1 - (accuracy / 360));
    qreal heading = qreal(newHeading.magneticHeading);
    m_iosCompass->headingChanged(heading, timestamp, calibrationLevel);
}

- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager
{
    Q_UNUSED(manager);
    return YES;
}

@end

IOSCompass::IOSCompass(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_locationManager(0)
{
    setReading<QCompassReading>(&m_reading);
    addDataRate(1, 70);
    addOutputRange(0, 359, 1);
}

IOSCompass::~IOSCompass()
{
    [m_locationManager release];
}

void IOSCompass::start()
{
    if (!m_locationManager) {
        m_locationManager = [[CLLocationManager alloc] init];
        m_locationManager.desiredAccuracy = kCLLocationAccuracyBest;
        m_locationManager.headingFilter = kCLHeadingFilterNone;
        m_locationManager.delegate = [[locationDelegate alloc] initWithQIOSCompass:this];
    }
    [m_locationManager startUpdatingHeading];
}

void IOSCompass::headingChanged(qreal heading, quint64 timestamp, qreal calibrationLevel)
{
    m_reading.setAzimuth(heading);
    m_reading.setTimestamp(timestamp);
    m_reading.setCalibrationLevel(calibrationLevel);
    newReadingAvailable();
}

void IOSCompass::stop()
{
    [m_locationManager stopUpdatingHeading];
}

QT_END_NAMESPACE
