/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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
#include "iosmagnetometer.h"

QT_BEGIN_NAMESPACE

char const * const IOSMagnetometer::id("ios.magnetometer");

IOSMagnetometer::IOSMagnetometer(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_updateQueue([[NSOperationQueue alloc] init])
{
    setReading<QMagnetometerReading>(&m_reading);
    // Technical information about data rate is not found, but
    // seems to be ~70Hz after testing on iPad4:
    addDataRate(1, 70);
    // Output range is +/- 2 gauss (0.0002 tesla) and can sense magnetic fields less than
    // 100 microgauss (1e-08 tesla) Ref: "iOS Sensor Programming", Alasdair, 2012.
    addOutputRange(-0.0002, 0.0002, 1e-08);
}

IOSMagnetometer::~IOSMagnetometer()
{
    [m_updateQueue release];
}

void IOSMagnetometer::start()
{
    if (static_cast<QMagnetometer *>(sensor())->returnGeoValues())
        startDeviceMotion();
    else
        startMagnetometer();
}

void IOSMagnetometer::startMagnetometer()
{
    CMMotionManager *motionManager = [QIOSMotionManager sharedManager];
    // Convert Hz to NSTimeInterval:
    int hz = sensor()->dataRate();
    motionManager.magnetometerUpdateInterval = (hz == 0) ? 0 : 1. / hz;

    QPointer<QObject> self = this;
    [motionManager startMagnetometerUpdatesToQueue:m_updateQueue withHandler:^(CMMagnetometerData *data, NSError *error) {
        // NSOperationQueue is multi-threaded, so we process the data by queuing a callback to
        // the main application queue. By the time the callback executes, IOSMagnetometer might
        // have been deleted, so we need an extra QPointer check for that:
        dispatch_async(dispatch_get_main_queue(), ^{
            if (self) {
                Q_UNUSED(error);
                CMMagneticField field = data.magneticField;
                // Convert NSTimeInterval to microseconds and microtesla to tesla:
                m_reading.setTimestamp(quint64(data.timestamp * 1e6));
                m_reading.setX(qreal(field.x) / 1e6);
                m_reading.setY(qreal(field.y) / 1e6);
                m_reading.setZ(qreal(field.z) / 1e6);
                m_reading.setCalibrationLevel(1.0);
                newReadingAvailable();
            }
        });
    }];
}

void IOSMagnetometer::startDeviceMotion()
{
    CMMotionManager *motionManager = [QIOSMotionManager sharedManager];
    // Convert Hz to NSTimeInterval:
    int hz = sensor()->dataRate();
    motionManager.deviceMotionUpdateInterval = (hz == 0) ? 0 : 1. / hz;
    QPointer<QObject> self = this;

    [motionManager startDeviceMotionUpdatesUsingReferenceFrame:CMAttitudeReferenceFrameXArbitraryCorrectedZVertical
        toQueue:m_updateQueue withHandler:^(CMDeviceMotion *data, NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (self) {
                Q_UNUSED(error);
                CMCalibratedMagneticField calibratedField = data.magneticField;
                CMMagneticField field = calibratedField.field;
                field = motionManager.deviceMotion.magneticField.field;
                // Convert NSTimeInterval to microseconds and microtesla to tesla:
                m_reading.setTimestamp(quint64(data.timestamp * 1e6));
                m_reading.setX(qreal(field.x) / 1e6);
                m_reading.setY(qreal(field.y) / 1e6);
                m_reading.setZ(qreal(field.z) / 1e6);

                switch (calibratedField.accuracy) {
                case CMMagneticFieldCalibrationAccuracyUncalibrated:
                    m_reading.setCalibrationLevel(0.0);
                    break;
                case CMMagneticFieldCalibrationAccuracyLow:
                    m_reading.setCalibrationLevel(0.3);
                    break;
                case CMMagneticFieldCalibrationAccuracyMedium:
                    m_reading.setCalibrationLevel(0.6);
                    break;
                case CMMagneticFieldCalibrationAccuracyHigh:
                    m_reading.setCalibrationLevel(1.0);
                    break;
                }

                newReadingAvailable();
            }
        });
    }];
}

void IOSMagnetometer::stop()
{
    [[QIOSMotionManager sharedManager] stopMagnetometerUpdates];
    [[QIOSMotionManager sharedManager] stopDeviceMotionUpdates];
}

QT_END_NAMESPACE
