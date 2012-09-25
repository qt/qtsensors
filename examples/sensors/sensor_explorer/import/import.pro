TEMPLATE = lib
CONFIG += plugin

TARGET = $$qtLibraryTarget(declarative_explorer)
TARGETPATH = Explorer

QT += qml sensors

SOURCES = main.cpp explorer.cpp sensoritem.cpp propertyinfo.cpp
HEADERS = explorer.h sensoritem.h propertyinfo.h

DESTPATH=$$[QT_INSTALL_EXAMPLES]/qtsensors/sensor_explorer/Explorer

target.path=$$DESTPATH
INSTALLS += target

qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += qmldir

OTHER_FILES += \
    plugin.json qmldir
