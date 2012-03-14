TEMPLATE = lib
CONFIG += plugin

TARGET = qtsensorgestures_shakeplugin

QT += sensors
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

