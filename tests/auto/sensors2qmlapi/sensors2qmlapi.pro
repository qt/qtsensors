TEMPLATE = app
TARGET = tst_sensors2qmlapi

CONFIG += testcase
QT = core testlib sensors-private declarative
INCLUDEPATH += ./
DEPENDPATH += ./

SOURCES += tst_sensors2qmlapi.cpp \
           ./../../../src/imports/sensors2/qsensor2ambientlight.cpp \
           ./../../../src/imports/sensors2/qsensor2proximity.cpp \
           ./../../../src/imports/sensors2/qsensor2tilt.cpp

HEADERS += qdeclaccelerometer.h \
           qdeclambientlightsensor.h \
           qdeclproximitysensor.h \
           qbackends.h \
           ./../../../src/imports/sensors2/qsensor2ambientlight.h \
           ./../../../src/imports/sensors2/qsensor2proximity.h \
           ./../../../src/imports/sensors2/qsensor2tilt.h
