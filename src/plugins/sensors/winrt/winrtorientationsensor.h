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
