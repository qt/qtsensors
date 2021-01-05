#####################################################################
## SensortagSensorPlugin Plugin:
#####################################################################

qt_internal_add_plugin(SensortagSensorPlugin
    OUTPUT_NAME qtsensors_sensortag
    TYPE sensors
    SOURCES
        main.cpp
        sensortagaccelerometer.cpp sensortagaccelerometer.h
        sensortagals.cpp sensortagals.h
        sensortagbase.cpp sensortagbase.h
        sensortaggyroscope.cpp sensortaggyroscope.h
        sensortaghumiditysensor.cpp sensortaghumiditysensor.h
        sensortaglightsensor.cpp sensortaglightsensor.h
        sensortagmagnetometer.cpp sensortagmagnetometer.h
        sensortagpressuresensor.cpp sensortagpressuresensor.h
        sensortagtemperaturesensor.cpp sensortagtemperaturesensor.h
    PUBLIC_LIBRARIES
        Qt::Bluetooth
        Qt::Core
        Qt::SensorsPrivate
)

#### Keys ignored in scope 1:.:.:sensortag.pro:<TRUE>:
# OTHER_FILES = "plugin.json"
