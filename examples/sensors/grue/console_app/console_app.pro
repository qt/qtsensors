TEMPLATE=app
TARGET=detect_grue
CONFIG += console
QT=core sensors
SOURCES=main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/grue
INSTALLS += target
