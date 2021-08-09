TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        maze \
        qmlqtsensors \
        sensor_explorer
        # qmlsensorgestures \
        # shakeit

     qtHaveModule(svg): SUBDIRS += \
        accelbubble
}

# qtHaveModule(widgets): SUBDIRS += \
#    sensorgestures

EXAMPLE_FILES += \
    stub.h
