// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef OHOSSENSORBACKENDBASE_H
#define OHOSSENSORBACKENDBASE_H

#include <QSensorBackend>
#include <QtCore/private/qohoslogger_p.h>
#include <limits>
#include <ohossensorsmanager.h>

template<typename T>
class OhosSensorBackendBase : public QSensorBackend
{
public:
    OhosSensorBackendBase(QSensor *sensor, bool absoluteValueSensor = false);
    virtual ~OhosSensorBackendBase();

    void start() final;
    void stop() final;

protected:
    virtual void processSensorData(const OhosSensorData &sensorData) = 0;
    T m_reading;
};

template<typename T>
OhosSensorBackendBase<T>::OhosSensorBackendBase(QSensor *sensor, bool absoluteValueSensor)
    : QSensorBackend(sensor)
{
    setReading<T>(&m_reading);
    auto capabilities = OhosSensorsManager::instance()->tryGetSensorCapabilities(sensor);
    if (capabilities.has_value()) {
        auto capabilitiesData = capabilities.value();

        addOutputRange(
            absoluteValueSensor
                ? 0.0
                : std::numeric_limits<qreal>::lowest(),
            std::numeric_limits<qreal>::max(),
            capabilitiesData.resolution);

        addDataRate(capabilitiesData.minDataRate, capabilitiesData.maxDataRate);
    } else {
        qOhosPrintfError("%s: Cannot obtain sensor capabilities.", Q_FUNC_INFO);
    }
}

template<typename T>
OhosSensorBackendBase<T>::~OhosSensorBackendBase()
{
    stop();
}

template<typename T>
void OhosSensorBackendBase<T>::start()
{
    if (sensor()->dataRate() == 0) {
        constexpr int defaultDataRate = 5;
        auto availableDataRates = sensor()->availableDataRates();
        sensor()->setDataRate(
            !availableDataRates.isEmpty() && availableDataRates.first().first != 0
                ? availableDataRates.first().first
                : defaultDataRate);
    }

    OhosSensorsManager::instance()->subscribeSensor(
        sensor(),
        [this](const OhosSensorData &data) {
            processSensorData(data);
        });
}

template<typename T>
void OhosSensorBackendBase<T>::stop()
{
    OhosSensorsManager::instance()->unsubscribeSensor(sensor());
}

#endif
