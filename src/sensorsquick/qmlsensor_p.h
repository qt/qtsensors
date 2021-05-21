/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMLSENSOR_P_H
#define QMLSENSOR_P_H

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

#include "qsensorsquickglobal_p.h"

#include <QObject>
#include <QQmlParserStatus>
#include <QtQml/qqml.h>
#include <QQmlListProperty>
#include "qmlsensorrange_p.h"

QT_BEGIN_NAMESPACE

class QSensor;
class QSensorReading;

class QmlSensorReading;

class QmlSensorPrivate;
class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensor : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QmlSensor)
    Q_ENUMS(AxesOrientationMode)
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
    Q_PROPERTY(AxesOrientationMode axesOrientationMode READ axesOrientationMode WRITE setAxesOrientationMode NOTIFY axesOrientationModeChanged REVISION 1)
    Q_PROPERTY(int currentOrientation READ currentOrientation NOTIFY currentOrientationChanged REVISION 1)
    Q_PROPERTY(int userOrientation READ userOrientation WRITE setUserOrientation NOTIFY userOrientationChanged REVISION 1)
    Q_PROPERTY(int maxBufferSize READ maxBufferSize NOTIFY maxBufferSizeChanged REVISION 1)
    Q_PROPERTY(int efficientBufferSize READ efficientBufferSize NOTIFY efficientBufferSizeChanged REVISION 1)
    Q_PROPERTY(int bufferSize READ bufferSize WRITE setBufferSize NOTIFY bufferSizeChanged REVISION 1)

    QML_NAMED_ELEMENT(Sensor)
    QML_UNCREATABLE("Cannot create Sensor")
    QML_ADDED_IN_VERSION(5,0)
public:
    // Keep in sync with QSensor::AxesOrientationMode
    enum AxesOrientationMode {
        FixedOrientation,
        AutomaticOrientation,
        UserOrientation
    };

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

    AxesOrientationMode axesOrientationMode() const;
    void setAxesOrientationMode(AxesOrientationMode axesOrientationMode);

    int currentOrientation() const;

    int userOrientation() const;
    void setUserOrientation(int userOrientation);

    int maxBufferSize() const;

    int efficientBufferSize() const;

    int bufferSize() const;
    void setBufferSize(int bufferSize);

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
    Q_REVISION(1) void skipDuplicatesChanged(bool skipDuplicates);
    Q_REVISION(1) void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode);
    Q_REVISION(1) void currentOrientationChanged(int currentOrientation);
    Q_REVISION(1) void userOrientationChanged(int userOrientation);
    Q_REVISION(1) void maxBufferSizeChanged(int maxBufferSize);
    Q_REVISION(1) void efficientBufferSizeChanged(int efficientBufferSize);
    Q_REVISION(1) void bufferSizeChanged(int bufferSize);

protected:
    virtual QSensor *sensor() const = 0;
    virtual QmlSensorReading *createReading() const = 0;

private Q_SLOTS:
    void updateReading();

protected Q_SLOTS:
    void componentComplete() override;

private:
    void classBegin() override;
    virtual void _update();
    bool m_parsed;
    bool m_active;
    QString m_identifier;
    QmlSensorReading *m_reading;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensorReading : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 timestamp READ timestamp NOTIFY timestampChanged)
    QML_NAMED_ELEMENT(SensorReading)
    QML_UNCREATABLE("Cannot create SensorReading")
    QML_ADDED_IN_VERSION(5,0)
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

#endif
