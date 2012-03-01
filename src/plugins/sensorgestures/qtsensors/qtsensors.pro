TEMPLATE = lib
CONFIG += plugin

TARGET = qtsensorgestures_plugin

QT += sensors
DESTDIR = $$QT.sensors.plugins/sensorgestures

# Input
HEADERS += qtsensorgestureplugin.h \
    qcoversensorgesturerecognizer.h \
    qdoubletapsensorgesturerecognizer.h \
    qhoversensorgesturerecognizer.h \
    qpickupsensorgesturerecognizer.h \
    qshake2recognizer.h \
    qslamgesturerecognizer.h \
    qturnoversensorgesturerecognizer.h \
    qtwistsensorgesturerecognizer.h \
    qwhipsensorgesturerecognizer.h \
    qtsensorgesturesensorhandler.h

SOURCES += qtsensorgestureplugin.cpp \
    qcoversensorgesturerecognizer.cpp \
    qdoubletapsensorgesturerecognizer.cpp \
    qhoversensorgesturerecognizer.cpp \
    qpickupsensorgesturerecognizer.cpp \
    qshake2recognizer.cpp \
    qslamgesturerecognizer.cpp \
    qturnoversensorgesturerecognizer.cpp \
    qtwistsensorgesturerecognizer.cpp \
    qwhipsensorgesturerecognizer.cpp \
    qtsensorgesturesensorhandler.cpp

target.path += $$[QT_INSTALL_PLUGINS]/sensorgestures
INSTALLS += target

