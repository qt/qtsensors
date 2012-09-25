TEMPLATE = lib
TARGET = gruesensor

# avoid going to release/debug subdirectory
win32:DESTDIR = $$OUT_PWD

DEFINES *= QT_BUILD_GRUE_LIB
QT = core sensors

HEADERS += gruesensor.h\
           gruesensor_p.h\

SOURCES += gruesensor.cpp\

target.path=$$[QT_INSTALL_EXAMPLES]/qtsensors/grue
INSTALLS += target
