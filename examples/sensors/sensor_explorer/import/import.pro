TARGET  = declarative_explorer
TARGETPATH = Explorer

include(qsensorsimport.pri)

QT += declarative sensors

SOURCES = main.cpp explorer.cpp sensoritem.cpp propertyinfo.cpp
HEADERS = explorer.h sensoritem.h propertyinfo.h

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

!isEmpty(EXAMPLES_PREFIX):DESTPATH=$$EXAMPLES_PREFIX/sensor_explorer/imports/Explorer
else:DESTPATH=$$[QT_INSTALL_IMPORTS]/Explorer

target.path=$$DESTPATH
INSTALLS += target

qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += qmldir
