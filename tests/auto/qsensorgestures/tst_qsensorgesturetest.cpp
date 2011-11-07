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

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDebug>
#include <QVariant>
#include <QSignalSpy>

#include <qsensorgesture.h>
#include <qsensorgesturemanager.h>

#include <qsensorgesturerecognizer.h>
#include <qsensorgestureplugininterface.h>

static bool waitForSignal(QObject *obj, const char *signal, int timeout = 0)
{
    QEventLoop loop;
    QObject::connect(obj, signal, &loop, SLOT(quit()));
    QTimer timer;
    QSignalSpy timeoutSpy(&timer, SIGNAL(timeout()));
    if (timeout > 0) {
        QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.setSingleShot(true);
        timer.start(timeout);
    }
    loop.exec();
    return timeoutSpy.isEmpty();
}

class QTest3Recognizer : public QSensorGestureRecognizer
{
    Q_OBJECT

public:

    QTest3Recognizer(QObject *parent = 0);

    void create();

    QString id() const;
    bool start() ;
    bool stop();
    bool isActive();
    void changeId(const QString &);

    QString recognizerId;
};

QTest3Recognizer::QTest3Recognizer(QObject *parent) : QSensorGestureRecognizer(parent),
 recognizerId("QtSensors/test3"){}

void QTest3Recognizer::create(){}

QString QTest3Recognizer::id() const{ return recognizerId; }
bool QTest3Recognizer::start(){return true;}
bool QTest3Recognizer::stop() { return true;}
bool QTest3Recognizer::isActive() { return true; }
void QTest3Recognizer::changeId(const QString &id)
{
    recognizerId = id;
}


class GestureThread : public QThread
{
    Q_OBJECT
public:
    GestureThread(const QStringList &name) { ids = name;}
    ~GestureThread() { delete gesture; }
   void run()
    {
       gesture = new QSensorGesture(ids, this);
       QObject::connect(gesture,SIGNAL(detected(QString)),this,SIGNAL(detected(QString)));
       gesture->startDetection();
   }

    QSensorGesture *gesture;
    QStringList ids;

Q_SIGNALS:
    void detected(const QString &);
};

class Tst_qsensorgestureTest : public QObject
{
    Q_OBJECT

public:
    Tst_qsensorgestureTest();

private Q_SLOTS:

    void tst_recognizer_dup(); //comes first to weed out messages

    void tst_manager();
    void tst_manager_gestureids();
    void tst_manager_recognizerSignals();
    void tst_manager_registerSensorGestureRecognizer();
    void tst_manager__newSensorAvailable();

    void tst_sensor_gesture_signals();
    void tst_sensor_gesture_threaded();

    void tst_sensor_gesture();
    void tst_sensor_gesture_metacast();

    void tst_recognizer();

    void tst_sensorgesture_noid();

    void tst_sensor_gesture_multi();

    void shakeDetected(const QString &);

private:
    QString currentSignal;
};

Tst_qsensorgestureTest::Tst_qsensorgestureTest()
{
}

void Tst_qsensorgestureTest::tst_recognizer_dup()
{
    {
        QStringList idList;
        QTest::ignoreMessage(QtWarningMsg, "\"QtSensors.test.dup\" from the plugin \"TestGesturesDup\" is already known. ");
        QSensorGestureManager manager;
        idList = manager.gestureIds();

        for (int i = 0; i < idList.count(); i++) {
            if (idList.at(i) == "QtSensors.test.dup")

                QTest::ignoreMessage(QtWarningMsg, "Ignoring recognizer  \"QtSensors.test.dup\" from plugin \"TestGesturesDup\" because it is already registered ");
            QStringList recognizerSignalsList = manager.recognizerSignals(idList.at(i));

            QVERIFY(!recognizerSignalsList.contains("QtSensors.test2"));
        }

        QSensorGesture *sensorGesture = new QSensorGesture(idList, this);
        QVERIFY(sensorGesture->validIds().contains("QtSensors.test2"));
        QVERIFY(sensorGesture->validIds().contains("QtSensors.test"));
        QVERIFY(sensorGesture->validIds().contains("QtSensors.test.dup"));
        delete sensorGesture;
    }

    QSensorGesture *thisGesture;
    QString plugin;
    plugin = "QtSensors.test2";
    thisGesture = new QSensorGesture(QStringList() << plugin, this);
    QVERIFY(thisGesture->validIds().contains("QtSensors.test2"));

    plugin = "QtSensors.test.dup";
    thisGesture = new QSensorGesture(QStringList() << plugin, this);
    QVERIFY(!thisGesture->validIds().contains("QtSensors.test2"));
    delete thisGesture;
}

void Tst_qsensorgestureTest::tst_manager()
{
    QSensorGestureManager *manager2;
    manager2 = new QSensorGestureManager(this);
    QVERIFY(manager2 != 0);
    delete manager2;
}

void Tst_qsensorgestureTest::tst_manager_gestureids()
{
    {
        QStringList idList;
        QSensorGestureManager manager;
        idList = manager.gestureIds();

        QVERIFY(idList.count() > 0);

        QVERIFY(idList.contains("QtSensors.test"));
        QVERIFY(idList.contains("QtSensors.test2"));
        QVERIFY(idList.contains("QtSensors.test.dup"));
    }
}

void Tst_qsensorgestureTest::tst_manager_recognizerSignals()
{
    {
        QStringList idList;

        QSensorGestureManager manager;
        idList = manager.gestureIds();

        idList.removeOne("QtSensors.test.dup");

        for (int i = 0; i < idList.count(); i++) {

            QStringList recognizerSignalsList = manager.recognizerSignals(idList.at(i));

            if (idList.at(i) == "QtSensors.test") {
                QStringList signalList;
                signalList << "detected(QString)";
                signalList << "tested()";
                QVERIFY(recognizerSignalsList.count() == 2);

                QVERIFY(recognizerSignalsList == signalList);

            } else if (idList.at(i) == "QtSensors.test2") {
                QStringList signalList;
                signalList << "detected(QString)";
                signalList << "test2()";
                signalList << "test3(bool)";

                QVERIFY(recognizerSignalsList.count() == 3);
                QVERIFY(recognizerSignalsList == signalList);
            }
        }
    }
}

void Tst_qsensorgestureTest::tst_manager_registerSensorGestureRecognizer()
{
    QSensorGestureManager manager;
    int num = manager.gestureIds().count();
    QSensorGestureRecognizer *recognizer = new QTest3Recognizer;
    bool ok = manager.registerSensorGestureRecognizer(recognizer);
    QCOMPARE(ok, true);
    QVERIFY(num+1 == manager.gestureIds().count());

    recognizer = new QTest3Recognizer;
    QTest::ignoreMessage(QtWarningMsg, "\"QtSensors/test3\" is already known ");
    ok = manager.registerSensorGestureRecognizer(recognizer);
    QCOMPARE(ok, false);
    QVERIFY(num+1 == manager.gestureIds().count());
}

void Tst_qsensorgestureTest::tst_manager__newSensorAvailable()
{
    QSensorGestureManager manager;
    QSensorGestureManager manager2;

    QSignalSpy spy_manager_available(&manager, SIGNAL(newSensorGestureAvailable()));
    QSignalSpy spy_manager2_available(&manager2, SIGNAL(newSensorGestureAvailable()));

    manager.gestureIds();
    QCOMPARE(spy_manager_available.count(),0);
    QCOMPARE(spy_manager2_available.count(),0);

    QTest3Recognizer *recognizer = new QTest3Recognizer;
    recognizer->changeId("QtSensors.test4");

    bool ok = manager.registerSensorGestureRecognizer(recognizer);
    QCOMPARE(ok, true);
    QCOMPARE(spy_manager_available.count(),1);

    recognizer = new QTest3Recognizer;
    recognizer->changeId("QtSensors.test4");
    QTest::ignoreMessage(QtWarningMsg, "\"QtSensors.test4\" is already known ");
    ok = manager.registerSensorGestureRecognizer(recognizer);
    QCOMPARE(ok, false);
    QCOMPARE(spy_manager_available.count(),1);
    QCOMPARE(spy_manager2_available.count(),1);

    QSensorGesture *test4sg;
    test4sg = new QSensorGesture(QStringList() << "QtSensors.test4",this);
    QVERIFY(!test4sg->validIds().isEmpty());
    QVERIFY(test4sg->invalidIds().isEmpty());
}


void Tst_qsensorgestureTest::tst_sensor_gesture_signals()
{
    QStringList  testidList;
    testidList << "QtSensors.test";
    testidList << "QtSensors.test2";

    Q_FOREACH (const QString &plugin, testidList) {

        QSensorGesture *thisGesture;
        thisGesture = new QSensorGesture(QStringList() << plugin, this);

        QSignalSpy spy_gesture_detected(thisGesture, SIGNAL(detected(QString)));

        QSignalSpy *spy_gesture_tested;
        QSignalSpy *spy_gesture_test2;

        if (plugin == "QtSensors.test") {
            QStringList signalList;
            signalList << "detected(QString)";
            signalList << "tested()";

            QVERIFY(thisGesture->gestureSignals().count() == 2);
            QVERIFY(thisGesture->gestureSignals() == signalList);

            QVERIFY(thisGesture->gestureSignals().at(1) == "tested()");

            spy_gesture_tested = new QSignalSpy(thisGesture, SIGNAL(tested()));
        }

        if (plugin == "QtSensors.test2") {
            QStringList signalList;
            signalList << "detected(QString)";
            signalList << "test2()";
            signalList << "test3(bool)";
            QVERIFY(thisGesture->gestureSignals().count() == 3);
            QVERIFY(thisGesture->gestureSignals() == signalList);

            QCOMPARE(thisGesture->gestureSignals().at(1), QString("test2()"));
            spy_gesture_test2 = new QSignalSpy(thisGesture, SIGNAL(test2()));

        }

        QVERIFY(!thisGesture->validIds().isEmpty());
        thisGesture->startDetection();

        QCOMPARE(spy_gesture_detected.count(),1);

        if (plugin == "QtSensors.test") {
            QCOMPARE(spy_gesture_tested->count(),1);
            QList<QVariant> arguments ;
           arguments = spy_gesture_detected.takeFirst(); // take the first signal
           QCOMPARE(arguments.at(0),QVariant("tested"));
        }

        if (plugin == "QtSensors.test2") {
            QCOMPARE(spy_gesture_test2->count(),1);
        }

        delete thisGesture;
        thisGesture = 0;
    }

}


void Tst_qsensorgestureTest::tst_sensor_gesture_threaded()
{

    QSensorGesture *gesture = new QSensorGesture(QStringList() << "QtSensors.test", this);

    GestureThread *thread = new GestureThread( QStringList() << "QtSensors.test");

    currentSignal = gesture->gestureSignals().at(0).left(gesture->gestureSignals().at(0).indexOf("("));

    QSignalSpy thread_gesture(thread, SIGNAL(detected(QString)));
    QSignalSpy spy_gesture2(gesture, SIGNAL(detected(QString)));

    QCOMPARE(gesture->isActive(),false);
    gesture->startDetection();

    QCOMPARE(thread_gesture.count(),0);
    QCOMPARE(spy_gesture2.count(),1);

    QCOMPARE(gesture->isActive(),true);

    thread->run();
    QCOMPARE(thread->gesture->isActive(),true);

    QVERIFY(::waitForSignal(thread, SIGNAL(detected(QString)), 60 * 1000));

    QVERIFY(::waitForSignal(gesture, SIGNAL(detected(QString)), 60 * 1000));

    thread->gesture->stopDetection();

    QCOMPARE(thread->gesture->isActive(),false);
    QCOMPARE(gesture->isActive(),true);

    delete gesture;
    gesture = 0;
    delete thread;
    thread = 0;
}

void Tst_qsensorgestureTest::tst_sensor_gesture()
{
    QSensorGesture *gesture = new QSensorGesture(QStringList() << "QtSensors.test", this);

    QSensorGesture *gesture2 = new QSensorGesture(QStringList() << "QtSensors.test2", this);
    QSensorGesture *gesture3 = new QSensorGesture(QStringList() << "QtSensors.test2", this);

    QCOMPARE(gesture->validIds(),QStringList() << "QtSensors.test");

    QCOMPARE(gesture->gestureSignals().at(1).left(gesture->gestureSignals().at(1).indexOf("(")),QString("tested"));

    QVERIFY(gesture->invalidIds().isEmpty());
    QVERIFY(gesture2->invalidIds().isEmpty());
    QVERIFY(gesture3->invalidIds().isEmpty());

    currentSignal = gesture->gestureSignals().at(1).left(gesture->gestureSignals().at(1).indexOf("("));

    QSignalSpy spy_gesture(gesture, SIGNAL(detected(QString)));

    QSignalSpy spy_gesture2(gesture2, SIGNAL(detected(QString)));

    QSignalSpy spy_gesture3_detected(gesture3, SIGNAL(detected(QString)));

    QSignalSpy spy_gesture4_test2(gesture3, SIGNAL(test2()));
    QSignalSpy spy_gesture5_test3(gesture3, SIGNAL(test3(bool)));


    QCOMPARE(gesture->isActive(),false);
    gesture->startDetection();

    QCOMPARE(spy_gesture.count(),1);

    QCOMPARE(gesture->isActive(),true);
    QCOMPARE(gesture2->validIds(),QStringList() <<"QtSensors.test2");
    QCOMPARE(gesture2->gestureSignals().at(1).left(gesture2->gestureSignals().at(1).indexOf("(")),QString("test2"));
    currentSignal = gesture2->gestureSignals().at(1).left(gesture2->gestureSignals().at(1).indexOf("("));

    connect(gesture2,SIGNAL(detected(QString)),
            this,SLOT(shakeDetected(QString)));

    QCOMPARE(gesture2->isActive(),false);

    gesture2->startDetection();

    QCOMPARE(gesture2->isActive(),true);

    QCOMPARE(spy_gesture2.count(),1);

    QCOMPARE(spy_gesture3_detected.count(),0);

    gesture2->stopDetection();

    QCOMPARE(gesture2->isActive(),false);
    QCOMPARE(gesture3->isActive(),false);

    gesture3->startDetection();

    QCOMPARE(gesture3->isActive(),true);
    QCOMPARE(gesture2->isActive(),false);

    QCOMPARE(spy_gesture.count(),1);

    QCOMPARE(spy_gesture2.count(),1);


    QCOMPARE(spy_gesture3_detected.count(),1);

    QCOMPARE(spy_gesture4_test2.count(),1);

    QCOMPARE(spy_gesture5_test3.count(),1);

    QList<QVariant> arguments2 = spy_gesture5_test3.takeFirst();
    QVERIFY(arguments2.at(0).type() == QVariant::Bool);
    QVERIFY(arguments2.at(0) == true);

    delete gesture;
    gesture = 0;
    delete gesture2;
    gesture2 = 0;
    delete gesture3;
    gesture3 = 0;
}

void Tst_qsensorgestureTest::tst_sensor_gesture_metacast()
{
    QSensorGesture *gesture = new QSensorGesture(QStringList() << "QtSensors.test", this);
    // exercise qt_metacast
    QVERIFY(!gesture->inherits(""));
    QVERIFY(gesture->inherits("QObject"));

#if defined(QT_NO_QOBJECT_CHECK)
    QObject *o = qobject_cast<QObject *>(gesture);
    QVERIFY(o);

    //    this will fail in the compile time check for
    //    the Q_OBJECT macro in qobjectdefs.h unless QT_NO_QOBJECT_CHECK is defined,
    QSensorGesture *gest = qobject_cast<QSensorGesture *>(o);
    QVERIFY(!gest->gestureSignals().isEmpty());
#endif
    delete gesture;
}


void Tst_qsensorgestureTest::tst_recognizer()
{
    QSensorGesture *gesture = new QSensorGesture(QStringList() << "QtSensors.test", this);
    QSensorGesture *gesture2 = new QSensorGesture(QStringList() << "QtSensors.test", this);

    QSignalSpy spy_gesture(gesture, SIGNAL(detected(QString)));
    QSignalSpy spy_gesture2(gesture2, SIGNAL(detected(QString)));

    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(gesture2->isActive(),false);

    currentSignal = gesture2->gestureSignals().at(0).left(gesture2->gestureSignals().at(0).indexOf("("));

    gesture2->startDetection();//activate 2

    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(gesture2->isActive(),true);

    QCOMPARE(spy_gesture.count(),0);

    QCOMPARE(spy_gesture2.count(),1);

    QList<QVariant> arguments = spy_gesture2.takeFirst();
    QVERIFY(arguments.at(0) == "tested");

    QCOMPARE(spy_gesture2.count(),0);

    gesture->startDetection(); //activate 1

    QCOMPARE(gesture->isActive(),true);
    QCOMPARE(gesture2->isActive(),true);

    QVERIFY(::waitForSignal(gesture, SIGNAL(detected(QString)), 5 * 1000));
    QCOMPARE(spy_gesture.count(),1);

    QCOMPARE(spy_gesture2.count(),1);

    arguments = spy_gesture.takeFirst(); // take the first signal
    QVERIFY(arguments.at(0) == "tested");
    spy_gesture2.removeFirst();

    gesture->stopDetection(); //stop 1 gesture object

    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(gesture2->isActive(),true);

    gesture2->startDetection();

    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(spy_gesture.count(),0);

    QCOMPARE(gesture2->isActive(),true);

    QVERIFY(::waitForSignal(gesture2, SIGNAL(detected(QString)), 60 * 1000));

    delete gesture;
    gesture = 0;
    delete gesture2;
    gesture2 = 0;
}


void Tst_qsensorgestureTest::tst_sensorgesture_noid()
{
    QSensorGesture *gesture = new QSensorGesture(QStringList() << "QtSensors.noid", this);
    QVERIFY(gesture->validIds().isEmpty());
    QCOMPARE(gesture->invalidIds(), QStringList() << "QtSensors.noid");

    QTest::ignoreMessage(QtWarningMsg, "QSignalSpy: No such signal: 'detected(QString)'");
    QSignalSpy spy_gesture(gesture, SIGNAL(detected(QString)));

    QCOMPARE(spy_gesture.count(),0);

    gesture->startDetection();
    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(spy_gesture.count(),0);

    gesture->stopDetection();
    QCOMPARE(gesture->isActive(),false);
    QCOMPARE(spy_gesture.count(),0);

    QVERIFY(gesture->gestureSignals().isEmpty());

    QCOMPARE(gesture->invalidIds() ,QStringList() << "QtSensors.noid");

    QSensorGestureManager manager;
    QStringList recognizerSignalsList = manager.recognizerSignals( "QtSensors.noid");
    QVERIFY(recognizerSignalsList.isEmpty());

    QVERIFY(!recognizerSignalsList.contains("QtSensors.noid"));

    QSensorGestureRecognizer *fakeRecognizer = manager.sensorGestureRecognizer("QtSensors.noid");
    QVERIFY(!fakeRecognizer);

    delete gesture;
    gesture = 0;
}

void Tst_qsensorgestureTest::tst_sensor_gesture_multi()
{

    QStringList ids;
    ids << "QtSensors.test";
    ids <<"QtSensors.test2";
    ids << "QtSensors.bogus";

    QSensorGesture *gesture = new QSensorGesture(ids,this);
    QStringList gestureSignals = gesture->gestureSignals();

    gestureSignals.removeDuplicates() ;
    QVERIFY(gestureSignals == gesture->gestureSignals());

    QVERIFY(gesture->gestureSignals().count() == 4);
    QCOMPARE(gesture->invalidIds(), QStringList() << "QtSensors.bogus");

    QCOMPARE(gesture->isActive(),false);

    QSignalSpy spy_gesture_detected(gesture, SIGNAL(detected(QString)));
    gesture->startDetection();
    QCOMPARE(gesture->isActive(),true);
    QCOMPARE(spy_gesture_detected.count(),2);

    QList<QVariant> arguments ;
    arguments = spy_gesture_detected.takeAt(0);
    QVERIFY(arguments.at(0) == "tested");

    arguments = spy_gesture_detected.takeAt(0);
    QVERIFY(arguments.at(0) == "test2");

    QVERIFY(::waitForSignal(gesture, SIGNAL(detected(QString)), 60 * 1000));
    QCOMPARE(spy_gesture_detected.count(),1);

    gesture->stopDetection();

    QCOMPARE(gesture->isActive(),false);

    {
        QSensorGestureManager manager;
        QVERIFY(!manager.gestureIds().contains("QtSensors.bogus"));
        QSensorGestureRecognizer *recognizer = manager.sensorGestureRecognizer("QtSensors.bogus");
        QVERIFY(recognizer == NULL);
    }

}

void Tst_qsensorgestureTest::shakeDetected(const QString &type)
{
    QCOMPARE(type,currentSignal);
}

QTEST_MAIN(Tst_qsensorgestureTest);

#include "tst_qsensorgesturetest.moc"
