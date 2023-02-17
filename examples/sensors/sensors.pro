TEMPLATE = subdirs

SUBDIRS += grue

qtHaveModule(quick) {
    SUBDIRS += \
        sensor_explorer
}
