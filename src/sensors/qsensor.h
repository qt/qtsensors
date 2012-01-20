/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSENSOR_H
#define QSENSOR_H

#include <QtSensors/qsensorsglobal.h>

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtCore/QPair>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QSensorPrivate;
class QSensorBackend;
class QSensorReading;
class QSensorReadingPrivate;
class QSensorFilter;

// This type is no longer used in the API but third party apps may be using it
typedef quint64 qtimestamp;

typedef QPair<int,int> qrange;
typedef QList<qrange> qrangelist;
struct qoutputrange
{
    qreal minimum;
    qreal maximum;
    qreal accuracy;
};
typedef QList<qoutputrange> qoutputrangelist;

class Q_SENSORS_EXPORT QSensor : public QObject
{
    friend class QSensorBackend;

    Q_OBJECT
    Q_PROPERTY(QByteArray sensorid READ identifier WRITE setIdentifier)
    Q_PROPERTY(QByteArray type READ type)
    Q_PROPERTY(bool connectedToBackend READ isConnectedToBackend)
    Q_PROPERTY(qrangelist availableDataRates READ availableDataRates)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate)
    Q_PROPERTY(QSensorReading* reading READ reading NOTIFY readingChanged)
    Q_PROPERTY(bool busy READ isBusy)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(qoutputrangelist outputRanges READ outputRanges)
    Q_PROPERTY(int outputRange READ outputRange WRITE setOutputRange)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(int error READ error NOTIFY sensorError)
    Q_PROPERTY(bool alwaysOn READ isAlwaysOn WRITE setAlwaysOn NOTIFY alwaysOnChanged REVISION 1)
#ifdef Q_QDOC
    Q_PROPERTY(int maxBufferSize)
    Q_PROPERTY(int efficientBufferSize)
    Q_PROPERTY(int bufferSize)
#endif
public:
    explicit QSensor(const QByteArray &type, QObject *parent = 0);
    virtual ~QSensor();

    QByteArray identifier() const;
    void setIdentifier(const QByteArray &identifier);

    QByteArray type() const;

    Q_INVOKABLE bool connectToBackend();
    bool isConnectedToBackend() const;

    bool isBusy() const;

    void setActive(bool active);
    bool isActive() const;

    bool isAlwaysOn() const;
    void setAlwaysOn(bool alwaysOn);

    qrangelist availableDataRates() const;
    int dataRate() const;
    void setDataRate(int rate);

    qoutputrangelist outputRanges() const;
    int outputRange() const;
    void setOutputRange(int index);

    QString description() const;
    int error() const;

    // Filters modify the reading
    void addFilter(QSensorFilter *filter);
    void removeFilter(QSensorFilter *filter);
    QList<QSensorFilter*> filters() const;

    // The readings are exposed via this object
    QSensorReading *reading() const;

    // Information about available sensors
    // These functions are implemented in qsensormanager.cpp
    static QList<QByteArray> sensorTypes();
    static QList<QByteArray> sensorsForType(const QByteArray &type);
    static QByteArray defaultSensorForType(const QByteArray &type);

public Q_SLOTS:
    // Start receiving values from the sensor
    bool start();

    // Stop receiving values from the sensor
    void stop();

Q_SIGNALS:
    void busyChanged();
    void activeChanged();
    void readingChanged();
    void sensorError(int error);
    void availableSensorsChanged();
    void alwaysOnChanged();

protected:
    // called by the back end
    QSensorPrivate *d_func() const { return d.data(); }

private:
    void registerInstance();

    QScopedPointer<QSensorPrivate> d;
    Q_DISABLE_COPY(QSensor)
};

class Q_SENSORS_EXPORT QSensorFilter
{
    friend class QSensor;
public:
    virtual bool filter(QSensorReading *reading) = 0;
protected:
    QSensorFilter();
    ~QSensorFilter();
    virtual void setSensor(QSensor *sensor);
    QSensor *m_sensor;
};

class Q_SENSORS_EXPORT QSensorReading : public QObject
{
    friend class QSensorBackend;

    Q_OBJECT
    Q_PROPERTY(quint64 timestamp READ timestamp)
public:
    virtual ~QSensorReading();

    quint64 timestamp() const;
    void setTimestamp(quint64 timestamp);

    // Access properties of sub-classes by numeric index
    // For name-based access use QObject::property()
    int valueCount() const;
    QVariant value(int index) const;

protected:
    explicit QSensorReading(QObject *parent, QSensorReadingPrivate *d);
    QScopedPointer<QSensorReadingPrivate> *d_ptr() { return &d; }
    virtual void copyValuesFrom(QSensorReading *other);

private:
    QScopedPointer<QSensorReadingPrivate> d;
    Q_DISABLE_COPY(QSensorReading)
};

#define DECLARE_READING(classname)\
        DECLARE_READING_D(classname, classname ## Private)

#define DECLARE_READING_D(classname, pclassname)\
    public:\
        classname(QObject *parent = 0);\
        virtual ~classname();\
        void copyValuesFrom(QSensorReading *other);\
    private:\
        QScopedPointer<pclassname> d;

#define IMPLEMENT_READING(classname)\
        IMPLEMENT_READING_D(classname, classname ## Private)

#define IMPLEMENT_READING_D(classname, pclassname)\
    classname::classname(QObject *parent)\
        : QSensorReading(parent, 0)\
        , d(new pclassname)\
        {}\
    classname::~classname() {}\
    void classname::copyValuesFrom(QSensorReading *_other)\
    {\
        /* No need to verify types, only called by QSensorBackend */\
        classname *other = static_cast<classname *>(_other);\
        pclassname *my_ptr = d.data();\
        pclassname *other_ptr = other->d.data();\
        /* Do a direct copy of the private class */\
        *(my_ptr) = *(other_ptr);\
        /* We need to copy the parent too */\
        QSensorReading::copyValuesFrom(_other);\
    }


QT_END_NAMESPACE
QT_END_HEADER

Q_DECLARE_METATYPE(qrange)
Q_DECLARE_METATYPE(qrangelist)
Q_DECLARE_METATYPE(qoutputrangelist)

#endif

