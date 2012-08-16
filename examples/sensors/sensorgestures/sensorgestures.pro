TEMPLATE = app
TARGET = gesture
QT       += core gui sensors widgets

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/sensorgestures
app.files = gesture.png
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/sensorgestures
INSTALLS += target app
