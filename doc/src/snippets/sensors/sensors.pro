TEMPLATE=app
TARGET=sensorsdocsnippet
QT += sensors
SOURCES+=main.cpp\
    creating.cpp\
    start.cpp\
    plugin.cpp
HEADERS+=mybackend.h
!win32:*g++*:LIBS+=-rdynamic
QT+=widgets
