TEMPLATE=app
TARGET=sensorsdocsnippet
QT += sensors
SOURCES+=main.cpp\
    creating.cpp\
    start.cpp\
    plugin.cpp
HEADERS+=mybackend.h
*g++*:LIBS+=-rdynamic
QT+=widgets
