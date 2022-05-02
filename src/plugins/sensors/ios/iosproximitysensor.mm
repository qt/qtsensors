/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#import <UIKit/UIDevice.h>

#include "iosproximitysensor.h"

char const * const IOSProximitySensor::id("ios.proximitysensor");

QT_BEGIN_NAMESPACE

int IOSProximitySensor::s_startCount = 0;

@interface ProximitySensorCallback : NSObject
{
}
@end

@implementation ProximitySensorCallback {
    IOSProximitySensor *m_iosProximitySensor;
}

- (id)initWithQIOSProximitySensor:(IOSProximitySensor *)iosProximitySensor
{
    self = [super init];
    if (self) {
        m_iosProximitySensor = iosProximitySensor;
        [[NSNotificationCenter defaultCenter]
            addObserver:self
            selector:@selector(proximityChanged:)
            name:@"UIDeviceProximityStateDidChangeNotification" object:nil];
    }
    return self;
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter]
        removeObserver:self
        name:@"UIDeviceProximityStateDidChangeNotification" object:nil];
    [super dealloc];
}

- (void)proximityChanged:(NSNotificationCenter *)notification
{
    Q_UNUSED(notification);
    bool close = [[UIDevice currentDevice] proximityState] == YES;
    m_iosProximitySensor->proximityChanged(close);
}

@end

bool IOSProximitySensor::available()
{
    UIDevice *device = [UIDevice currentDevice];
    if (device.proximityMonitoringEnabled)
        return true;
    // According to the docs, you need to switch it on and
    // re-read the property to check if it is available:
    device.proximityMonitoringEnabled = YES;
    bool available = device.proximityMonitoringEnabled;
    device.proximityMonitoringEnabled = NO;
    return available;
}

IOSProximitySensor::IOSProximitySensor(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_proximitySensorCallback(0)
{
    setReading<QProximityReading>(&m_reading);
}

IOSProximitySensor::~IOSProximitySensor()
{
    [m_proximitySensorCallback release];
}

void IOSProximitySensor::start()
{
    if (m_proximitySensorCallback)
        return;

    m_proximitySensorCallback = [[ProximitySensorCallback alloc] initWithQIOSProximitySensor:this];
    if (++s_startCount == 1)
        [UIDevice currentDevice].proximityMonitoringEnabled = YES;
}

void IOSProximitySensor::proximityChanged(bool close)
{
    m_reading.setClose(close);
    m_reading.setTimestamp(quint64([[NSDate date] timeIntervalSinceReferenceDate] * 1e6));
    newReadingAvailable();
}

void IOSProximitySensor::stop()
{
    if (!m_proximitySensorCallback)
        return;

    [m_proximitySensorCallback release];
    m_proximitySensorCallback = 0;
    if (--s_startCount == 0)
        [UIDevice currentDevice].proximityMonitoringEnabled = NO;
}

QT_END_NAMESPACE
