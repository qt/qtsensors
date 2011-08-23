TEMPLATE = app
TARGET = tst_qtmsensor

CONFIG += testcase
QT = core testlib qtmsensors-private

SOURCES += \
    tst_qtmsensor.cpp

HEADERS += \
    ../qsensor/test_sensor.h\
    ../qsensor/test_sensor_p.h\
    ../qsensor/test_sensorimpl.h\
    ../qsensor/test_sensor2.h\
    ../qsensor/test_sensor2_p.h\
    ../qsensor/test_sensor2impl.h\
    ../qsensor/test_backends.h

SOURCES += \
    ../qsensor/test_sensor.cpp\
    ../qsensor/test_sensorimpl.cpp\
    ../qsensor/test_sensor2.cpp\
    ../qsensor/test_sensor2impl.cpp\
    ../qsensor/test_sensorplugin.cpp\
    ../qsensor/test_backends.cpp

HEADERS += \
    test_sensor_qtm.h \
    test_sensor_qtm_p.h \
    test_sensor_wrapper.h \
    test_backends_qtm.h

SOURCES += \
    test_sensor_qtm.cpp \
    test_sensor_wrapper.cpp \
    test_backends_qtm.cpp
