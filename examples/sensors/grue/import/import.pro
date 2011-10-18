TARGET = declarative_grue
TARGETPATH = Grue

include(qsensorsimport.pri)

QT = declarative sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

SOURCES = main.cpp

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

!isEmpty(EXAMPLES_PREFIX):DESTPATH=$$EXAMPLES_PREFIX/grue/imports/Grue
else:DESTPATH=$$[QT_INSTALL_IMPORTS]/Grue

target.path=$$DESTPATH
INSTALLS += target

qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += qmldir
