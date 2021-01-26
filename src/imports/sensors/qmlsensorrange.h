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

#ifndef QMLSENSORRANGE_H
#define QMLSENSORRANGE_H

#include <QObject>

QT_BEGIN_NAMESPACE

class QmlSensorRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int minimum READ minimum)
    Q_PROPERTY(int maximum READ maximum)
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

class QmlSensorOutputRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum)
    Q_PROPERTY(qreal maximum READ maximum)
    Q_PROPERTY(qreal accuracy READ accuracy)
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
