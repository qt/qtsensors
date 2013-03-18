/****************************************************************************
**
** Copyright (C) 2012 Lorn Potter
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "iosaccelerometer.h"
#include "iosmotionmanager.h"

#include <UIKit/UIAccelerometer.h>
#include <CoreMotion/CMMotionManager.h>

char const * const IOSAccelerometer::id("ios.accelerometer");

@interface QtIoAccelListener : NSObject
{
    IOSAccelerometer *m_qiosAccelerometer;
    NSOperationQueue *m_updateQueue;
}
@end

@implementation QtIoAccelListener

-(id)initWithQIOSAccelerometer:(IOSAccelerometer *) qiosAccelerometer
{
    self = [super init];
    if (self) {
        m_qiosAccelerometer = qiosAccelerometer;
        m_updateQueue = [[NSOperationQueue alloc] init];
    }
    return self;
}

-(void)dealloc
{
    [m_updateQueue release];
    [super dealloc];
}

-(void)startAccelerometer
{
    CMMotionManager *motionManager = [QIOSMotionManager sharedManager];

    if (motionManager.deviceMotionAvailable) {
        [motionManager startAccelerometerUpdatesToQueue:m_updateQueue withHandler:^(CMAccelerometerData *data, NSError *error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                Q_UNUSED(error);
                CMAcceleration acc = data.acceleration;
                // Convert from G to m/s2, and flip axes:
                const qreal G = 9.8066;
                qreal x = qreal(acc.x) * G * -1;
                qreal y = qreal(acc.y) * G * -1;
                qreal z = qreal(acc.z) * G * -1;
                // Convert from NSTimeInterval to microseconds:
                quint64 timestamp = quint64(data.timestamp * 1000000);
                m_qiosAccelerometer->readingsChanged(timestamp, x, y, z);
            });
        }];
    }
}

-(void)stopAccelerometer
{
    [[QIOSMotionManager sharedManager] stopAccelerometerUpdates];
}

-(void)setInterval:(NSTimeInterval) interval
{
    [QIOSMotionManager sharedManager].accelerometerUpdateInterval = interval;
}

@end

QT_BEGIN_NAMESPACE

IOSAccelerometer::IOSAccelerometer(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_listener([[QtIoAccelListener alloc] initWithQIOSAccelerometer:this])
{
    setReading<QAccelerometerReading>(&m_reading);
    addDataRate(1, 100); // 100Hz
    addOutputRange(-22.418, 22.418, 0.17651); // 2G
}

IOSAccelerometer::~IOSAccelerometer()
{
    [m_listener dealloc];
}

void IOSAccelerometer::start()
{
    [m_listener startAccelerometer];
}

void IOSAccelerometer::stop()
{
    [m_listener stopAccelerometer];
}

void IOSAccelerometer::readingsChanged(quint64 ts, qreal x, qreal y, qreal z)
{
    m_reading.setTimestamp(ts);
    m_reading.setX(x);
    m_reading.setY(y);
    m_reading.setZ(z);

    newReadingAvailable();
}

QT_END_NAMESPACE
