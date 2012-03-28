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

symbian {
    # In Symbian, a library should enjoy _largest_ possible capability set.
    TARGET.CAPABILITY = ALL -TCB
    # Allow writable DLL data
    TARGET.EPOCALLOWDLLDATA = 1
    # Target UID, makes every Symbian app unique
    TARGET.UID3 = 0x20021324
    # Specifies what files shall be deployed: the plugin itself and the qmldir file.
    importFiles.sources = $$DESTDIR/declarative_sensors$${QT_LIBINFIX}.dll qmldir
    importFiles.path = $$QT_IMPORTS_BASE_DIR/$$TARGETPATH
    DEPLOYMENT = importFiles
}

OTHER_FILES += \
    plugin.json qmldir plugin.qmltypes
