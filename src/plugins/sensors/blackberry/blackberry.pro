load(qt_module)

TARGET = qtsensors_blackberry
QT = sensors core
DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

HEADERS += bbsensorbackend.h \
    bbaccelerometer.h \
    bbaltimeter.h \
    bbgyroscope.h \
    bblightsensor.h \
    bbmagnetometer.h \
    bborientationsensor.h \
    bbproximitysensor.h \
    bbrotationsensor.h \
    bbtemperaturesensor.h \
    bbutil.h

SOURCES += bbsensorbackend.cpp \
    bbaccelerometer.cpp \
    bbaltimeter.cpp \
    bbgyroscope.cpp \
    bblightsensor.cpp \
    bbmagnetometer.cpp \
    bborientationsensor.cpp \
    bbproximitysensor.cpp \
    bbrotationsensor.cpp \
    bbtemperaturesensor.cpp \
    main.cpp

OTHER_FILES = plugin.json

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
