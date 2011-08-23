TEMPLATE = subdirs

SUBDIRS += sensors
sensors.subdir = sensors
sensors.target = sub-sensors

SUBDIRS += qtmsensors
qtmsensors.subdir = qtmsensors
qtmsensors.target = sub-qtmsensors
qtmsensors.depends = sensors

SUBDIRS += imports
imports.subdir = imports
imports.target = sub-imports
imports.depends = sensors qtmsensors

SUBDIRS += plugins
plugins.subdir = plugins
plugins.target = sub-plugins
plugins.depends = sensors

