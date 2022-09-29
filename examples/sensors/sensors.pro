TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        maze \
        qmlqtsensors \
        sensor_explorer

     qtHaveModule(svg): SUBDIRS += \
        accelbubble
}

EXAMPLE_FILES += \
    stub.h
