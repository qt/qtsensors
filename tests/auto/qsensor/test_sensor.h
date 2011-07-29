/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TEST_SENSOR_H
#define TEST_SENSOR_H

#include <qsensor.h>

class TestSensorReadingPrivate;

class TestSensorReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(int test READ test)
    DECLARE_READING(TestSensorReading)
public:
    int test() const;
    void setTest(int test);
};

class TestSensorFilter : public QSensorFilter
{
public:
    virtual bool filter(TestSensorReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<TestSensorReading*>(reading)); }
};

class TestSensor : public QSensor
{
    Q_OBJECT
public:
    explicit TestSensor(QObject *parent = 0)
        : QSensor(TestSensor::type, parent)
        , sensorsChangedEmitted(0)
    {
        connect(this, SIGNAL(availableSensorsChanged()), this, SLOT(s_availableSensorsChanged()));
    }
    virtual ~TestSensor() {}
    TestSensorReading *reading() const { return static_cast<TestSensorReading*>(QSensor::reading()); }
    static const char *type;

    // used by the testSensorsChangedSignal test function
    int sensorsChangedEmitted;
private slots:
    void s_availableSensorsChanged()
    {
        sensorsChangedEmitted++;
    }
};

#endif
