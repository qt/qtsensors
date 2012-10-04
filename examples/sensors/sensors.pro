TEMPLATE = subdirs

SUBDIRS += grue

!isEmpty(QT.quick.name) {
    SUBDIRS += \
        accelbubble \
        cubehouse \
        qmlsensorgestures \
        maze \
        qmlqtsensors \
        sensor_explorer \
        shakeit
}

!isEmpty(QT.widgets.name):SUBDIRS += \
    sensorgestures

OTHER_FILES = stub.h
