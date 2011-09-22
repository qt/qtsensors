#include <QtTest/QtTest>
#include <QtDeclarative/QtDeclarative>

class tst_legacy_sensors : public QObject
{
    Q_OBJECT
public:
    tst_legacy_sensors(QObject *parent = 0)
        : QObject(parent)
    {
    }

private slots:
    void initTestCase()
    {
    }

    void cleanupTestCase()
    {
    }

    void versions_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<bool>("exists");

        QTest::newRow("1.0") << "1.0" << false;
        QTest::newRow("1.1") << "1.1" << true;
        QTest::newRow("1.2") << "1.2" << true;
        QTest::newRow("1.3") << "1.3" << true;
    }

    void versions()
    {
        QFETCH(QString, version);
        QFETCH(bool, exists);

        QDeclarativeEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors %1\nItem {}").arg(version);
        QDeclarativeComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        if (!exists)
            QTest::ignoreMessage(QtWarningMsg, "QDeclarativeComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(exists, (obj != 0));
        delete obj;
        QList<QDeclarativeError> errors = c.errors();
        if (exists) {
            QCOMPARE(errors.count(), 0);
        } else {
            QCOMPARE(errors.count(), 1);
            QString expected = QString("module \"QtMobility.sensors\" version %1 is not installed").arg(version);
            QString actual = errors.first().description();
            QCOMPARE(expected, actual);
        }
    }

    void elements_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<QString>("element");
        QTest::addColumn<bool>("exists");

        QTest::newRow("") << "1.1" << "SensorReading" << false;
        QTest::newRow("") << "1.1" << "Accelerometer" << true;
        QTest::newRow("") << "1.1" << "AccelerometerReading" << true;
        QTest::newRow("") << "1.1" << "AmbientLightSensor" << true;
        QTest::newRow("") << "1.1" << "AmbientLightReading" << true;
        QTest::newRow("") << "1.1" << "Compass" << true;
        QTest::newRow("") << "1.1" << "CompassReading" << true;
        QTest::newRow("") << "1.1" << "Magnetometer" << true;
        QTest::newRow("") << "1.1" << "MagnetometerReading" << true;
        QTest::newRow("") << "1.1" << "OrientationSensor" << true;
        QTest::newRow("") << "1.1" << "OrientationReading" << true;
        QTest::newRow("") << "1.1" << "ProximitySensor" << true;
        QTest::newRow("") << "1.1" << "ProximityReading" << true;
        QTest::newRow("") << "1.1" << "RotationSensor" << true;
        QTest::newRow("") << "1.1" << "RotationReading" << true;
        QTest::newRow("") << "1.1" << "TapSensor" << true;
        QTest::newRow("") << "1.1" << "TapReading" << true;

        QTest::newRow("") << "1.2" << "SensorReading" << false;
        QTest::newRow("") << "1.2" << "Accelerometer" << true;
        QTest::newRow("") << "1.2" << "AccelerometerReading" << false;
        QTest::newRow("") << "1.2" << "AmbientLightSensor" << true;
        QTest::newRow("") << "1.2" << "AmbientLightReading" << false;
        QTest::newRow("") << "1.2" << "Compass" << true;
        QTest::newRow("") << "1.2" << "CompassReading" << false;
        QTest::newRow("") << "1.2" << "Magnetometer" << true;
        QTest::newRow("") << "1.2" << "MagnetometerReading" << false;
        QTest::newRow("") << "1.2" << "OrientationSensor" << true;
        QTest::newRow("") << "1.2" << "OrientationReading" << false;
        QTest::newRow("") << "1.2" << "ProximitySensor" << true;
        QTest::newRow("") << "1.2" << "ProximityReading" << false;
        QTest::newRow("") << "1.2" << "RotationSensor" << true;
        QTest::newRow("") << "1.2" << "RotationReading" << false;
        QTest::newRow("") << "1.2" << "TapSensor" << true;
        QTest::newRow("") << "1.2" << "TapReading" << false;
        QTest::newRow("") << "1.2" << "LightSensor" << true;
        QTest::newRow("") << "1.2" << "LightReading" << false;
        QTest::newRow("") << "1.2" << "Gyroscope" << true;
        QTest::newRow("") << "1.2" << "GyroscopeReading" << false;

        QTest::newRow("") << "1.3" << "SensorReading" << false;
        QTest::newRow("") << "1.3" << "Accelerometer" << true;
        QTest::newRow("") << "1.3" << "AccelerometerReading" << false;
        QTest::newRow("") << "1.3" << "AmbientLightSensor" << true;
        QTest::newRow("") << "1.3" << "AmbientLightReading" << false;
        QTest::newRow("") << "1.3" << "Compass" << true;
        QTest::newRow("") << "1.3" << "CompassReading" << false;
        QTest::newRow("") << "1.3" << "Magnetometer" << true;
        QTest::newRow("") << "1.3" << "MagnetometerReading" << false;
        QTest::newRow("") << "1.3" << "OrientationSensor" << true;
        QTest::newRow("") << "1.3" << "OrientationReading" << false;
        QTest::newRow("") << "1.3" << "ProximitySensor" << true;
        QTest::newRow("") << "1.3" << "ProximityReading" << false;
        QTest::newRow("") << "1.3" << "RotationSensor" << true;
        QTest::newRow("") << "1.3" << "RotationReading" << false;
        QTest::newRow("") << "1.3" << "TapSensor" << true;
        QTest::newRow("") << "1.3" << "TapReading" << false;
        QTest::newRow("") << "1.3" << "LightSensor" << true;
        QTest::newRow("") << "1.3" << "LightReading" << false;
        QTest::newRow("") << "1.3" << "Gyroscope" << true;
        QTest::newRow("") << "1.3" << "GyroscopeReading" << false;
        QTest::newRow("") << "1.3" << "IRProximitySensor" << true;
        QTest::newRow("") << "1.3" << "IRProximityReading" << false;
    }

    void elements()
    {
        QFETCH(QString, version);
        QFETCH(QString, element);
        QFETCH(bool, exists);

        QDeclarativeEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors %1\n%2 {}").arg(version).arg(element);
        QDeclarativeComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        if (!exists)
            QTest::ignoreMessage(QtWarningMsg, "QDeclarativeComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(exists, (obj != 0));
        delete obj;
        QList<QDeclarativeError> errors = c.errors();
        if (exists) {
            QCOMPARE(errors.count(), 0);
        } else {
            QCOMPARE(errors.count(), 1);
            QString expected = QString("Cannot create %1").arg(element);
            QString actual = errors.first().description();
            QCOMPARE(expected, actual);
        }
    }
};

QTEST_MAIN(tst_legacy_sensors)

#include "tst_legacy_sensors.moc"
