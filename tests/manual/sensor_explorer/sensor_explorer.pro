TEMPLATE=app
TARGET=sensor_explorer

QT = core gui sensors

FORMS=\
    explorer.ui

HEADERS=\
    explorer.h

SOURCES=\
    explorer.cpp\
    main.cpp


DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
