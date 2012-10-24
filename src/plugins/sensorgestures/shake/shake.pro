TARGET = qtsensorgestures_shakeplugin
QT = core sensors

PLUGIN_TYPE = sensorgestures
load(qt_plugin)

# Input
HEADERS += qshakesensorgestureplugin.h \
           qshakerecognizer.h
SOURCES += qshakesensorgestureplugin.cpp \
           qshakerecognizer.cpp

OTHER_FILES += \
    plugin.json

