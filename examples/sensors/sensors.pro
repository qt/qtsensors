TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        maze \
        qmlqtsensors \
        sensor_explorer
}

EXAMPLE_FILES += \
    stub.h
