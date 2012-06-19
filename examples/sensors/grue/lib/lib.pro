TEMPLATE = lib
TARGET = gruesensor

# avoid going to release/debug subdirectory
win32:DESTDIR = $$OUT_PWD

DEFINES *= QT_BUILD_GRUE_LIB
QT = core sensors

HEADERS += gruesensor.h\
           gruesensor_p.h\

SOURCES += gruesensor.cpp\

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    target.path = $$EXAMPLES_PREFIX/com.nokia.mt.grue/lib
    remove_so.commands = "rm $(INSTALL_ROOT)$${target.path}/lib$${TARGET}.so"
    remove_so.CONFIG = no_path
    remove_so.depends = install_target
    INSTALLS += remove_so
}

