TARGET = qtsensors_android
QT = sensors core

PLUGIN_TYPE = sensors
load(qt_plugin)

# STATICPLUGIN needed because there's a Q_IMPORT_PLUGIN in main.cpp
# Yes, the plugin imports itself statically
DEFINES += QT_STATICPLUGIN

HEADERS = \
    androidjnisensors.h \
    androidaccelerometer.h \
    androidcommonsensor.h \
    androidgyroscope.h \
    androidmagnetometer.h \
    androidrotation.h \
    androidlight.h

SOURCES = \
    main.cpp \
    androidjnisensors.cpp \
    androidaccelerometer.cpp \
    androidgyroscope.cpp \
    androidmagnetometer.cpp \
    androidrotation.cpp \
    androidlight.cpp

OTHER_FILES = plugin.json
