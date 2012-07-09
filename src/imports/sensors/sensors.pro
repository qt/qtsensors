CXX_MODULE = sensors
TARGET  = declarative_sensors
TARGETPATH = QtMobility/sensors
IMPORT_VERSION = 1.3 # Doesn't matter, as long as it's a valid version?!

QT += qml sensors

SOURCES += sensors.cpp

load(qml_plugin)

OTHER_FILES += \
    plugin.json
