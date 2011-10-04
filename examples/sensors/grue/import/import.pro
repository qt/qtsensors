TARGET = declarative_grue
TARGETPATH = Grue

include(qsensorsimport.pri)

QT = declarative sensors

DESTDIR = $$QT.sensors.imports/$$TARGETPATH

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

SOURCES = main.cpp

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

