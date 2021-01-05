#####################################################################
## tst_legacy_sensors Binary:
#####################################################################

qt_internal_add_test(tst_legacy_sensors
    SOURCES
        ../qsensor/test_backends.cpp ../qsensor/test_backends.h
        tst_legacy_sensors.cpp
    INCLUDE_DIRECTORIES
        ../qsensor
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Sensors
        Qt::Test
)
