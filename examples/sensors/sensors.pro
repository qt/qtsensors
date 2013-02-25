TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        accelbubble \
        cubehouse \
        qmlsensorgestures \
        maze \
        qmlqtsensors \
        sensor_explorer \
        shakeit
}

qtHaveModule(widgets): SUBDIRS += \
    sensorgestures

OTHER_FILES = stub.h
