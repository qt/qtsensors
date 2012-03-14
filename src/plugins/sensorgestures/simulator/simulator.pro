load(qt_module)

TARGET = qtsensorgestures_simulator
load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensorgestures

QT=core gui network sensors simulator

target.path += $$[QT_INSTALL_PLUGINS]/sensorgestures
INSTALLS += target

HEADERS += \
    simulatorgesturescommon.h\
    qsimulatorrecognizer.h\
    qsimulatorsensorgestureplugin.h


SOURCES += \
    simulatorgesturescommon.cpp\
    qsimulatorrecognizer.cpp\
    qsimulatorsensorgestureplugin.cpp

OTHER_FILES += \
    plugin.json


