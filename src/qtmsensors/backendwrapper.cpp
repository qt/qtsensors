#include "backendwrapper_p.h"
#include "qsensormanager_p.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
QTM_BEGIN_NAMESPACE

class WrapperFactory : public QSensorPluginInterface,
                       public QSensorBackendFactory
{
public:
    void registerSensors()
    {
        QList<QByteArray> types;
        types << QAccelerometer::type;
        types << QAmbientLightSensor::type;
        types << QCompass::type;
        types << QGyroscope::type;
        types << QLightSensor::type;
        types << QMagnetometer::type;
        types << QOrientationSensor::type;
        types << QProximitySensor::type;
        types << QRotationSensor::type;
        types << QTapSensor::type;
        foreach (const QByteArray &type, types) {
            foreach (const QByteArray &identifier, NEW_NAMESPACE(QSensor)::sensorsForType(type)) {
                QSensorManager::registerBackend(type, identifier, this);
            }
        }
    }

    QSensorBackend *createBackend(QSensor *sensor)
    {
        if (sensor->type() == QAccelerometer::type) {
            return new QAccelerometerWrapper(sensor);
        }
        if (sensor->type() == QAmbientLightSensor::type) {
            return new QAmbientLightSensorWrapper(sensor);
        }
        if (sensor->type() == QCompass::type) {
            return new QCompassWrapper(sensor);
        }
        if (sensor->type() == QGyroscope::type) {
            return new QGyroscopeWrapper(sensor);
        }
        if (sensor->type() == QLightSensor::type) {
            return new QLightSensorWrapper(sensor);
        }
        if (sensor->type() == QMagnetometer::type) {
            return new QMagnetometerWrapper(sensor);
        }
        if (sensor->type() == QOrientationSensor::type) {
            return new QOrientationSensorWrapper(sensor);
        }
        if (sensor->type() == QProximitySensor::type) {
            return new QProximitySensorWrapper(sensor);
        }
        if (sensor->type() == QRotationSensor::type) {
            return new QRotationSensorWrapper(sensor);
        }
        if (sensor->type() == QTapSensor::type) {
            return new QTapSensorWrapper(sensor);
        }
        return 0;
    }
};

REGISTER_STATIC_PLUGIN_V1(WrapperFactory)

QSensorWrapper::QSensorWrapper(QSensor *sensor)
    : QSensorBackend(sensor)
{
}

void QSensorWrapper::init(QObject *wsensor)
{
    connect(wsensor, SIGNAL(readingChanged()), this, SLOT(fetchData()));
    connect(wsensor, SIGNAL(sensorError(int)), this, SLOT(reportSensorError(int)));
    connect(wsensor, SIGNAL(busyChanged()), sensor(), SIGNAL(busyChanged()));
    m_wsensor = wsensor;
}

void QSensorWrapper::start()
{
    _start();
}

void QSensorWrapper::stop()
{
    _stop();
}

void QSensorWrapper::fetchData()
{
    _fetchData();
}

void QSensorWrapper::setProperty(const char *name, const QVariant &value)
{
    //qDebug() << "QSensorWrapper::setProperty" << name << value;
    QObject::setProperty(name, value);
    m_wsensor->setProperty(name, value);
}

QVariant QSensorWrapper::property(const char *name) const
{
    //qDebug() << "QSensorWrapper::property";
    return m_wsensor->property(name);
}

void QSensorWrapper::reportSensorError(int error)
{
    sensorError(error);
}

IMPLEMENT_WRAPPER(QAccelerometer, QAccelerometerReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setX(sensor->reading()->x());
                  m_reading.setY(sensor->reading()->y());
                  m_reading.setZ(sensor->reading()->z());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QAmbientLightSensor, QAmbientLightReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setLightLevel(static_cast<QAmbientLightReading::LightLevel>(sensor->reading()->lightLevel()));
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QCompass, QCompassReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setAzimuth(sensor->reading()->azimuth());
                  //m_reading.setCalibrationLevel(sensor->calibrationLevel());
                  m_reading.setCalibrationLevel(sensor->reading()->calibrationLevel());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QGyroscope, QGyroscopeReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setX(sensor->reading()->x());
                  m_reading.setY(sensor->reading()->y());
                  m_reading.setZ(sensor->reading()->z());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QLightSensor, QLightReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setLux(sensor->reading()->lux());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QMagnetometer, QMagnetometerReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setX(sensor->reading()->x());
                  m_reading.setY(sensor->reading()->y());
                  m_reading.setZ(sensor->reading()->z());
                  //m_reading.setCalibrationLevel(sensor->calibrationLevel());
                  m_reading.setCalibrationLevel(sensor->reading()->calibrationLevel());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QOrientationSensor, QOrientationReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setOrientation(static_cast<QOrientationReading::Orientation>(sensor->reading()->orientation()));
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QProximitySensor, QProximityReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setClose(sensor->reading()->close());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QRotationSensor, QRotationReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setX(sensor->reading()->x());
                  m_reading.setY(sensor->reading()->y());
                  m_reading.setZ(sensor->reading()->z());
                  newReadingAvailable();
                  })

IMPLEMENT_WRAPPER(QTapSensor, QTapReading, {
                  m_reading.setTimestamp(sensor->reading()->timestamp());
                  m_reading.setTapDirection(static_cast<QTapReading::TapDirection>(sensor->reading()->tapDirection()));
                  m_reading.setDoubleTap(sensor->reading()->isDoubleTap());
                  newReadingAvailable();
                  })

#include "moc_backendwrapper_p.cpp"
QTM_END_NAMESPACE
QT_END_NAMESPACE
