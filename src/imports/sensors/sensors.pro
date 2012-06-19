CXX_MODULE = sensors
TARGET  = declarative_sensors
TARGETPATH = QtMobility/sensors
IMPORT_VERSION = 1.3 # Doesn't matter, as long as it's a valid version?!

QT += qml sensors

HEADERS += \
    qmlsensor.h \
    qmlsensorrange.h \
    qmlaccelerometer.h \
    qmlambientlightsensor.h \
    qmlcompass.h \
    qmlgyroscope.h \
    qmlirproximitysensor.h \
    qmllightsensor.h \
    qmlmagnetometer.h \
    qmlorientationsensor.h \
    qmlproximitysensor.h \
    qmltapsensor.h \
    qmlrotationsensor.h \
    qmlsensorglobal.h
SOURCES += sensors.cpp \
    qmlsensor.cpp \
    qmlsensorrange.cpp \
    qmlaccelerometer.cpp \
    qmlambientlightsensor.cpp \
    qmlcompass.cpp \
    qmlgyroscope.cpp \
    qmlirproximitysensor.cpp \
    qmllightsensor.cpp \
    qmlmagnetometer.cpp \
    qmlorientationsensor.cpp \
    qmlproximitysensor.cpp \
    qmltapsensor.cpp \
    qmlrotationsensor.cpp \
    qmlsensorglobal.cpp

load(qml_plugin)

OTHER_FILES += \
    plugin.json qmldir plugins.qmltypes
