TARGET = qtsensors_tizen
QT = core sensors

PLUGIN_TYPE = sensors
PLUGIN_CLASS_NAME = TizenSensorPlugin
load(qt_plugin)

OTHER_FILES = plugin.json

HEADERS += tizenaccelerometer.h \
    tizensensorbase.h \
    tizendeviceorientation.h \
    tizencompass.h \
    tizenlight.h \
    tizengyroscope.h \
    tizenproximity.h \
    tizenmagnetometer.h \
    tizengravity.h

SOURCES += main.cpp \
    tizenaccelerometer.cpp \
    tizensensorbase.cpp \
    tizendeviceorientation.cpp \
    tizencompass.cpp \
    tizenlight.cpp \
    tizengyroscope.cpp \
    tizenproximity.cpp \
    tizenmagnetometer.cpp \
    tizengravity.cpp

LIBS += -lcapi-system-sensor
