qt_internal_add_module(SensorsQuick
    SOURCES
        qmlaccelerometer.cpp qmlaccelerometer_p.h
        qmlaltimeter.cpp qmlaltimeter_p.h
        qmlambientlightsensor.cpp qmlambientlightsensor_p.h
        qmlambienttemperaturesensor.cpp qmlambienttemperaturesensor_p.h
        qmlcompass.cpp qmlcompass_p.h
        qmldistancesensor.cpp qmldistancesensor_p.h
        qmlgyroscope.cpp qmlgyroscope_p.h
        qmlholstersensor.cpp qmlholstersensor_p.h
        qmlhumiditysensor.cpp qmlhumiditysensor_p.h
        qmlirproximitysensor.cpp qmlirproximitysensor_p.h
        qmllidsensor.cpp qmllidsensor_p.h
        qmllightsensor.cpp qmllightsensor_p.h
        qmlmagnetometer.cpp qmlmagnetometer_p.h
        qmlorientationsensor.cpp qmlorientationsensor_p.h
        qmlpressuresensor.cpp qmlpressuresensor_p.h
        qmlproximitysensor.cpp qmlproximitysensor_p.h
        qmlrotationsensor.cpp qmlrotationsensor_p.h
        qmlsensor.cpp qmlsensor_p.h
        qmlsensorgesture.cpp qmlsensorgesture_p.h
        qmlsensorglobal.cpp qmlsensorglobal_p.h
        qmlsensorrange.cpp qmlsensorrange_p.h
        qmltapsensor.cpp qmltapsensor_p.h
        qmltiltsensor.cpp qmltiltsensor_p.h
        qsensorsquickglobal_p.h
    DEFINES
        QT_BUILD_SENSORSQUICK_LIB
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Qml
        Qt::Sensors
    LIBRARIES
        Qt::CorePrivate
)

set_target_properties(SensorsQuick PROPERTIES
    QT_QML_MODULE_INSTALL_QMLTYPES TRUE
    QT_QML_MODULE_VERSION ${PROJECT_VERSION}
    QT_QML_MODULE_URI QtSensors
    QT_QMLTYPES_FILENAME plugins.qmltypes
    QT_QML_MODULE_INSTALL_DIR "${INSTALL_QMLDIR}/QtSensors"
)

qt6_qml_type_registration(SensorsQuick)
