TEMPLATE = lib
CONFIG += plugin

TARGET = $$qtLibraryTarget(declarative_grue)
TARGETPATH = Grue

QT = core gui qml sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

SOURCES = main.cpp

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX):DESTPATH=$$EXAMPLES_PREFIX/com.nokia.mt.grue/imports/Grue
else:DESTPATH=$$[QT_INSTALL_IMPORTS]/Grue

target.path=$$DESTPATH
INSTALLS += target

qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += qmldir

OTHER_FILES += \
    plugin.json qmldir
