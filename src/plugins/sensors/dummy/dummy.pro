load(qt_module)

TARGET = qtsensors_dummy
QT += sensors core

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

include(dummy.pri)

unix:LIBS+=-lrt

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
