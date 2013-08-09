TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
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

qtHaveModule(systeminfo): SUBDIRS += \
    maze

OTHER_FILES = stub.h
