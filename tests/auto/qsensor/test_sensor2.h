// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef TEST_SENSOR2_H
#define TEST_SENSOR2_H

#include "qsensor.h"

#undef DECLARE_READING
#undef DECLARE_READING_D

template <typename T>
class qTypedWrapper
{
public:
    qTypedWrapper(QScopedPointer<QSensorReadingPrivate> *_ptr)
        : ptr(_ptr)
    {
    }

    T *operator->() const
    {
        return static_cast<T*>(ptr->data());
    }

private:
    QScopedPointer<QSensorReadingPrivate> *ptr;
};

#define DECLARE_READING(classname)\
        DECLARE_READING_D(classname, classname ## Private)

#define DECLARE_READING_D(classname, pclassname)\
    public:\
        classname(QObject *parent = 0);\
        virtual ~classname();\
        void copyValuesFrom(QSensorReading *other) override;\
    private:\
        qTypedWrapper<pclassname> d;

class TestSensor2ReadingPrivate;

class TestSensor2Reading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(int test READ test)
    DECLARE_READING(TestSensor2Reading)
public:
    int test() const;
    void setTest(int test);
};

class TestSensor2Filter : public QSensorFilter
{
public:
    virtual bool filter(TestSensor2Reading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override { return filter(static_cast<TestSensor2Reading*>(reading)); }
};

class TestSensor2 : public QSensor
{
    Q_OBJECT
public:
    explicit TestSensor2(QObject *parent = 0) : QSensor(TestSensor2::sensorType, parent) {}
    virtual ~TestSensor2() {}
    TestSensor2Reading *reading() const { return static_cast<TestSensor2Reading*>(QSensor::reading()); }
    static char const * const sensorType;
};

#endif
