TARGET = qtsensors_generic
QT = core sensors

PLUGIN_TYPE = sensors
load(qt_plugin)

HEADERS += genericorientationsensor.h\
           genericrotationsensor.h\
           genericalssensor.h\
           generictiltsensor.h

SOURCES += genericorientationsensor.cpp\
           main.cpp\
           genericrotationsensor.cpp\
           genericalssensor.cpp\
           generictiltsensor.cpp

OTHER_FILES = plugin.json
