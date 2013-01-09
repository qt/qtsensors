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

#ifndef QMLSENSOR_H
#define QMLSENSOR_H

#include <QQmlParserStatus>
#include <QQmlListProperty>
#include "qmlsensorrange.h"

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QSensor;
class QSensorReading;

class QmlSensorReading;

class QmlSensor : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(bool connectedToBackend READ isConnectedToBackend NOTIFY connectedToBackendChanged)
    Q_PROPERTY(QQmlListProperty<QmlSensorRange> availableDataRates READ availableDataRates NOTIFY availableDataRatesChanged)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)
    Q_PROPERTY(QmlSensorReading* reading READ reading NOTIFY readingChanged)
    Q_PROPERTY(bool busy READ isBusy)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QQmlListProperty<QmlSensorOutputRange> outputRanges READ outputRanges NOTIFY outputRangesChanged)
    Q_PROPERTY(int outputRange READ outputRange WRITE setOutputRange NOTIFY outputRangeChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool alwaysOn READ isAlwaysOn WRITE setAlwaysOn NOTIFY alwaysOnChanged)
    Q_PROPERTY(bool skipDuplicates READ skipDuplicates WRITE setSkipDuplicates NOTIFY skipDuplicatesChanged REVISION 1)
public:
    explicit QmlSensor(QObject *parent = 0);
    ~QmlSensor();

    QString identifier() const;
    void setIdentifier(const QString &identifier);

    QString type() const;

    bool isConnectedToBackend() const;

    bool isBusy() const;

    void setActive(bool active);
    bool isActive() const;

    bool isAlwaysOn() const;
    void setAlwaysOn(bool alwaysOn);

    bool skipDuplicates() const;
    void setSkipDuplicates(bool skipDuplicates);

    QQmlListProperty<QmlSensorRange> availableDataRates() const;
    int dataRate() const;
    void setDataRate(int rate);

    QQmlListProperty<QmlSensorOutputRange> outputRanges() const;
    int outputRange() const;
    void setOutputRange(int index);

    QString description() const;
    int error() const;

    QmlSensorReading *reading() const;

public Q_SLOTS:
    bool start();
    void stop();

Q_SIGNALS:
    void identifierChanged();
    void typeChanged();
    void connectedToBackendChanged();
    void availableDataRatesChanged();
    void dataRateChanged();
    void readingChanged();
    void activeChanged();
    void outputRangesChanged();
    void outputRangeChanged();
    void descriptionChanged();
    void errorChanged();
    void alwaysOnChanged();
    void skipDuplicatesChanged(bool skipDuplicates);

protected:
    virtual QSensor *sensor() const = 0;
    virtual QmlSensorReading *createReading() const = 0;

private Q_SLOTS:
    void updateReading();
    void componentComplete();

private:
    void classBegin();
    virtual void _update();
    bool m_parsed;
    bool m_active;
    QString m_identifier;
    QmlSensorReading *m_reading;
};

class QmlSensorReading : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 timestamp READ timestamp NOTIFY timestampChanged)
public:
    explicit QmlSensorReading(QSensor *sensor);
    ~QmlSensorReading();

    quint64 timestamp() const;
    void update();

Q_SIGNALS:
    void timestampChanged();

private:
    virtual QSensorReading *reading() const = 0;
    virtual void readingUpdate() = 0;
    quint64 m_timestamp;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif
