CXX_MODULE = sensors
TARGET  = declarative_qtsensors5

QT += qml sensors

SOURCES += sensors2.cpp \
           qsensor2ambientlight.cpp \
           qsensor2proximity.cpp \
           qsensor2tilt.cpp \
           qsensor2gesture.cpp \
    qsensor2common.cpp

HEADERS += qsensor2ambientlight.h \
           qsensor2proximity.h \
           qsensor2tilt.h \
           qsensor2gesture.h \
    qsensor2common.h

load(qml_plugin)

OTHER_FILES += \
    plugin.json
