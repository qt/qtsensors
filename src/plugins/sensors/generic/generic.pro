TARGET = qtsensors_generic
QT = core sensors

PLUGIN_TYPE = sensors
load(qt_plugin)

HEADERS += generictiltsensor.h

SOURCES += main.cpp\
           generictiltsensor.cpp

!blackberry {
    HEADERS += genericorientationsensor.h\
               genericrotationsensor.h\
               genericalssensor.h

    SOURCES += genericorientationsensor.cpp\
               genericrotationsensor.cpp\
               genericalssensor.cpp
}

OTHER_FILES = plugin.json
