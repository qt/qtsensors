TEMPLATE = lib
CONFIG += plugin

TARGET = $$qtLibraryTarget(declarative_grue)
TARGETPATH = Grue

QT = core gui qml sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

# Shared gruesensor library will be installed in parent directory.
# Define rpath so that this plugin will know where to look for it.
unix:!mac: QMAKE_LFLAGS += -Wl,-rpath,\\\$\$ORIGIN/..

SOURCES = main.cpp

DESTPATH=$$[QT_INSTALL_EXAMPLES]/qtsensors/grue/Grue

target.path=$$DESTPATH
INSTALLS += target

qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += qmldir

OTHER_FILES += \
    plugin.json qmldir

