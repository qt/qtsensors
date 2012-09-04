TARGET = qtsensors_generic
QT = core sensors

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

HEADERS += genericorientationsensor.h\
           genericrotationsensor.h\
           genericalssensor.h

SOURCES += genericorientationsensor.cpp\
           main.cpp\
           genericrotationsensor.cpp\
           genericalssensor.cpp

OTHER_FILES = plugin.json

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
