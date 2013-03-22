/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
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

#include <CoreMotion/CMMotionManager.h>
#include <QPointer>

#include "iosmotionmanager.h"
#include "iosgyroscope.h"

char const * const IOSGyroscope::id("ios.gyroscope");

QT_BEGIN_NAMESPACE

IOSGyroscope::IOSGyroscope(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_updateQueue([[NSOperationQueue alloc] init])
{
    setReading<QGyroscopeReading>(&m_reading);
    addDataRate(1, 100); // 100Hz is max it seems
    addOutputRange(-360, 360, 0.01);
}

IOSGyroscope::~IOSGyroscope()
{
    [m_updateQueue release];
}

void IOSGyroscope::start()
{
    CMMotionManager *motionManager = [QIOSMotionManager sharedManager];
    // Convert Hz to NSTimeInterval:
    int hz = sensor()->dataRate();
    motionManager.gyroUpdateInterval = (hz == 0) ? 0 : 1. / hz;

    QPointer<QObject> self = this;
    [motionManager startGyroUpdatesToQueue:m_updateQueue withHandler:^(CMGyroData *data, NSError *error) {
        // NSOperationQueue is multi-threaded, so we process the data by queuing a callback to
        // the main application queue. By the time the callback executes, IOSAccelerometer might
        // have been deleted, so we need an extra QPointer check for that:
        dispatch_async(dispatch_get_main_queue(), ^{
            if (self) {
                Q_UNUSED(error);
                // Convert NSTimeInterval to microseconds and radians to degrees:
                CMRotationRate rate = data.rotationRate;
                m_reading.setTimestamp(quint64(data.timestamp * 1000000));
                m_reading.setX((qreal(rate.x) / M_PI) * 180);
                m_reading.setY((qreal(rate.y) / M_PI) * 180);
                m_reading.setZ((qreal(rate.z) / M_PI) * 180);
                newReadingAvailable();
            }
        });
    }];
}

void IOSGyroscope::stop()
{
    [[QIOSMotionManager sharedManager] stopGyroUpdates];
}

QT_END_NAMESPACE
