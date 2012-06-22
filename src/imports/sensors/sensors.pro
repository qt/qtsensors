TARGET  = declarative_sensors
TARGETPATH = QtMobility/sensors
IMPORT_NAME = $$TARGETPATH
IMPORT_NAME~=s,/,.,g
IMPORT_VERSION = 1.3 # Doesn't matter, as long as it's a valid version?!

include(qsensorsimport.pri)

QT += qml sensors

SOURCES += sensors.cpp

DESTDIR = $$QT.sensors.imports/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmldir.files += $$PWD/qmldir $$PWD/plugin.qmltypes
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir

OTHER_FILES += \
    plugin.json qmldir plugin.qmltypes
