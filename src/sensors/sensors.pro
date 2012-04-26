load(qt_module)

TARGET = QtSensors
QPRO_PWD = $$PWD

CONFIG += module
CONFIG += strict_flags
CONFIG(debug,debug|release):DEFINES += ENABLE_RUNTIME_SENSORLOG

MODULE_PRI = ../../modules/qt_sensors.pri

QT = core core-private

DEFINES += QT_BUILD_SENSORS_LIB QT_MAKEDLL
!isEmpty(SENSORS_CONFIG_PATH):DEFINES += "QTSENSORS_CONFIG_PATH=\\\"$$SENSORS_CONFIG_PATH\\\""

simulator {
    DEFINES += SIMULATOR_BUILD
    QT += simulator
}

load(qt_module_config)
HEADERS += qtsensorsversion.h


symbian {
    TARGET.CAPABILITY = ALL -TCB
    TARGET.UID3 = 0x2002BFC0

    ### Sensors
    # Main library
    SENSORS_DEPLOYMENT.sources = QtSensors.dll
    SENSORS_DEPLOYMENT.path = /sys/bin
    DEPLOYMENT += SENSORS_DEPLOYMENT
    LIBS += -lefsrv

    # We break on Symbian^3 unless we have this include (normally obtained by linking to QtGui)
    load(platform_paths)
    INCLUDEPATH *= $$MW_LAYER_SYSTEMINCLUDE

}


#INCLUDEPATH += .
#DEPENDPATH += .

PUBLIC_HEADERS += \
           qsensorbackend.h\
           qsensormanager.h\
           qsensorplugin.h\
           qsensorsglobal.h

PRIVATE_HEADERS += \
           sensorlog_p.h\

SOURCES += qsensorbackend.cpp\
           qsensormanager.cpp\
           qsensorplugin.cpp\

SOURCES += \
    gestures/qsensorgesture.cpp \
    gestures/qsensorgesturerecognizer.cpp \
    gestures/qsensorgesturemanager.cpp \
    gestures/qsensorgesturemanagerprivate.cpp \
    gestures/qsensorgestureplugininterface.cpp

GESTURE_HEADERS += \
    gestures/qsensorgesture.h\
    gestures/qsensorgesture_p.h\
    gestures/qsensorgesturerecognizer.h \
    gestures/qsensorgesturemanager.h \
    gestures/qsensorgesturemanagerprivate_p.h \
    gestures/qsensorgestureplugininterface.h

simulator {
    SOURCES += gestures/simulatorgesturescommon.cpp
    GESTURE_HEADERS += gestures/simulatorgesturescommon_p.h
}

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
    qirproximitysensor\
    qrotationsensor\
    qtapsensor\
    qgyroscope\

for(s,SENSORS) {
    # Client API
    PUBLIC_HEADERS += $${s}.h
    SOURCES        += $${s}.cpp
    # Private header
    PRIVATE_HEADERS += $${s}_p.h
}

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS $$GESTURE_HEADERS
