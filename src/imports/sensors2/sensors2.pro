TARGET  = declarative_qtsensors5
TARGETPATH = QtSensors
IMPORT_NAME = $$TARGETPATH
IMPORT_NAME~=s,/,.,g
IMPORT_VERSION = 5.0 # Doesn't matter, as long as it's a valid version?!

include(qsensors2import.pri)

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

DESTDIR = $$QT.sensors.imports/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmldir.files += $$PWD/qmldir $$PWD/plugin.qmltypes
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir

OTHER_FILES += \
    plugin.json qmldir plugin.qmltypes

