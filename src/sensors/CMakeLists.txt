#####################################################################
## Sensors Module:
#####################################################################

qt_internal_add_module(Sensors
    PLUGIN_TYPES sensors sensorgestures
    SOURCES
    gestures/qsensorgesture.cpp gestures/qsensorgesture.h gestures/qsensorgesture_p.h
    gestures/qsensorgesturemanager.cpp gestures/qsensorgesturemanager.h
    gestures/qsensorgesturemanagerprivate.cpp gestures/qsensorgesturemanagerprivate_p.h
    gestures/qsensorgestureplugininterface.cpp gestures/qsensorgestureplugininterface.h
    gestures/qsensorgesturerecognizer.cpp gestures/qsensorgesturerecognizer.h
    qsensorbackend.cpp qsensorbackend.h
    qsensormanager.cpp qsensormanager.h
    qsensorplugin.cpp qsensorplugin.h
    qsensorsglobal.h
    sensorlog_p.h
    qsensor.h
    qaccelerometer.h
    qaltimeter.h
    qambientlightsensor.h
    qambienttemperaturesensor.h
    qcompass.h
    qdistancesensor.h
    qholstersensor.h
    qlightsensor.h
    qmagnetometer.h
    qorientationsensor.h
    qproximitysensor.h
    qirproximitysensor.h
    qrotationsensor.h
    qtapsensor.h
    qtiltsensor.h
    qgyroscope.h
    qpressuresensor.h
    qhumiditysensor.h
    qlidsensor.h
    qsensor_p.h
    qaccelerometer_p.h
    qaltimeter_p.h
    qambientlightsensor_p.h
    qambienttemperaturesensor_p.h
    qcompass_p.h
    qdistancesensor_p.h
    qholstersensor_p.h
    qlightsensor_p.h
    qmagnetometer_p.h
    qorientationsensor_p.h
    qproximitysensor_p.h
    qirproximitysensor_p.h
    qrotationsensor_p.h
    qtapsensor_p.h
    qtiltsensor_p.h
    qgyroscope_p.h
    qpressuresensor_p.h
    qhumiditysensor_p.h
    qlidsensor_p.h
    qsensor.cpp
    qaccelerometer.cpp
    qaltimeter.cpp
    qambientlightsensor.cpp
    qambienttemperaturesensor.cpp
    qcompass.cpp
    qdistancesensor.cpp
    qholstersensor.cpp
    qlightsensor.cpp
    qmagnetometer.cpp
    qorientationsensor.cpp
    qproximitysensor.cpp
    qirproximitysensor.cpp
    qrotationsensor.cpp
    qtapsensor.cpp
    qtiltsensor.cpp
    qgyroscope.cpp
    qpressuresensor.cpp
    qhumiditysensor.cpp
    qlidsensor.cpp
    DEFINES
        $<$<CONFIG:Debug>:ENABLE_RUNTIME_SENSORLOG>
    LIBRARIES
        Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Core
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
)

if(ANDROID)
    set_property(TARGET Sensors APPEND PROPERTY QT_ANDROID_LIB_DEPENDENCIES
        plugins/sensors/libplugins_sensors_qtsensors_android.so
    )
endif()

#### Keys ignored in scope 1:.:.:sensors.pro:<TRUE>:
# SENSORS = "qsensor" "qaccelerometer" "qaltimeter" "qambientlightsensor" "qambienttemperaturesensor" "qcompass" "qdistancesensor" "qholstersensor" "qlightsensor" "qmagnetometer" "qorientationsensor" "qproximitysensor" "qirproximitysensor" "qrotationsensor" "qtapsensor" "qtiltsensor" "qgyroscope" "qpressuresensor" "qhumiditysensor" "qlidsensor"

## Scopes:
#####################################################################

qt_internal_extend_target(Sensors CONDITION NOT SENSORS_CONFIG_PATH
    DEFINES
        QTSENSORS_CONFIG_PATH="${SENSORS_CONFIG_PATH}"
)

qt_internal_add_docs(Sensors
    doc/qtsensors.qdocconf
)

