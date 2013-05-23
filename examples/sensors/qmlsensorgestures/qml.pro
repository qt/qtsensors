TEMPLATE = app
TARGET = qmlsensorgestures
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/qmlsensorgestures
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/qmlsensorgestures
INSTALLS += target app

RESOURCES += \
    qml.qrc
