
# TODO Qt 6.2 split into separate QML library + plugin

qt_internal_add_qml_module(sensors
    URI "QtSensors"
    VERSION "${CMAKE_PROJECT_VERSION}"
    CLASSNAME QtSensorsDeclarativeModule
    SKIP_TYPE_REGISTRATION
    SOURCES
        qmlaccelerometer.cpp qmlaccelerometer.h
        qmlaltimeter.cpp qmlaltimeter.h
        qmlambientlightsensor.cpp qmlambientlightsensor.h
        qmlambienttemperaturesensor.cpp qmlambienttemperaturesensor.h
        qmlcompass.cpp qmlcompass.h
        qmldistancesensor.cpp qmldistancesensor.h
        qmlgyroscope.cpp qmlgyroscope.h
        qmlholstersensor.cpp qmlholstersensor.h
        qmlhumiditysensor.cpp qmlhumiditysensor.h
        qmlirproximitysensor.cpp qmlirproximitysensor.h
        qmllidsensor.cpp qmllidsensor.h
        qmllightsensor.cpp qmllightsensor.h
        qmlmagnetometer.cpp qmlmagnetometer.h
        qmlorientationsensor.cpp qmlorientationsensor.h
        qmlpressuresensor.cpp qmlpressuresensor.h
        qmlproximitysensor.cpp qmlproximitysensor.h
        qmlrotationsensor.cpp qmlrotationsensor.h
        qmlsensor.cpp qmlsensor.h
        qmlsensorgesture.cpp qmlsensorgesture.h
        qmlsensorglobal.cpp qmlsensorglobal.h
        qmlsensorrange.cpp qmlsensorrange.h
        qmltapsensor.cpp qmltapsensor.h
        qmltiltsensor.cpp qmltiltsensor.h
        sensors.cpp
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Sensors
    LIBRARIES
        Qt::CorePrivate
        Qt::SensorsPrivate
)
