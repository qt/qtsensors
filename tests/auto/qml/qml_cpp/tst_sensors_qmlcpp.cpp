// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QtCore/QDebug>

#include <QtTest/private/qpropertytesthelper_p.h>
#include <QtSensorsQuick/private/qmlsensor_p.h>
// #include <QtSensorsQuick/private/qmlsensorgesture_p.h>

#include "qtemplategestureplugin.h"
#include "qtemplaterecognizer.h"
#include <qsensorgesturemanager.h>
#include <qsensorbackend.h>
#include "qsensormanager.h"

#include "../../common/test_backends.h"
#include <QtSensorsQuick/private/qmlaccelerometer_p.h>
#include <QtSensorsQuick/private/qmlpressuresensor_p.h>
#include <QtSensorsQuick/private/qmlgyroscope_p.h>
#include <QtSensorsQuick/private/qmltapsensor_p.h>
#include <QtSensorsQuick/private/qmlcompass_p.h>
#include <QtSensorsQuick/private/qmlproximitysensor_p.h>
#include <QtSensorsQuick/private/qmlorientationsensor_p.h>
#include <QtSensorsQuick/private/qmlambientlightsensor_p.h>
#include <QtSensorsQuick/private/qmlmagnetometer_p.h>
#include <QtSensorsQuick/private/qmllidsensor_p.h>
#include <QtSensorsQuick/private/qmltiltsensor_p.h>
#include <QtSensorsQuick/private/qmlrotationsensor_p.h>
#include <QtSensorsQuick/private/qmlhumiditysensor_p.h>
#include <QtSensorsQuick/private/qmlambienttemperaturesensor_p.h>
#include <QtSensorsQuick/private/qmllightsensor_p.h>
#include <QtSensorsQuick/private/qmlirproximitysensor_p.h>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

class tst_sensors_qmlcpp : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testReadingBindings();
    // void testGesture();
    void testSensorRanges();
};

void tst_sensors_qmlcpp::initTestCase()
{
    qputenv("QT_SENSORS_LOAD_PLUGINS", "0"); // Do not load plugins
}

template<typename SensorClass, typename ReadingClass, typename ValueType>
void testSensorReadings(const char* identifier, const QVariantMap& values)
{
    SensorClass sensor;
    sensor.setIdentifier(identifier);
    sensor.componentComplete();
    sensor.start();

    for (const auto& key : values.keys()) {
        ValueType initialValue = values[key].toList()[0].value<ValueType>();
        ValueType changedValue = values[key].toList()[1].value<ValueType>();
        QTestPrivate::testReadOnlyPropertyBasics<ReadingClass, ValueType>(
                    *static_cast<ReadingClass*>(sensor.reading()),
                    initialValue, changedValue, key.toStdString().c_str(),
                    [&](){ set_test_backend_reading(sensor.sensor(), {{key, changedValue}}); });
        if (QTest::currentTestFailed()) {
            qWarning() << identifier << "::" << key << "test failed.";
            return;
        }
    }
}

void tst_sensors_qmlcpp::testReadingBindings()
{
    register_test_backends();

    testSensorReadings<QmlAccelerometer, QmlAccelerometerReading, qreal>(
                "QAccelerometer",
                {{"x", QVariantList{1.0, 2.0}},
                 {"y", QVariantList{1.0, 2.0}},
                 {"z", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlAccelerometer, QmlAccelerometerReading, quint64>(
                "QAccelerometer",
                {{"timestamp", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlAmbientLightSensor, QmlAmbientLightSensorReading, QAmbientLightReading::LightLevel>(
                "QAmbientLightSensor",
                {{"lightLevel", QVariantList{QAmbientLightReading::Twilight, QAmbientLightReading::Sunny}}});
    testSensorReadings<QmlPressureSensor, QmlPressureReading, qreal>(
                "QPressureSensor",
                {{"pressure", QVariantList{1.0, 2.0}},
                 {"temperature", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlGyroscope, QmlGyroscopeReading, qreal>(
                "QGyroscope",
                {{"x", QVariantList{1.0, 2.0}},
                 {"y", QVariantList{1.0, 2.0}},
                 {"z", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlTapSensor, QmlTapSensorReading, bool>(
                "QTapSensor",
                {{"doubleTap", QVariantList{true, false}}});
    testSensorReadings<QmlTapSensor, QmlTapSensorReading, QTapReading::TapDirection>(
                "QTapSensor",
                {{"tapDirection", QVariantList{QTapReading::Z_Both, QTapReading::X_Both}}});
    testSensorReadings<QmlCompass, QmlCompassReading, qreal>(
                "QCompass",
                {{"azimuth", QVariantList{1.0, 2.0}},
                 {"calibrationLevel", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlProximitySensor, QmlProximitySensorReading, bool>(
                "QProximitySensor",
                {{"near", QVariantList{true, false}}});
    testSensorReadings<QmlOrientationSensor, QmlOrientationSensorReading, QOrientationReading::Orientation>(
                "QOrientationSensor",
                {{"orientation", QVariantList{QOrientationReading::LeftUp, QOrientationReading::RightUp}}});
    testSensorReadings<QmlMagnetometer, QmlMagnetometerReading, qreal>(
                "QMagnetometer",
                {{"x", QVariantList{1.0, 2.0}},
                 {"y", QVariantList{1.0, 2.0}},
                 {"z", QVariantList{1.0, 2.0}},
                 {"calibrationLevel", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlLidSensor, QmlLidReading, bool>(
                "QLidSensor",
                {{"backLidClosed", QVariantList{true, false}},
                 {"frontLidClosed", QVariantList{true, false}}});
    testSensorReadings<QmlTiltSensor, QmlTiltSensorReading, qreal>(
                "QTiltSensor",
                {{"yRotation", QVariantList{1.0, 2.0}},
                 {"xRotation", QVariantList{1.0, 2.0}}});
    // rotation sensor properties need to be tested separately because the setter function is
    // not symmetric with getter functions ("setFromEuler()" vs. "x() & y() & z()")
    testSensorReadings<QmlRotationSensor, QmlRotationSensorReading, qreal>(
                "QRotationSensor",
                {{"x", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlRotationSensor, QmlRotationSensorReading, qreal>(
                "QRotationSensor",
                {{"y", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlRotationSensor, QmlRotationSensorReading, qreal>(
                "QRotationSensor",
                {{"z", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlHumiditySensor, QmlHumidityReading, qreal>(
                "QHumiditySensor",
                {{"relativeHumidity", QVariantList{1.0, 2.0}},
                 {"absoluteHumidity", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlAmbientTemperatureSensor, QmlAmbientTemperatureReading, qreal>(
                "QAmbientTemperatureSensor",
                {{"temperature", QVariantList{30.0, 40.0}}});
    testSensorReadings<QmlLightSensor, QmlLightSensorReading, qreal>(
                "QLightSensor",
                {{"illuminance", QVariantList{1.0, 2.0}}});
    testSensorReadings<QmlIRProximitySensor, QmlIRProximitySensorReading, qreal>(
                "QIRProximitySensor",
                {{"reflectance", QVariantList{0.5, 0.6}}});

    // The following tests QmlSensor (the baseclass) 'readingChanged' which is
    // emitted every time a sensor value changes. For that we instantiate a
    // concrete sensor. The actual 'reading' value (a QObject pointer) of the
    // 'readingChanged' property will not change, but rather the
    // 'readingChanged' is used to indicate that the value it contains has changed.
    QmlAccelerometer accelerometer;
    accelerometer.setIdentifier("QAccelerometer");
    accelerometer.componentComplete();
    accelerometer.start();
    QTestPrivate::testReadOnlyPropertyBasics<QmlSensor, QmlSensorReading*>(
                accelerometer, accelerometer.reading(), accelerometer.reading(), "reading",
                [&](){ set_test_backend_reading(accelerometer.sensor(), {{"x", 2.0}}); });

    unregister_test_backends();
}

/*
void tst_sensors_qmlcpp::testGesture()
{
    QTemplateGesturePlugin* plugin = new QTemplateGesturePlugin();
    QList <QSensorGestureRecognizer *> recognizers = plugin->createRecognizers();
    QSensorGestureManager manager;

    QmlSensorGesture* gs = new QmlSensorGesture(this);
    gs->componentComplete();
    QSignalSpy spy_availableGesturesChanged(gs, SIGNAL(availableGesturesChanged()));
    QSignalSpy spy_detected(gs, SIGNAL(detected(QString)));
    QSignalSpy spy_gesturesChanged(gs, SIGNAL(gesturesChanged()));
    QSignalSpy spy_validGesturesChanged(gs, SIGNAL(validGesturesChanged()));
    QSignalSpy spy_invalidGesturesChanged(gs, SIGNAL(invalidGesturesChanged()));
    QSignalSpy spy_enabledChanged(gs, SIGNAL(enabledChanged()));

    //This flag is needed if you run this unit test with an alread installed template plugin
    bool registered = false;
    for (int i = 0; i < recognizers.count(); i++){
        registered = manager.registerSensorGestureRecognizer(recognizers[i]);
    }
    if (registered) {
        QCOMPARE(spy_availableGesturesChanged.count(), 2);
    }

    //check creation of a not known plugin
    QCOMPARE(spy_invalidGesturesChanged.count(), 0);
    QCOMPARE(spy_gesturesChanged.count(), 0);
    gs->setGestures(QStringList() << "lollipop");
    QCOMPARE(spy_gesturesChanged.count(), 1);
    QCOMPARE(spy_invalidGesturesChanged.count(), 1);

    //check creation of a known plugin
    QCOMPARE(spy_validGesturesChanged.count(), 0);
    QCOMPARE(spy_gesturesChanged.count(), 1);
    spy_invalidGesturesChanged.clear();
    spy_validGesturesChanged.clear();
    gs->setGestures(QStringList() << "QtSensors.template");
    QCOMPARE(spy_gesturesChanged.count(), 2);
    QCOMPARE(spy_invalidGesturesChanged.count(), 1);
    QCOMPARE(spy_validGesturesChanged.count(), 1);

    //enable "QtSensors.template"
    QCOMPARE(spy_enabledChanged.count(), 0);
    QCOMPARE(spy_detected.count(), 0);
    gs->setEnabled(true);
    QCOMPARE(spy_enabledChanged.count(), 1);
    QCOMPARE(spy_detected.count(), 1);

    //set gesture during running sensor should not emit gesture changed
    spy_gesturesChanged.clear();
    gs->setGestures(QStringList() << "QtSensors.template2");
    QCOMPARE(spy_gesturesChanged.count(), 0);

    gs->setEnabled(false);

    QmlSensorGesture* gs1 = new QmlSensorGesture(this);
    QSignalSpy spy1_detected(gs1, SIGNAL(detected(QString)));
    QSignalSpy spy1_gesturesChanged(gs1, SIGNAL(gesturesChanged()));
    QSignalSpy spy1_validGesturesChanged(gs1, SIGNAL(validGesturesChanged()));
    QSignalSpy spy1_invalidGesturesChanged(gs1, SIGNAL(invalidGesturesChanged()));
    QSignalSpy spy1_enabledChanged(gs1, SIGNAL(enabledChanged()));
    gs1->componentComplete();

    //set enable = true without gesture should
    gs1->setEnabled(true);
    QCOMPARE(spy1_enabledChanged.count(), 1);
    gs1->setEnabled(false);
    spy1_enabledChanged.clear();

    //reding gestures check if we get back an empty string list
    QStringList gestures = gs1->gestures();
    QCOMPARE(gestures.count(), 0);
    QStringList validgestures = gs1->validGestures();
    QCOMPARE(validgestures.count(), 0);
    QStringList invalidgestures = gs1->invalidGestures();
    QCOMPARE(invalidgestures.count(), 0);

    //check types "QtSensors.template" "QtSensors.template1" "lollipop"
    //expect valid 2 not available 1
    gestures << "QtSensors.template" << "QtSensors.template1" << "lollipop";
    gs1->setGestures(gestures);
    gestures = gs1->gestures();
    QCOMPARE(gestures.count(), 3);
    QCOMPARE(spy1_validGesturesChanged.count(), 1);
    QCOMPARE(spy1_invalidGesturesChanged.count(), 1);
    QCOMPARE(spy1_gesturesChanged.count(), 1);
    //set same gesture again should not emit gesture changed
    gs1->setGestures(gestures);
    QCOMPARE(spy1_gesturesChanged.count(), 1);

    spy1_gesturesChanged.clear();
    gestures.clear();
    gs1->setGestures(gestures);
    QCOMPARE(spy1_gesturesChanged.count(), 1);

    //enable "QtSensors.template" and "QtSensors.template1"
    gestures << "QtSensors.template" << "QtSensors.template1";
    gs1->setEnabled(false);
    gs1->setGestures(gestures);
    spy1_enabledChanged.clear();
    spy1_detected.clear();
    gs1->setEnabled(true);
    QCOMPARE(spy1_enabledChanged.count(), 1);
    QCOMPARE(spy1_detected.count(), 2);
    gs1->setEnabled(false);

    //check sensor shouldn't run until the componentComplete gets called
    QmlSensorGesture* gs2 = new QmlSensorGesture(this);
    QSignalSpy spy2_detected(gs2, SIGNAL(detected(QString)));
    gs2->setGestures(QStringList() << "QtSensors.template");
    gs2->setEnabled(true);
    QCOMPARE(spy2_detected.count(), 0);
    gs2->componentComplete();
    QCOMPARE(spy2_detected.count(), 1);
}

*/

class QDummySensorBackend : public QSensorBackend
{
    Q_OBJECT
public:
    QDummySensorBackend(QSensor *sensor) : QSensorBackend(sensor)
    {
        addDataRate(2, 3);
        addDataRate(5, 7);
        addOutputRange(100, 200, 1);
        addOutputRange(600, 700, 10);
        addOutputRange(0, 1, 2);
    }

    void start() override {}
    void stop() override {}
};

class QDummySensorReading : public QSensorReading
{
    Q_OBJECT
public:
    QDummySensorReading(QObject *parent) : QSensorReading(parent, nullptr) {}
};

class QmlDummySensorReading : public QmlSensorReading
{
    Q_OBJECT
public:
    QmlDummySensorReading() :
        m_reading(new QDummySensorReading(this))
    {}

    QSensorReading *reading() const override { return m_reading; }
    void readingUpdate() override {}

private:
    QSensorReading *m_reading = nullptr;
};

class QmlDummySensor : public QmlSensor
{
    Q_OBJECT
public:
    QmlDummySensor(QObject *parent = nullptr) :
        QmlSensor(parent),
        m_sensor(new QSensor("dummy", this))
    {
        QDummySensorBackend b(m_sensor);
        Q_UNUSED(b);
    }

    QSensor *sensor() const override { return m_sensor; }
    QmlSensorReading *createReading() const override { return new QmlDummySensorReading(); }

    void componentComplete() override { QmlSensor::componentComplete(); }

private:
    QSensor *m_sensor = nullptr;
};

void tst_sensors_qmlcpp::testSensorRanges()
{
    QScopedPointer<QmlDummySensor> qmlSensor(new QmlDummySensor);
    qmlSensor->componentComplete();

    auto ranges = qmlSensor->availableDataRates();
    QCOMPARE(ranges.count(&ranges), 2);

    const auto range0 = ranges.at(&ranges, 0);
    QCOMPARE(range0->minimum(), 2);
    QCOMPARE(range0->maximum(), 3);
    QSignalSpy range0Spy(range0, SIGNAL(destroyed()));

    const auto range1 = ranges.at(&ranges, 1);
    QCOMPARE(range1->minimum(), 5);
    QCOMPARE(range1->maximum(), 7);
    QSignalSpy range1Spy(range1, SIGNAL(destroyed()));

    auto outputs = qmlSensor->outputRanges();
    QCOMPARE(outputs.count(&outputs), 3);

    const auto output0 = outputs.at(&outputs, 0);
    QCOMPARE(output0->minimum(), 100);
    QCOMPARE(output0->maximum(), 200);
    QCOMPARE(output0->accuracy(), 1);
    QSignalSpy output0Spy(output0, SIGNAL(destroyed()));

    const auto output1 = outputs.at(&outputs, 1);
    QCOMPARE(output1->minimum(), 600);
    QCOMPARE(output1->maximum(), 700);
    QCOMPARE(output1->accuracy(), 10);
    QSignalSpy output1Spy(output1, SIGNAL(destroyed()));

    const auto output2 = outputs.at(&outputs, 2);
    QCOMPARE(output2->minimum(), 0);
    QCOMPARE(output2->maximum(), 1);
    QCOMPARE(output2->accuracy(), 2);
    QSignalSpy output2Spy(output2, SIGNAL(destroyed()));

    qmlSensor.reset();
    QCOMPARE(range0Spy.size(), 1);
    QCOMPARE(range1Spy.size(), 1);
    QCOMPARE(output0Spy.size(), 1);
    QCOMPARE(output1Spy.size(), 1);
    QCOMPARE(output2Spy.size(), 1);
}

QT_END_NAMESPACE

QTEST_MAIN(tst_sensors_qmlcpp)
#include "tst_sensors_qmlcpp.moc"
