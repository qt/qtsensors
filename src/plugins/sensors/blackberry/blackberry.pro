load(qt_build_config)

TARGET = qtsensors_blackberry
QT = sensors core gui gui-private
DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII

load(qt_plugin)

contains(config_test_bbsensor_header, yes):DEFINES += HAVE_NDK_SENSOR_H

DESTDIR = $$QT.sensors.plugins/sensors

HEADERS += bbsensorbackend.h \
    bbaccelerometer.h \
    bbaltimeter.h \
    bbambientlightsensor.h \
    bbcompass.h \
    bbgyroscope.h \
    bbirproximitysensor.h \
    bblightsensor.h \
    bbmagnetometer.h \
    bborientationsensor.h \
    bbpressuresensor.h \
    bbproximitysensor.h \
    bbrotationsensor.h \
    bbtemperaturesensor.h \
    bbutil.h

SOURCES += bbsensorbackend.cpp \
    bbaccelerometer.cpp \
    bbaltimeter.cpp \
    bbambientlightsensor.cpp \
    bbcompass.cpp \
    bbgyroscope.cpp \
    bbirproximitysensor.cpp \
    bblightsensor.cpp \
    bbmagnetometer.cpp \
    bborientationsensor.cpp \
    bbpressuresensor.cpp \
    bbproximitysensor.cpp \
    bbrotationsensor.cpp \
    bbtemperaturesensor.cpp \
    main.cpp

OTHER_FILES = plugin.json

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
