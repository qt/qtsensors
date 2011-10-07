TEMPLATE = lib
TARGET = gruesensor

QT = core sensors

HEADERS += gruesensor.h\
           gruesensor_p.h\

SOURCES += gruesensor.cpp\

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

target.path=$$[QT_INSTALL_LIBS]
INSTALLS += target

