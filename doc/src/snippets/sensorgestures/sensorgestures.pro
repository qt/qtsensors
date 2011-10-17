TEMPLATE=app
TARGET=sensorgesturessdocsnippet
QT += sensors
SOURCES+=main.cpp\
    creating.cpp\
    plugin.cpp
HEADERS+=myplugin.h
LIBS+=-rdynamic
QT+=widgets
