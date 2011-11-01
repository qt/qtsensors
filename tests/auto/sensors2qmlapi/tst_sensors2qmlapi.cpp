/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QtCore/QDebug>
#include "../../../src/imports/sensors2/qsensor2ambientlight.h"
#include "../../../src/imports/sensors2/qsensor2proximity.h"
#include "../../../src/imports/sensors2/qsensor2tilt.h"
#include "../../../src/imports/sensors2/qsensor2gesture.h"
#include "qtemplategestureplugin.h"
#include "qtemplaterecognizer.h"
#include <qsensorgesturemanager.h>
#include "qbackends.h"
#include "qsensormanager.h"

QT_USE_NAMESPACE
QDeclAccelerometer* TestSensorPlugin::stAccel = 0;
QDeclAmbientLightSensor* TestSensorPlugin::stAbl = 0;
QDeclProximitySensor* TestSensorPlugin::stProxi = 0;

Q_SENSORS_EXPORT void sensors_unit_test_hook(int index);

class tst_Sensors2QMLAPI : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testTilt_data();
    void testTilt();
    void testTilt_receivedSignalsCount();
    void testTiltSettings();
    void testTiltAccuracy();
    void testTiltCalibration();
    void testTiltRunningMode();
    void testTiltUnit();
    void testProximity();
    void testAmbientLight();
    void testGesture();

protected:
    TestSensorPlugin _plugin;
    QSensor2Tilt* _tilt;
};

void tst_Sensors2QMLAPI::initTestCase()
{
    sensors_unit_test_hook(0); // change some flags the library uses
    _plugin.registerSensors();
    _tilt = 0;
}

void tst_Sensors2QMLAPI::testProximity()
{
    QSensor2Proximity prox;
    QSignalSpy spy(&prox, SIGNAL(enabledChanged()));
    prox.setProperty("enabled", true);
    QCOMPARE(spy.count() , 1);

    spy.clear();
    prox.setProperty("enabled", true);
    QCOMPARE(spy.count() , 0);

    TestSensorPlugin plugin;
    QDeclProximitySensor* proxi = plugin.stProxi;

    proxi->test(true);
    bool expected = true;
    bool actual = prox.property("near").toBool();
    QCOMPARE(expected, actual);

    QSignalSpy spy1(&prox, SIGNAL(nearChanged()));
    proxi->test(false);
    QCOMPARE(spy1.count() , 1);
    expected = false;
    actual = prox.property("near").toBool();
    QCOMPARE(expected, actual);

    spy1.clear();
    proxi->test(false);
    QCOMPARE(spy1.count() , 0);
    prox.setProperty("enabled", false);
}

void tst_Sensors2QMLAPI::testAmbientLight()
{
    QSensor2AmbientLight als;
    QSignalSpy spy(&als, SIGNAL(enabledChanged()));
    als.setProperty("enabled", true);
    QCOMPARE(spy.count() , 1);

    spy.clear();
    als.setProperty("enabled", true);
    QCOMPARE(spy.count() , 0);

    TestSensorPlugin plugin;
    QDeclAmbientLightSensor* abl = plugin.stAbl;

    for (int en = 5; en >= 0; en--){
        QSignalSpy spy1(&als, SIGNAL(lightLevelChanged()));
        abl->test(static_cast<QSensor2AmbientLight::LightLevel>(en));
        QCOMPARE(spy1.count() , 1);
        int expected = en;
        int actual = als.property("lightLevel").toInt();
        if (expected != actual)
        QCOMPARE(expected, actual);

        spy1.clear();
        abl->test(static_cast<QSensor2AmbientLight::LightLevel>(en));
        QCOMPARE(spy1.count() , 0);
    }
    als.setProperty("enabled", false);
}

void tst_Sensors2QMLAPI::testTilt_data()
{
    QTest::addColumn<float>("pitch");
    QTest::addColumn<float>("roll");
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("z");
    QTest::addColumn<int>("xRotation");
    QTest::addColumn<int>("yRotation");

    //Face up
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("FaceUp1")    << 0.0f  << 0.0f  << 0    << 0    << 1    << 0    << 0;
    QTest::newRow("FaceUp2")    << 0.0f  << 0.0f  << 0    << 1    << 0    << 90   << 0;
    QTest::newRow("FaceUp3")    << 0.0f  << 0.0f  << 1    << 0    << 0    << 0    << -90;
    QTest::newRow("FaceUp4")    << 0.0f  << 0.0f  << 1    << 0    << 1    << 0    << -45;
    QTest::newRow("FaceUp5")    << 0.0f  << 0.0f  << 1    << 1    << 0    << 45   << -45;
    QTest::newRow("FaceUp6")    << 0.0f  << 0.0f  << 0    << 1    << 1    << 45   << 0;

    //top up roll = 90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("TopUp1")     << 0.0f  << 90.0f << 0    << 0    << 1    << -90  << 0;
    QTest::newRow("TopUp2")     << 0.0f  << 90.0f << 0    << 1    << 0    << 0    << 0;
    QTest::newRow("TopUp3")     << 0.0f  << 90.0f << 1    << 0    << 0    << -90  << -90;
    QTest::newRow("TopUp4")     << 0.0f  << 90.0f << 1    << 0    << 1    << -90  << -45;
    QTest::newRow("TopUp5")     << 0.0f  << 90.0f << 1    << 1    << 0    << -45  << -45;
    QTest::newRow("TopUp6")     << 0.0f  << 90.0f << 0    << 1    << 1    << -45  << 0;

    //top down roll = -90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("TopDown1")   << 0.0f  <<-90.0f << 0    << 0    << 1    << 90   << 0;
    QTest::newRow("TopDown2")   << 0.0f  <<-90.0f << 0    << 1    << 0    << 0    << 0;
    QTest::newRow("TopDown3")   << 0.0f  <<-90.0f << 1    << 0    << 0    << 90   << -90;
    QTest::newRow("TopDown4")   << 0.0f  <<-90.0f << 1    << 0    << 1    << 90   << -45;
    QTest::newRow("TopDown5")   << 0.0f  <<-90.0f << 1    << 1    << 0    << 45   << -45;
    QTest::newRow("TopDown6")   << 0.0f  <<-90.0f << 0    << 1    << 1    << 45   << 0;

    //Left up Pitch = -90 Roll = 90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("LeftUp1")    <<-90.0f << 90.0f << 0    << 0    << 1    << -90  << 90;
    QTest::newRow("LeftUp2")    <<-90.0f << 90.0f << 0    << 1    << 0    << 0    << 90;
    QTest::newRow("LeftUp3")    <<-90.0f << 90.0f << 1    << 0    << 0    << -90  << 0;
    QTest::newRow("LeftUp4")    <<-90.0f << 90.0f << 1    << 0    << 1    << -90  << 45;
    QTest::newRow("LeftUp5")    <<-90.0f << 90.0f << 1    << 1    << 0    << -45  << 45;
    QTest::newRow("LeftUp6")    <<-90.0f << 90.0f << 0    << 1    << 1    << -45  << 90;

    //Right up Pitch = -90 Roll = 90
    //                             Pitch  Roll      x       y       z       xRot    yRot
    QTest::newRow("RightUp1")    << 90.0f << 90.0f << 0    << 0    << 1    << -90  << -90;
    QTest::newRow("RightUp2")    << 90.0f << 90.0f << 0    << 1    << 0    << 0    << -90;
    QTest::newRow("RightUp3")    << 90.0f << 90.0f << 1    << 0    << 0    << -90  << 0;
    QTest::newRow("RightUp4")    << 90.0f << 90.0f << 1    << 0    << 1    << -90  << -45;
    QTest::newRow("RightUp5")    << 90.0f << 90.0f << 1    << 1    << 0    << -45  << -45;
    QTest::newRow("RightUp6")    << 90.0f << 90.0f << 0    << 1    << 1    << -45  << -90;

    //Face Down Pitch = -180 Roll = -180
    //                             Pitch   Roll     x       y       z       xRot    yRot
    QTest::newRow("FaceDown1")   <<-180.0f<<-180.0f<< 0    << 0    << 1    << 0    << 0;
    QTest::newRow("FaceDown2")   <<-180.0f<<-180.0f<< 0    << 1    << 0    << -90  << 0;
    QTest::newRow("FaceDown3")   <<-180.0f<<-180.0f<< 1    << 0    << 0    << 0    << 90;
    QTest::newRow("FaceDown4")   <<-180.0f<<-180.0f<< 1    << 0    << 1    << 0    << 45;
    QTest::newRow("FaceDown5")   <<-180.0f<<-180.0f<< 1    << 1    << 0    << -45  << 45;
    QTest::newRow("FaceDown6")   <<-180.0f<<-180.0f<< 0    << 1    << 1    << -45  << 0;
}

int xrotch = 0;
int yrotch = 0;
void tst_Sensors2QMLAPI::testTilt()
{
    QFETCH(float, pitch);
    QFETCH(float, roll);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, z);
    QFETCH(int, xRotation);
    QFETCH(int, yRotation);

    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QSignalSpy spy(_tilt, SIGNAL(enabledChanged()));
    _tilt->setProperty("enabled", true);
    QCOMPARE(spy.count() , 1);

    spy.clear();
    _tilt->setProperty("enabled", true);
    QCOMPARE(spy.count() , 0);

    _tilt->setProperty("unit", QSensor2Tilt::Radians);
    QSignalSpy spyunitch(_tilt, SIGNAL(unitChanged()));
    _tilt->setProperty("unit", QSensor2Tilt::Degrees);
    QCOMPARE(spyunitch.count() , 1);

    QByteArray settings;
    settings.append(QString::number(-5.0));
    settings.append(";");
    settings.append(QString::number(-5.0));
    _tilt->setProperty("settings", settings);

    QByteArray settings1;
    settings1.append(QString::number(pitch * M_PI / 180.0, 'g', 20));
    settings1.append(";");
    settings1.append(QString::number(roll * M_PI / 180.0, 'g', 20));
    _tilt->setProperty("settings", settings1);

    QDeclAccelerometer* accel = _plugin.stAccel;

    QSignalSpy spyxrot(_tilt, SIGNAL(xRotationChanged()));
    QSignalSpy spyyrot(_tilt, SIGNAL(yRotationChanged()));
    accel->test(x,y,z);
    xrotch += spyxrot.count();
    yrotch += spyyrot.count();

    QCOMPARE(xRotation, _tilt->property("xRotation").toInt());
    QCOMPARE(yRotation, _tilt->property("yRotation").toInt());

    spy.clear();
    _tilt->setProperty("enabled", false);
    QCOMPARE(spy.count() , 1);

    spy.clear();
    _tilt->setProperty("enabled", false);
    QCOMPARE(spy.count() , 0);
}

void tst_Sensors2QMLAPI::testTiltSettings()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QByteArray settings;
    settings.append(QString::number(-5.0));
    settings.append(";");
    settings.append(QString::number(-5.0));
    _tilt->setProperty("settings", settings);
    QByteArray val = _tilt->property("settings").toByteArray();
    QCOMPARE(settings, val);

    QByteArray settings1;
    settings1.append(QString::number(-6.0));
    settings1.append(":");
    settings1.append(QString::number(3.0));
    _tilt->setProperty("settings", settings1);
    val = _tilt->property("settings").toByteArray();
    QCOMPARE(settings, val);

    settings1.clear();
    settings1.append(":");
    _tilt->setProperty("settings", settings1);
    val = _tilt->property("settings").toByteArray();
    QCOMPARE(settings, val);

    settings1.clear();
    settings1.append("1;2;3");
    _tilt->setProperty("settings", settings1);
    val = _tilt->property("settings").toByteArray();
    QCOMPARE(settings, val);
}

void tst_Sensors2QMLAPI::testTiltAccuracy()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QByteArray settings;
    settings.append(QString::number(0.0));
    settings.append(";");
    settings.append(QString::number(0.0));
    _tilt->setProperty("settings", settings);
    _tilt->setProperty("enabled", true);

    QDeclAccelerometer* accel = _plugin.stAccel;

    //be sure we set rotation to 0
    _tilt->setProperty("accuracy", 0.0);
    QVERIFY(0.01 > _tilt->property("accuracy").toFloat());

    accel->test(0,0,1);

    //now set accuracy a little bigger then Pi / 4 in deg
    _tilt->setProperty("accuracy", 180 / 4.0 + 0.1);
    QSignalSpy spyxrot(_tilt, SIGNAL(xRotationChanged()));
    QSignalSpy spyyrot(_tilt, SIGNAL(yRotationChanged()));

    accel->test(1, 1, 0);
    QCOMPARE(spyxrot.count() , 0);
    QCOMPARE(spyyrot.count() , 0);

    spyxrot.clear();
    spyyrot.clear();
    _tilt->setProperty("accuracy", 180 / 4.0 + 0.1 - 0.1);
    accel->test(1, 1, 0);
    QCOMPARE(spyxrot.count() , 1);
    QCOMPARE(spyyrot.count() , 1);

}

void tst_Sensors2QMLAPI::testTilt_receivedSignalsCount()
{
    QCOMPARE(xrotch , 23);
    QCOMPARE(yrotch , 21);
}

void tst_Sensors2QMLAPI::testTiltCalibration()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QByteArray settings;
    settings.append(QString::number(0.0));
    settings.append(";");
    settings.append(QString::number(0.0));
    _tilt->setProperty("settings", settings);
    _tilt->setProperty("enabled", true);
    _tilt->setProperty("unit", QSensor2Tilt::Degrees);

    QDeclAccelerometer* accel = _plugin.stAccel;

    //be sure we set rotation to 0
    _tilt->setProperty("accuracy", 0.0);
    accel->test(-3.59904, 5.52114, 7.07059);
    _tilt->calibrate();
    accel->test(-3.59904, 5.52114, 7.07059);
    float xRotation = _tilt->property("xRotation").toFloat();
    float yRotation = _tilt->property("yRotation").toFloat();
    if (xRotation < 0.0) xRotation = -xRotation;
    if (yRotation < 0.0) yRotation = -yRotation;
    QVERIFY(xRotation < 0.001);
    QVERIFY(yRotation < 0.001);

    accel->test(0.519752, 6.82543, 7.06079);
    _tilt->calibrate();
    accel->test(0.539366, 6.79601, 7.0804);
    xRotation = _tilt->property("xRotation").toFloat();
    yRotation = _tilt->property("yRotation").toFloat();
    if (xRotation < 0.0) xRotation = -xRotation;
    if (yRotation < 0.0) yRotation = -yRotation;
    QVERIFY(xRotation < 0.25);
    QVERIFY(yRotation < 0.12);
    _tilt->setProperty("enabled", false);
}

void tst_Sensors2QMLAPI::testTiltUnit()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);
    QDeclAccelerometer* accel = _plugin.stAccel;
    _tilt->setProperty("enabled", false);
    _tilt->setProperty("accuracy", 0.0);
    _tilt->setProperty("unit", QVariant(QSensor2Tilt::Radians));
    accel->test(-3.59904, 5.52114, 7.07059);
    float xRotation = _tilt->property("xRotation").toFloat();
    float yRotation = _tilt->property("yRotation").toFloat();
    xRotation += 0.159136;
    yRotation -= 0.43440;
    QVERIFY(xRotation < 0.0001);
    QVERIFY(yRotation < 0.0001);
    QCOMPARE(_tilt->property("unit").toInt(), (int)QSensor2Tilt::Radians);

    _tilt->setProperty("unit", QVariant(QSensor2Tilt::Degrees));
    accel->test(-3.59904, 5.52114, 7.07059);
    xRotation = _tilt->property("xRotation").toFloat();
    yRotation = _tilt->property("yRotation").toFloat();
    xRotation += 9.11778;
    yRotation -= 24.8898;
    QVERIFY(xRotation < 0.0001);
    QVERIFY(yRotation < 0.0001);
    QCOMPARE(_tilt->property("unit").toInt(), (int)QSensor2Tilt::Degrees);
}

void tst_Sensors2QMLAPI::testTiltRunningMode()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);
    QDeclAccelerometer* accel = _plugin.stAccel;
    QCOMPARE(_tilt->_dataRate.count(), 0);
    accel->addDataRate(13, 15);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 13);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 13);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 15);

    accel->addDataRate(1, 8);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 8);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 15);

    accel->addDataRate(11, 12);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 11);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 15);

    accel->addDataRate(13, 18);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 11);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 18);

    accel->addDataRate(21, 31);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 11);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 21);

    accel->addDataRate(19, 20);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 11);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 20);

    accel->addDataRate(9, 10);
    _tilt->createRunModeDataRateMap();
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Slow), 2);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Medium), 10);
    QCOMPARE(_tilt->_dataRate.value(QSensor2Tilt::Fast), 20);

    QSensor2Tilt::Speed speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Slow);
    _tilt->setProperty("speed", QSensor2Tilt::Slow);

    QSignalSpy spymode(_tilt, SIGNAL(speedChanged()));
    _tilt->setProperty("speed", QSensor2Tilt::Slow);
    QCOMPARE(spymode.count() , 0);
    speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Slow);

    _tilt->setProperty("speed", QSensor2Tilt::Medium);
    QCOMPARE(spymode.count() , 1);
    spymode.clear();
    speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Medium);

    _tilt->setProperty("speed", QSensor2Tilt::Medium);
    QCOMPARE(spymode.count() , 0);
    speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Medium);

    _tilt->setProperty("speed", QSensor2Tilt::Fast);
    QCOMPARE(spymode.count() , 1);
    spymode.clear();
    speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Fast);

    _tilt->setProperty("speed", QSensor2Tilt::Fast);
    QCOMPARE(spymode.count() , 0);
    speed = static_cast<QSensor2Tilt::Speed>(_tilt->property("speed").toInt());
    QCOMPARE(speed, QSensor2Tilt::Fast);
}

void tst_Sensors2QMLAPI::testGesture()
{
    QTemplateGesturePlugin* plugin = new QTemplateGesturePlugin();
    QList <QSensorGestureRecognizer *> recognizers = plugin->createRecognizers();
    QSensorGestureManager manager;

    QSensor2Gesture* gs = new QSensor2Gesture(this);
    gs->componentComplete();
    qDebug() << "QSensor2Gesture gestures:";
    qDebug() << gs->availableGestures();
    QSignalSpy spy_availableGesturesChanged(gs, SIGNAL(availableGesturesChanged()));
    QSignalSpy spy_detected(gs, SIGNAL(detected(const QString)));
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

    QSensor2Gesture* gs1 = new QSensor2Gesture(this);
    QSignalSpy spy1_detected(gs1, SIGNAL(detected(const QString)));
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
    QSensor2Gesture* gs2 = new QSensor2Gesture(this);
    QSignalSpy spy2_detected(gs2, SIGNAL(detected(const QString)));
    gs2->setGestures(QStringList() << "QtSensors.template");
    gs2->setEnabled(true);
    QCOMPARE(spy2_detected.count(), 0);
    gs2->componentComplete();
    QCOMPARE(spy2_detected.count(), 1);
}


QTEST_MAIN(tst_Sensors2QMLAPI)
#include "tst_sensors2qmlapi.moc"
