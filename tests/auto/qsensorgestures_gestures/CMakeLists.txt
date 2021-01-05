#####################################################################
## tst_sensorgestures_gestures Test:
#####################################################################

# Collect test data
list(APPEND test_data "mock_data")
list(APPEND test_data "dataset2_mock_data")

qt_internal_add_test(tst_sensorgestures_gestures
    SOURCES
        mockbackends.h
        mockcommon.cpp mockcommon.h
        tst_sensorgestures_gestures.cpp
    DEFINES
        SRCDIR=\\\"${CMAKE_CURRENT_SOURCE_DIR}/\\\"
    PUBLIC_LIBRARIES
        Qt::SensorsPrivate
    TESTDATA ${test_data}
)
