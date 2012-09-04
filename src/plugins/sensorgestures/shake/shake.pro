TARGET = qtsensorgestures_shakeplugin
QT = core sensors

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensorgestures

# Input
HEADERS += qshakesensorgestureplugin.h \
           qshakerecognizer.h
SOURCES += qshakesensorgestureplugin.cpp \
           qshakerecognizer.cpp

target.path += $$[QT_INSTALL_PLUGINS]/sensorgestures
INSTALLS += target

OTHER_FILES += \
    plugin.json

