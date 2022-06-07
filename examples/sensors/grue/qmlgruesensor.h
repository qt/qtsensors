// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef QMLGRUESENSOR_H
#define QMLGRUESENSOR_H

#include <QtQml/qqml.h>
#include <QtSensors/qsensor.h>

class QMLGrueSensor : public QSensor
{
    Q_OBJECT
    QML_ELEMENT

public:
    QMLGrueSensor();
};

#endif // QMLGRUESENSOR_H
