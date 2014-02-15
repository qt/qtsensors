TARGET = qtsensors_winrt
QT = sensors core

PLUGIN_TYPE = sensors
load(qt_plugin)

HEADERS += \
    winrtaccelerometer.h \
    winrtcommon.h \
    winrtcompass.h \
    winrtrotationsensor.h \
    winrtgyroscope.h

SOURCES += \
    main.cpp \
    winrtaccelerometer.cpp \
    winrtcommon.cpp \
    winrtcompass.cpp \
    winrtrotationsensor.cpp \
    winrtgyroscope.cpp

!winphone {
    HEADERS += \
        winrtambientlightsensor.h \
        winrtorientationsensor.h
    SOURCES += \
        winrtambientlightsensor.cpp \
        winrtorientationsensor.cpp
}

OTHER_FILES = plugin.json
