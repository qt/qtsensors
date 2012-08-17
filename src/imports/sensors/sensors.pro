CXX_MODULE = sensors
TARGET  = declarative_sensors
TARGETPATH = QtSensors
IMPORT_VERSION = 5.0 # Doesn't matter, as long as it's a valid version?!

include(qsensorsimport.pri)

QT += qml sensors sensors-private

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
    qmlsensorglobal.h \
    qmltiltsensor.h \
    qmlsensorgesture.h

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
    qmlsensorglobal.cpp \
    qmltiltsensor.cpp \
    qmlsensorgesture.cpp


DESTDIR = $$QT.sensors.imports/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmldir.files += $$PWD/qmldir $$PWD/plugin.qmltypes
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir

load(qml_plugin)

OTHER_FILES += \
    plugin.json qmldir plugins.qmltypes
