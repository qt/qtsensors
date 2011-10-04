TEMPLATE = subdirs

SUBDIRS += \
    accel\
    cubehouse\
    grue

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensor_explorer
