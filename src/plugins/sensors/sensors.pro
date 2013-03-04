TEMPLATE = subdirs

# Don't build dummy plugins, the Blackberry backend has real implementations
# of these. This reduces compile time and plugin loading time.
blackberry {
    isEmpty(SENSORS_PLUGINS): SENSORS_PLUGINS = blackberry generic
} else: android {
    SENSORS_PLUGINS = android generic
}

isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, dummy):SUBDIRS += dummy
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, generic):SUBDIRS += generic
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, simulator):simulator:SUBDIRS += simulator
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, blackberry):blackberry:SUBDIRS += blackberry
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, linux):linux:SUBDIRS += linux
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, android):android:SUBDIRS += android
