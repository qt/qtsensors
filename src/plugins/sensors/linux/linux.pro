TARGET = qtsensors_linuxsys
QT = core sensors

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

OTHER_FILES = plugin.json

LIBS += -lrt
HEADERS += linuxsysaccelerometer.h
SOURCES += linuxsysaccelerometer.cpp \
main.cpp

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
