TEMPLATE = app
TARGET = sensorsshowcase
QT += quick sensors svg
SOURCES = main.cpp

RESOURCES += \
    sensorsshowcase.qrc

OTHER_FILES = \
    $$files(*.qml) \
    images \
    android/AndroidManifest.xml

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensorsshowcase
INSTALLS += target

ios {
QMAKE_INFO_PLIST = Info.plist

# manual plugin loading needed with older Qt
# QTPLUGIN += qsvg qtsensors_ios qtsensors_generic
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

EXAMPLE_FILES += \
    Info.plist
