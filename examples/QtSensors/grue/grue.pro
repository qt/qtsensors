TEMPLATE = subdirs

SUBDIRS += lib plugin console_app
SUBDIRS += import qml_app

plugin.depends = lib
import.depends = lib

