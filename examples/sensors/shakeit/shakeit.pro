TEMPLATE = app
TARGET = shakeit
QT += quick
SOURCES = main.cpp

RESOURCES += \
    shakeit.qrc

app.files = \
    $$files(*.qml) \
    icon.png \
    audio \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/shakeit
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/shakeit
INSTALLS += target app
