/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

class tst_qtsensors5 : public QObject
{
    Q_OBJECT
public:
    tst_qtsensors5(QObject *parent = 0)
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

        QTest::newRow("version 5.0") << "5.0" << true;
    }

    void versions()
    {
        QFETCH(QString, version);
        QFETCH(bool, exists);

        QDeclarativeEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtSensors %1\nItem {}").arg(version);
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
            QString expected = QString("module \"QtSensors\" version %1 is not installed").arg(version);
            QString actual = errors.first().description();
            QCOMPARE(expected, actual);
        }
    }

    void elements_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<QString>("element");
        QTest::addColumn<bool>("exists");

        QTest::newRow("TiltSensor 5.0")         << "5.0" << "TiltSensor" << true;
        QTest::newRow("AmbientLightSensor 5.0") << "5.0" << "AmbientLightSensor" << true;
        QTest::newRow("ProximitySensor 5.0")    << "5.0" << "ProximitySensor" << true;
        QTest::newRow("SensorGesture 5.0")      << "5.0" << "SensorGesture" << true;
    }

    void elements()
    {
        QFETCH(QString, version);
        QFETCH(QString, element);
        QFETCH(bool, exists);

        QDeclarativeEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtSensors %1\n%2 {}").arg(version).arg(element);
        QDeclarativeComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        if (!exists)
            QTest::ignoreMessage(QtWarningMsg, "QDeclarativeComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(exists, (obj != 0));
        delete obj;
        QList<QDeclarativeError> errors = c.errors();
        QCOMPARE(errors.count(), 0);
    }

    void uncreatable_elements_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<QString>("element");

        QTest::newRow("Sensor 5.0")         << "5.0" << "Sensor";
    }

    void uncreatable_elements()
    {
        QFETCH(QString, version);
        QFETCH(QString, element);

        QDeclarativeEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtSensors %1\n%2 {}").arg(version).arg(element);
        QDeclarativeComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        //QTest::ignoreMessage(QtWarningMsg, "QDeclarativeComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(obj, static_cast<QObject*>(0));
        delete obj;
        QList<QDeclarativeError> errors = c.errors();
        QCOMPARE(errors.count(), 1);
        QString expected = QString("Cannot create %1").arg(element);
        QString actual = errors.first().description();
        QCOMPARE(expected, actual);
    }
};

QTEST_MAIN(tst_qtsensors5)

#include "tst_qtsensors5.moc"
