load(qt_build_config)

TARGET = qtsensors_dummy
QT += sensors core

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

HEADERS += dummycommon.h\
           dummyaccelerometer.h\
           dummylightsensor.h

SOURCES += dummycommon.cpp\
           dummyaccelerometer.cpp\
           dummylightsensor.cpp\
           main.cpp

OTHER_FILES = plugin.json

unix:!mac:!qnx:LIBS+=-lrt

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
