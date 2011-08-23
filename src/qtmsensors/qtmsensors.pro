load(qt_module)

TARGET = QtmSensors
QPRO_PWD = $$PWD

CONFIG += module
CONFIG += strict_flags
#CONFIG(debug,debug|release):
DEFINES += ENABLE_RUNTIME_SENSORLOG

MODULE_PRI = ../../modules/qt_sensors.pri

QT = core sensors-private

DEFINES += QTM_BUILD_SENSORS_LIB QT_MAKEDLL

load(qt_module_config)

HEADERS += \
    qtmsensorsversion.h\
    qtmsensorsglobal.h\
    qsensorbackend.h\
    qsensormanager_p.h\
    qsensorbackend_p.h\
    backendwrapper_p.h

SOURCES += \
    qsensorbackend.cpp\
    qsensormanager.cpp\
    backendwrapper.cpp

# 3 files per sensor (including QSensor)
SENSORS=\
    qsensor\
    qaccelerometer\
    qambientlightsensor\
    qcompass\
    qlightsensor\
    qmagnetometer\
    qorientationsensor\
    qproximitysensor\
    qrotationsensor\
    qtapsensor\
    qgyroscope

for(s,SENSORS) {
    # Client API
    HEADERS += $${s}.h
    SOURCES += $${s}.cpp
    # Private header
    HEADERS += $${s}_p.h
}
