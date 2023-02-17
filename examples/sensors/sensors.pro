TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        qmlqtsensors \
        sensor_explorer
}

EXAMPLE_FILES += \
    stub.h
