// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtCore>
#include <qsensor.h>

class Filter : public QSensorFilter
{
    int lastPercent;
public:
    Filter()
        : QSensorFilter()
        , lastPercent(0)
    {
    }

    bool filter(QSensorReading *reading) override
    {
        int percent = reading->property("chanceOfBeingEaten").value<int>();
        if (percent == 0) {
            qDebug() << "It is light. You are safe from Grues.";
        } else if (lastPercent == 0) {
            qDebug() << "It is dark. You are likely to be eaten by a Grue.";
        }
        if (percent == 100) {
            qDebug() << "You have been eaten by a Grue!";
            QCoreApplication::instance()->quit();
        } else if (percent)
            qDebug() << "Your chance of being eaten by a Grue:" << percent << "percent.";
        lastPercent = percent;
        return false;
    }
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QSensor sensor("GrueSensor");

    Filter filter;
    sensor.addFilter(&filter);
    sensor.start();

    if (!sensor.isActive()) {
        qWarning("The Grue sensor didn't start. You're on your own!");
        return 1;
    }

    return app.exec();
}

