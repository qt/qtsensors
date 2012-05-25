TEMPLATE = subdirs

SUBDIRS += lib plugin console_app
SUBDIRS += import qml.pro

plugin.depends = lib
import.depends = lib

