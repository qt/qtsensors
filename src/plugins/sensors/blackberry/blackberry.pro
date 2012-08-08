load(qt_build_config)

TARGET = qtsensors_blackberry
QT = sensors core
DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII

load(qt_plugin)

config_bbsensor_header {
    DEFINES += HAVE_NDK_SENSOR_H
}

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
    bbguihelper.h \
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
    bbguihelper.cpp \
    bbutil.cpp \
    main.cpp

OTHER_FILES = plugin.json

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
