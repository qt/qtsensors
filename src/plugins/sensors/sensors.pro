TEMPLATE = subdirs

# Don't build dummy plugins, the Blackberry backend has real implementations
# of these. This reduces compile time and plugin loading time.
blackberry {
    isEmpty(SENSORS_PLUGINS): SENSORS_PLUGINS = blackberry generic
}

android {
    isEmpty(SENSORS_PLUGINS): SENSORS_PLUGINS = android generic
}

sensorfw {
    isEmpty(SENSORS_PLUGINS): SENSORS_PLUGINS = sensorfw generic
}

ios {
    isEmpty(SENSORS_PLUGINS): SENSORS_PLUGINS = ios generic
}

isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, dummy):SUBDIRS += dummy
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, generic):SUBDIRS += generic
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, simulator):simulator:SUBDIRS += simulator
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, blackberry):blackberry:SUBDIRS += blackberry
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, linux):linux:SUBDIRS += linux
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, android):android:SUBDIRS += android
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, sensorfw):sensorfw:SUBDIRS += sensorfw
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, ios):ios:SUBDIRS += ios
