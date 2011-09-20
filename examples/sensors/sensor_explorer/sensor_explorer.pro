TEMPLATE=app
TARGET=sensor_explorer
QT=core gui widgets sensors

FORMS=\
    explorer.ui

HEADERS=\
    explorer.h

SOURCES=\
    explorer.cpp\
    main.cpp

maemo5:DEFINES+=MAEMO5

