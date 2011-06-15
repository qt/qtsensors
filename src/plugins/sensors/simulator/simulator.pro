load(qt_module)

include(simulator.pri)

TARGET = qtsensors_simulator
load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

#TODO what is the simulator called in Qt 5?
#qtAddLibrary(QtMobilitySimulator)

symbian:TARGET.EPOCALLOWDLLDATA = 1

QT=core gui network sensors

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target

