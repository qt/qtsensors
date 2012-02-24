TEMPLATE = lib
CONFIG += plugin

TARGET = qtsensorgestures_counterplugin

QT += sensors
DESTDIR = $$QT.sensors.plugins/sensorgestures

HEADERS += \
    qcountergestureplugin.h \
    qcounterrecognizer.h
SOURCES += \
    qcountergestureplugin.cpp \
    qcounterrecognizer.cpp

target.path += $$[QT_INSTALL_PLUGINS]/sensorgestures
INSTALLS += target

