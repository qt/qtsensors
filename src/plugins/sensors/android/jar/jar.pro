load(qt_build_paths)

CONFIG += java
TARGET = QtSensors
DESTDIR = $$MODULE_BASE_OUTDIR/jar

JAVACLASSPATH += $$PWD/src

JAVASOURCES += \
    $$PWD/src/org/qtproject/qt5/android/sensors/QtSensors.java
