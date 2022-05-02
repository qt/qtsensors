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

#ifndef QMLSENSORRANGE_P_H
#define QMLSENSORRANGE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQml/qqml.h>
#include <QObject>
#include "qsensorsquickglobal_p.h"

QT_BEGIN_NAMESPACE

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensorRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int minimum READ minimum)
    Q_PROPERTY(int maximum READ maximum)
    QML_NAMED_ELEMENT(Range)
    QML_UNCREATABLE("Cannot create Range")
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlSensorRange(QObject *parent = 0);
    ~QmlSensorRange();

    int minimum() const;
    void setMinumum(int mini) { min = mini; }

    int maximum() const;
    void setMaximum(int maxi) { max = maxi; }

private:

    int min;
    int max;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensorOutputRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum)
    Q_PROPERTY(qreal maximum READ maximum)
    Q_PROPERTY(qreal accuracy READ accuracy)
    QML_NAMED_ELEMENT(OutputRange)
    QML_UNCREATABLE("Cannot create OutputRange")
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlSensorOutputRange(QObject *parent = 0);
    ~QmlSensorOutputRange();

    qreal minimum() const;
    void setMinimum(int mini) { min = mini; }

    qreal maximum() const;
    void setMaximum(int maxi) { max = maxi; }

    qreal accuracy() const;
    void setAccuracy(int accu) { acc = accu; }

private:
    qreal min;
    qreal max;
    qreal acc;
};

QT_END_NAMESPACE
#endif
