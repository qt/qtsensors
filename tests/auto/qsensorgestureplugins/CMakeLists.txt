#####################################################################
## tst_qsensorgesturepluginstest Binary:
#####################################################################

qt_internal_add_test(tst_qsensorgesturepluginstest
    SOURCES
        ../qsensor/test_backends.cpp ../qsensor/test_backends.h
        tst_qsensorgesturepluginstest.cpp
    INCLUDE_DIRECTORIES
        ../qsensor
    PUBLIC_LIBRARIES
        Qt::Sensors
        Qt::Test
)
