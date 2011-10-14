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
    void testTiltAccuracy();
    void testTiltCalibration();
    void testTiltRunningMode();
    void testProximity();
    void testAmbientLight();

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
    prox.setProperty("enabled", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    prox.setProperty("enabled", QVariant(true));
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
    prox.setProperty("enabled", QVariant(false));
}

void tst_Sensors2QMLAPI::testAmbientLight()
{
    QSensor2AmbientLight als;
    QSignalSpy spy(&als, SIGNAL(enabledChanged()));
    als.setProperty("enabled", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    als.setProperty("enabled", QVariant(true));
    QCOMPARE(spy.count() , 0);

    TestSensorPlugin plugin;
    QDeclAmbientLightSensor* abl = plugin.stAbl;

    for (int en = 5; en >= 0; en--){
        QSignalSpy spy1(&als, SIGNAL(lightLevelChanged()));
        abl->test((QSensor2AmbientLight::LightLevel)en);
        QCOMPARE(spy1.count() , 1);
        int expected = en;
        int actual = als.property("lightLevel").toInt();
        if (expected != actual)
        QCOMPARE(expected, actual);

        spy1.clear();
        abl->test((QSensor2AmbientLight::LightLevel)en);
        QCOMPARE(spy1.count() , 0);
    }
    als.setProperty("enabled", QVariant(false));
}

void tst_Sensors2QMLAPI::testTilt_data()
{
    QTest::addColumn<qreal>("pitch");
    QTest::addColumn<qreal>("roll");
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("z");
    QTest::addColumn<int>("xRotation");
    QTest::addColumn<int>("yRotation");

    //Face up
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("FaceUp1")    << 0.0  << 0.0  << 0    << 0    << 1    << 0    << 0;
    QTest::newRow("FaceUp2")    << 0.0  << 0.0  << 0    << 1    << 0    << 90   << 0;
    QTest::newRow("FaceUp3")    << 0.0  << 0.0  << 1    << 0    << 0    << 0    << -90;
    QTest::newRow("FaceUp4")    << 0.0  << 0.0  << 1    << 0    << 1    << 0    << -45;
    QTest::newRow("FaceUp5")    << 0.0  << 0.0  << 1    << 1    << 0    << 45   << -45;
    QTest::newRow("FaceUp6")    << 0.0  << 0.0  << 0    << 1    << 1    << 45   << 0;

    //top up roll = 90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("TopUp1")     << 0.0  << 90.0 << 0    << 0    << 1    << -90  << 0;
    QTest::newRow("TopUp2")     << 0.0  << 90.0 << 0    << 1    << 0    << 0    << 0;
    QTest::newRow("TopUp3")     << 0.0  << 90.0 << 1    << 0    << 0    << -90  << -90;
    QTest::newRow("TopUp4")     << 0.0  << 90.0 << 1    << 0    << 1    << -90  << -45;
    QTest::newRow("TopUp5")     << 0.0  << 90.0 << 1    << 1    << 0    << -45  << -45;
    QTest::newRow("TopUp6")     << 0.0  << 90.0 << 0    << 1    << 1    << -45  << 0;

    //top down roll = -90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("TopDown1")   << 0.0  <<-90.0 << 0    << 0    << 1    << 90   << 0;
    QTest::newRow("TopDown2")   << 0.0  <<-90.0 << 0    << 1    << 0    << 0    << 0;
    QTest::newRow("TopDown3")   << 0.0  <<-90.0 << 1    << 0    << 0    << 90   << -90;
    QTest::newRow("TopDown4")   << 0.0  <<-90.0 << 1    << 0    << 1    << 90   << -45;
    QTest::newRow("TopDown5")   << 0.0  <<-90.0 << 1    << 1    << 0    << 45   << -45;
    QTest::newRow("TopDown6")   << 0.0  <<-90.0 << 0    << 1    << 1    << 45   << 0;

    //Left up Pitch = -90 Roll = 90
    //                             Pitch  Roll     x       y       z       xRot    yRot
    QTest::newRow("LeftUp1")    <<-90.0 << 90.0 << 0    << 0    << 1    << -90  << 90;
    QTest::newRow("LeftUp2")    <<-90.0 << 90.0 << 0    << 1    << 0    << 0    << 90;
    QTest::newRow("LeftUp3")    <<-90.0 << 90.0 << 1    << 0    << 0    << -90  << 0;
    QTest::newRow("LeftUp4")    <<-90.0 << 90.0 << 1    << 0    << 1    << -90  << 45;
    QTest::newRow("LeftUp5")    <<-90.0 << 90.0 << 1    << 1    << 0    << -45  << 45;
    QTest::newRow("LeftUp6")    <<-90.0 << 90.0 << 0    << 1    << 1    << -45  << 90;

    //Right up Pitch = -90 Roll = 90
    //                             Pitch  Roll      x       y       z       xRot    yRot
    QTest::newRow("RightUp1")    << 90.0 << 90.0 << 0    << 0    << 1    << -90  << -90;
    QTest::newRow("RightUp2")    << 90.0 << 90.0 << 0    << 1    << 0    << 0    << -90;
    QTest::newRow("RightUp3")    << 90.0 << 90.0 << 1    << 0    << 0    << -90  << 0;
    QTest::newRow("RightUp4")    << 90.0 << 90.0 << 1    << 0    << 1    << -90  << -45;
    QTest::newRow("RightUp5")    << 90.0 << 90.0 << 1    << 1    << 0    << -45  << -45;
    QTest::newRow("RightUp6")    << 90.0 << 90.0 << 0    << 1    << 1    << -45  << -90;

    //Face Down Pitch = -180 Roll = -180
    //                             Pitch   Roll     x       y       z       xRot    yRot
    QTest::newRow("FaceDown1")   <<-180.0<<-180.0<< 0    << 0    << 1    << 0    << 0;
    QTest::newRow("FaceDown2")   <<-180.0<<-180.0<< 0    << 1    << 0    << -90  << 0;
    QTest::newRow("FaceDown3")   <<-180.0<<-180.0<< 1    << 0    << 0    << 0    << 90;
    QTest::newRow("FaceDown4")   <<-180.0<<-180.0<< 1    << 0    << 1    << 0    << 45;
    QTest::newRow("FaceDown5")   <<-180.0<<-180.0<< 1    << 1    << 0    << -45  << 45;
    QTest::newRow("FaceDown6")   <<-180.0<<-180.0<< 0    << 1    << 1    << -45  << 0;
}

int xrotch = 0;
int yrotch = 0;
void tst_Sensors2QMLAPI::testTilt()
{
    QFETCH(qreal, pitch);
    QFETCH(qreal, roll);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, z);
    QFETCH(int, xRotation);
    QFETCH(int, yRotation);

    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QSignalSpy spy(_tilt, SIGNAL(enabledChanged()));
    _tilt->setProperty("enabled", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    _tilt->setProperty("enabled", QVariant(true));
    QCOMPARE(spy.count() , 0);

    _tilt->setProperty("unit", QVariant((int)QSensor2Tilt::Radians));
    QSignalSpy spyunitch(_tilt, SIGNAL(unitChanged()));
    _tilt->setProperty("unit", QVariant((int)QSensor2Tilt::Degrees));
    QCOMPARE(spyunitch.count() , 1);

    QByteArray settings;
    settings.append(QString::number((double)-5.0));
    settings.append(";");
    settings.append(QString::number((double)-5.0));
    _tilt->setProperty("settings", QVariant((QByteArray)settings));

    QByteArray settings1;
    settings1.append(QString::number((double)(pitch * M_PI / 180), 'g', 20));
    settings1.append(";");
    settings1.append(QString::number((double)(roll * M_PI / 180), 'g', 20));
    _tilt->setProperty("settings", QVariant((QByteArray)settings1));

    QDeclAccelerometer* accel = _plugin.stAccel;

    QSignalSpy spyxrot(_tilt, SIGNAL(xRotationChanged()));
    QSignalSpy spyyrot(_tilt, SIGNAL(yRotationChanged()));
    accel->test(x,y,z);
    xrotch += spyxrot.count();
    yrotch += spyyrot.count();

    QCOMPARE(xRotation, (int)_tilt->property("xRotation").toFloat());
    QCOMPARE(yRotation, (int)_tilt->property("yRotation").toFloat());

    spy.clear();
    _tilt->setProperty("enabled", QVariant(false));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    _tilt->setProperty("enabled", QVariant(false));
    QCOMPARE(spy.count() , 0);
}

void tst_Sensors2QMLAPI::testTiltAccuracy()
{
    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QByteArray settings;
    settings.append(QString::number((double)(0)));
    settings.append(";");
    settings.append(QString::number((double)(0)));
    _tilt->setProperty("settings", QVariant((QByteArray)settings));
    _tilt->setProperty("enabled", QVariant(true));

    QDeclAccelerometer* accel = _plugin.stAccel;

    //be sure we set rotation to 0
    _tilt->setProperty("accuracy", QVariant((double)0));
    accel->test(0,0,1);

    //now set accuracy a little bigger then Pi / 4 in deg
    _tilt->setProperty("accuracy", QVariant((double)180 / 4 + 0.1));
    QSignalSpy spyxrot(_tilt, SIGNAL(xRotationChanged()));
    QSignalSpy spyyrot(_tilt, SIGNAL(yRotationChanged()));

    accel->test(1, 1, 0);
    QCOMPARE(spyxrot.count() , 0);
    QCOMPARE(spyyrot.count() , 0);

    spyxrot.clear();
    spyyrot.clear();
    _tilt->setProperty("accuracy", QVariant((double)180 / 4 + 0.1 - 0.1));
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
    settings.append(QString::number((double)(0)));
    settings.append(";");
    settings.append(QString::number((double)(0)));
    _tilt->setProperty("settings", QVariant((QByteArray)settings));
    _tilt->setProperty("enabled", QVariant(true));
    _tilt->setProperty("unit", QVariant((int)QSensor2Tilt::Degrees));

    QDeclAccelerometer* accel = _plugin.stAccel;

    //be sure we set rotation to 0
    _tilt->setProperty("accuracy", QVariant((double)0));
    accel->test(-3.59904, 5.52114, 7.07059);
    _tilt->calibrate();
    accel->test(-3.59904, 5.52114, 7.07059);
    qreal xRotation = (qreal)_tilt->property("xRotation").toFloat();
    qreal yRotation = (qreal)_tilt->property("yRotation").toFloat();
    if (xRotation < 0) xRotation = -xRotation;
    if (yRotation < 0) yRotation = -yRotation;
    QVERIFY(xRotation < 0.001);
    QVERIFY(yRotation < 0.001);

    accel->test(0.519752, 6.82543, 7.06079);
    _tilt->calibrate();
    accel->test(0.539366, 6.79601, 7.0804);
    xRotation = (qreal)_tilt->property("xRotation").toFloat();
    yRotation = (qreal)_tilt->property("yRotation").toFloat();
    if (xRotation < 0) xRotation = -xRotation;
    if (yRotation < 0) yRotation = -yRotation;
    QVERIFY(xRotation < 0.25);
    QVERIFY(yRotation < 0.12);
    _tilt->setProperty("enabled", QVariant(false));
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

    accel->addDataRate(21, 25);
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

    QSensor2Tilt::Speed speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Slow);
    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Slow));

    QSignalSpy spymode(_tilt, SIGNAL(speedChanged()));
    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Slow));
    QCOMPARE(spymode.count() , 0);
    speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Slow);

    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Medium));
    QCOMPARE(spymode.count() , 1);
    spymode.clear();
    speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Medium);

    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Medium));
    QCOMPARE(spymode.count() , 0);
    speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Medium);

    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Fast));
    QCOMPARE(spymode.count() , 1);
    spymode.clear();
    speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Fast);

    _tilt->setProperty("speed", QVariant(QSensor2Tilt::Fast));
    QCOMPARE(spymode.count() , 0);
    speed = (QSensor2Tilt::Speed)_tilt->property("speed").toInt();
    QCOMPARE(speed, QSensor2Tilt::Fast);
}

QTEST_MAIN(tst_Sensors2QMLAPI)
#include "tst_sensors2qmlapi.moc"
