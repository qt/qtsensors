load(qt_module)

TARGET = qtsensors_simulator
load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

symbian:TARGET.EPOCALLOWDLLDATA = 1

QT=core gui network sensors simulator

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target

HEADERS += \
    simulatorcommon.h\
    simulatoraccelerometer.h\
    simulatorambientlightsensor.h\
    simulatorlightsensor.h\
    simulatorcompass.h\
    simulatorproximitysensor.h\
    simulatorirproximitysensor.h\
    simulatormagnetometer.h\
    qsensordata_simulator_p.h

SOURCES += \
    simulatorcommon.cpp\
    simulatoraccelerometer.cpp\
    simulatorambientlightsensor.cpp\
    simulatorlightsensor.cpp\
    simulatorcompass.cpp\
    simulatorproximitysensor.cpp\
    simulatorirproximitysensor.cpp\
    simulatormagnetometer.cpp\
    qsensordata_simulator.cpp\
    main.cpp

OTHER_FILES = plugin.json
