TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        maze \
        qmlsensorgestures \
        qmlqtsensors \
        sensor_explorer \
        shakeit

     qtHaveModule(svg): SUBDIRS += \
        accelbubble
}

qtHaveModule(widgets): SUBDIRS += \
    sensorgestures

qtHaveModule(3d): SUBDIRS += \
    cubehouse

OTHER_FILES = stub.h
