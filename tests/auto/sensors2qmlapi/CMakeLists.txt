#####################################################################
## tst_sensors2qmlapi Test:
#####################################################################

qt_internal_add_test(tst_sensors2qmlapi
    SOURCES
        ../../../src/imports/sensors/qmlsensor.cpp ../../../src/imports/sensors/qmlsensor.h
        ../../../src/imports/sensors/qmlsensorgesture.cpp ../../../src/imports/sensors/qmlsensorgesture.h
        ../../../src/imports/sensors/qmlsensorrange.cpp ../../../src/imports/sensors/qmlsensorrange.h
        qtemplategestureplugin.cpp qtemplategestureplugin.h
        qtemplaterecognizer.cpp qtemplaterecognizer.h
        tst_sensors2qmlapi.cpp
    PUBLIC_LIBRARIES
        Qt::Qml
    LIBRARIES
        Qt::SensorsPrivate
)
