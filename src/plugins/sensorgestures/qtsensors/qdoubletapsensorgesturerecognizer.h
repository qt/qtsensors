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

#ifndef QDOUBLETAPSENSORGESTURERECOGNIZER_H
#define QDOUBLETAPSENSORGESTURERECOGNIZER_H

#include <QtSensors/QSensor>

#include <QtSensors/qsensorgesturerecognizer.h>
#include <QtSensors/QTapSensor>

#include "qtsensorgesturesensorhandler.h"

QT_BEGIN_NAMESPACE

class QDoubleTapSensorGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:
    explicit QDoubleTapSensorGestureRecognizer(QObject *parent = 0);
    ~QDoubleTapSensorGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

Q_SIGNALS:
    void doubletap();

private slots:
    void tapChanged(QTapReading *reading);

private:
    QTapSensor *tapSensor;
    bool active;

};
QT_END_NAMESPACE
#endif // QDOUBLETAPSENSORGESTURERECOGNIZER_H
