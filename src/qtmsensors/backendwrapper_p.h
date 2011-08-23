#ifndef BACKENDWRAPPER_P_H
#define BACKENDWRAPPER_P_H

#include "qsensorbackend_p.h"
#include "qaccelerometer.h"
#include <QtSensors/qaccelerometer.h>
#include "qambientlightsensor.h"
#include <QtSensors/qambientlightsensor.h>
#include "qcompass.h"
#include <QtSensors/qcompass.h>
#include "qgyroscope.h"
#include <QtSensors/qgyroscope.h>
#include "qlightsensor.h"
#include <QtSensors/qlightsensor.h>
#include "qmagnetometer.h"
#include <QtSensors/qmagnetometer.h>
#include "qorientationsensor.h"
#include <QtSensors/qorientationsensor.h>
#include "qproximitysensor.h"
#include <QtSensors/qproximitysensor.h>
#include "qrotationsensor.h"
#include <QtSensors/qrotationsensor.h>
#include "qtapsensor.h"
#include <QtSensors/qtapsensor.h>

QT_BEGIN_NAMESPACE
QTM_BEGIN_NAMESPACE

class QTM_SENSORS_EXPORT QSensorWrapper : public QSensorBackend
{
    Q_OBJECT
public:
    explicit QSensorWrapper(QSensor *sensor);

    void start();
    void stop();

    void setProperty(const char *name, const QVariant &value);
    QVariant property(const char *name) const;

    virtual bool _connect() = 0;

public slots:
    void fetchData();
    void reportSensorError(int);

protected:
    void init(QObject *wsensor);

private:
    virtual void _start() = 0;
    virtual void _stop() = 0;
    virtual void _fetchData() = 0;
protected:
    QObject *m_wsensor;
};

#define DECLARE_WRAPPER(sensorclass, readingclass)\
    class sensorclass ## Wrapper : public QSensorWrapper {\
    public:\
        explicit sensorclass ## Wrapper(QSensor *sensor);\
        void _start();\
        void _stop();\
        void _fetchData();\
        bool _connect();\
        readingclass m_reading;\
    };

#define IMPLEMENT_WRAPPER(sensorclass, readingclass, fetchfunc)\
    sensorclass ## Wrapper::sensorclass ## Wrapper(QSensor *wsensor) : QSensorWrapper(wsensor) {\
        setReading(&m_reading);\
        NEW_NAMESPACE(sensorclass) *sensor = new NEW_NAMESPACE(sensorclass)(this);\
        init(sensor);\
    }\
    bool sensorclass ## Wrapper::_connect() {\
        QSensor *wsensor = this->sensor();\
        NEW_NAMESPACE(sensorclass) *sensor = static_cast<NEW_NAMESPACE(sensorclass)*>(m_wsensor);\
        sensor->setIdentifier(wsensor->identifier());\
        sensor->connectToBackend();\
        setDescription(sensor->description());\
        foreach (const NEW_NAMESPACE(qoutputrange) &range, sensor->outputRanges()) {\
            addOutputRange(range.minimum, range.maximum, range.accuracy);\
        }\
        foreach (const NEW_NAMESPACE(qrange) &range, sensor->availableDataRates()) {\
            addDataRate(range.first, range.second);\
        }\
        return sensor->isConnectedToBackend();\
    }\
    void sensorclass ## Wrapper::_start() {\
        NEW_NAMESPACE(sensorclass) *sensor = static_cast<NEW_NAMESPACE(sensorclass)*>(m_wsensor);\
        if (!sensor->start()) {\
            if (sensor->isBusy()) sensorBusy();\
            sensorStopped();\
        }\
    }\
    void sensorclass ## Wrapper::_stop() { NEW_NAMESPACE(sensorclass) *sensor = static_cast<NEW_NAMESPACE(sensorclass)*>(m_wsensor); sensor->stop(); }\
    void sensorclass ## Wrapper::_fetchData() { NEW_NAMESPACE(sensorclass) *sensor = static_cast<NEW_NAMESPACE(sensorclass)*>(m_wsensor); fetchfunc }

DECLARE_WRAPPER(QAccelerometer, QAccelerometerReading)
DECLARE_WRAPPER(QAmbientLightSensor, QAmbientLightReading)
DECLARE_WRAPPER(QCompass, QCompassReading)
DECLARE_WRAPPER(QGyroscope, QGyroscopeReading)
DECLARE_WRAPPER(QLightSensor, QLightReading)
DECLARE_WRAPPER(QMagnetometer, QMagnetometerReading)
DECLARE_WRAPPER(QOrientationSensor, QOrientationReading)
DECLARE_WRAPPER(QProximitySensor, QProximityReading)
DECLARE_WRAPPER(QRotationSensor, QRotationReading)
DECLARE_WRAPPER(QTapSensor, QTapReading)

QTM_END_NAMESPACE
QT_END_NAMESPACE

#endif
