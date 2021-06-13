/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtQuickTest>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtSensorsQuick/private/qmlsensor_p.h>
#include "../../common/test_backends.h"

class TestSetup : public QObject
{
    Q_OBJECT

public:
    TestSetup() {}

public slots:
    void qmlEngineAvailable(QQmlEngine *engine) {
        engine->rootContext()->setContextProperty("TestControl", this);
    }

    void registerTestBackends() {
        register_test_backends();
    }

    void unregisterTestBackends() {
        unregister_test_backends();
    }

    void setSensorReading(const QmlSensor* qmlSensor, const QVariantMap& values) {
        set_test_backend_reading(qmlSensor->sensor(), values);
    }

    void setSensorBusy(const QmlSensor* qmlSensor, bool busy) {
        set_test_backend_busy(qmlSensor->sensor(), busy);
    }
};

QUICK_TEST_MAIN_WITH_SETUP(tst_sensors_qmlquick, TestSetup)

#include "tst_sensors_qmlquick.moc"
