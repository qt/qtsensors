/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors middleware.
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
    QSignalSpy spy(&prox, SIGNAL(runningChanged()));
    prox.setProperty("running", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    prox.setProperty("running", QVariant(true));
    QCOMPARE(spy.count() , 0);

    TestSensorPlugin plugin;
    QDeclProximitySensor* proxi = plugin.stProxi;

    proxi->test(true);
    bool expected = true;
    bool actual = prox.property("close").toBool();
    QCOMPARE(expected, actual);

    QSignalSpy spy1(&prox, SIGNAL(closeChanged()));
    proxi->test(false);
    QCOMPARE(spy1.count() , 1);
    expected = false;
    actual = prox.property("close").toBool();
    QCOMPARE(expected, actual);

    spy1.clear();
    proxi->test(false);
    QCOMPARE(spy1.count() , 0);
    prox.setProperty("running", QVariant(false));
}

void tst_Sensors2QMLAPI::testAmbientLight()
{
    QSensor2AmbientLight als;
    QSignalSpy spy(&als, SIGNAL(runningChanged()));
    als.setProperty("running", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    als.setProperty("running", QVariant(true));
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
    als.setProperty("running", QVariant(false));
}

void tst_Sensors2QMLAPI::testTilt_data()
{
    QTest::addColumn<int>("pos");
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("z");
    QTest::addColumn<int>("xRotation");
    QTest::addColumn<int>("yRotation");

    QTest::newRow("TopUp001") << (int)QSensor2Tilt::TopUp << 0 << 0 << 1 << -90 << 0;
    QTest::newRow("TopDown001") << (int)QSensor2Tilt::TopDown << 0 << 0 << 1 << -90 << 0;
    QTest::newRow("LeftUp001") << (int)QSensor2Tilt::LeftUp << 0 << 0 << 1 << -90 << 0;
    QTest::newRow("RightUp001") << (int)QSensor2Tilt::RightUp << 0 << 0 << 1 << -90 << 0;
    QTest::newRow("FaceUp001") << (int)QSensor2Tilt::FaceUp << 0 << 0 << 1 << 0 << 0;
    QTest::newRow("FaceDown001") << (int)QSensor2Tilt::FaceDown << 0 << 0 << 1 << 0 << 0;

    QTest::newRow("TopUp010") << (int)QSensor2Tilt::TopUp << 0 << 1 << 0 << 0 << 0;
    QTest::newRow("TopDown010") << (int)QSensor2Tilt::TopDown << 0 << 1 << 0 << 0 << 0;
    QTest::newRow("LeftUp010") << (int)QSensor2Tilt::LeftUp << 0 << 1 << 0 << 0 << -90;
    QTest::newRow("RightUp010") << (int)QSensor2Tilt::RightUp << 0 << 1 << 0 << 0 << 90;
    QTest::newRow("FaceUp010") << (int)QSensor2Tilt::FaceUp << 0 << 1 << 0 << 90 << 0;
    QTest::newRow("FaceDown010") << (int)QSensor2Tilt::FaceDown << 0 << 1 << 0 << 90 << 0;

    QTest::newRow("TopUp100") << (int)QSensor2Tilt::TopUp << 1 << 0 << 0 << 0 << -90;
    QTest::newRow("TopDown100") << (int)QSensor2Tilt::TopDown << 1 << 0 << 0 << 0 << 90;
    QTest::newRow("LeftUp100") << (int)QSensor2Tilt::LeftUp << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("RightUp100") << (int)QSensor2Tilt::RightUp << 1 << 0 << 0 << 0 << 0;
    QTest::newRow("FaceUp100") << (int)QSensor2Tilt::FaceUp << 1 << 0 << 0 << 0 << -90;
    QTest::newRow("FaceDown100") << (int)QSensor2Tilt::FaceDown << 1 << 0 << 0 << 0 << 90;

    QTest::newRow("TopUp101") << (int)QSensor2Tilt::TopUp << 1 << 0 << 1 << -45 << -45;
    QTest::newRow("TopDown101") << (int)QSensor2Tilt::TopDown << 1 << 0 << 1 << -45 << 45;
    QTest::newRow("LeftUp101") << (int)QSensor2Tilt::LeftUp << 1 << 0 << 1 << -45 << 0;
    QTest::newRow("RightUp101") << (int)QSensor2Tilt::RightUp << 1 << 0 << 1 << -45 << 0;
    QTest::newRow("FaceUp101") << (int)QSensor2Tilt::FaceUp << 1 << 0 << 1 << 0 << -45;
    QTest::newRow("FaceDown101") << (int)QSensor2Tilt::FaceDown << 1 << 0 << 1 << 0 << 45;

    QTest::newRow("TopUp110") << (int)QSensor2Tilt::TopUp << 1 << 1 << 0 << 0 << -45;
    QTest::newRow("TopDown110") << (int)QSensor2Tilt::TopDown << 1 << 1 << 0 << 0 << 45;
    QTest::newRow("LeftUp110") << (int)QSensor2Tilt::LeftUp << 1 << 1 << 0 << 0 << -45;
    QTest::newRow("RightUp110") << (int)QSensor2Tilt::RightUp << 1 << 1 << 0 << 0 << 45;
    QTest::newRow("FaceUp110") << (int)QSensor2Tilt::FaceUp << 1 << 1 << 0 << 45 << -45;
    QTest::newRow("FaceDown110") << (int)QSensor2Tilt::FaceDown << 1 << 1 << 0 << 45 << 45;

    QTest::newRow("TopUp011") << (int)QSensor2Tilt::TopUp << 0 << 1 << 1 << -45 << 0;
    QTest::newRow("TopDown011") << (int)QSensor2Tilt::TopDown << 0 << 1 << 1 << -45 << 0;
    QTest::newRow("LeftUp011") << (int)QSensor2Tilt::LeftUp << 0 << 1 << 1 << -45 << -45;
    QTest::newRow("RightUp011") << (int)QSensor2Tilt::RightUp << 0 << 1 << 1 << -45 << 45;
    QTest::newRow("FaceUp011") << (int)QSensor2Tilt::FaceUp << 0 << 1 << 1 << 45 << 0;
    QTest::newRow("FaceDown011") << (int)QSensor2Tilt::FaceDown << 0 << 1 << 1 << 45 << 0;
}

int xrotch = 0;
int yrotch = 0;
int datarate = 10;
void tst_Sensors2QMLAPI::testTilt()
{
    QFETCH(int, pos);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, z);
    QFETCH(int, xRotation);
    QFETCH(int, yRotation);

    if (!_tilt)
        _tilt = new QSensor2Tilt(this);

    QSignalSpy spy(_tilt, SIGNAL(runningChanged()));
    _tilt->setProperty("running", QVariant(true));
    QCOMPARE(spy.count() , 1);

    spy.clear();
    _tilt->setProperty("running", QVariant(true));
    QCOMPARE(spy.count() , 0);

    _tilt->setProperty("radian", QVariant(false));

    QSignalSpy spymf(_tilt, SIGNAL(measureFromChanged()));
    _tilt->setProperty("measureFrom", QVariant(pos));
    QVERIFY((int)_tilt->property("measureFrom").toInt() == pos);
    QCOMPARE(spymf.count() , 1);
    spymf.clear();
    _tilt->setProperty("measureFrom", QVariant(pos));
    QCOMPARE(spymf.count() , 0);

    QDeclAccelerometer* accel = _plugin.stAccel;

    QSignalSpy spyxrot(_tilt, SIGNAL(xRotationChanged()));
    QSignalSpy spyyrot(_tilt, SIGNAL(yRotationChanged()));
    accel->test(x,y,z);
    xrotch += spyxrot.count();
    yrotch += spyyrot.count();

    QCOMPARE(xRotation, (int)_tilt->property("xRotation").toFloat());
    QCOMPARE(yRotation, (int)_tilt->property("yRotation").toFloat());

    spy.clear();
    _tilt->setProperty("running", QVariant(false));
    QCOMPARE(spy.count() , 1);
    spy.clear();
    _tilt->setProperty("running", QVariant(false));
    QCOMPARE(spy.count() , 0);

    datarate++;
    QSignalSpy spydr(_tilt, SIGNAL(dataRateChanged()));
    _tilt->setProperty("dataRate", QVariant(datarate));
    QCOMPARE(spydr.count() , 1);
}

void tst_Sensors2QMLAPI::testTilt_receivedSignalsCount()
{
    QCOMPARE(xrotch , 9);
    QCOMPARE(yrotch , 23);
}

QTEST_MAIN(tst_Sensors2QMLAPI)
#include "tst_sensors2qmlapi.moc"
