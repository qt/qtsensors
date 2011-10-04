TEMPLATE = lib
TARGET = gruesensor

QT = core sensors

HEADERS += gruesensor.h\
           gruesensor_p.h\

SOURCES += gruesensor.cpp\

DESTDIR=$$QT.sensors.libs

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

