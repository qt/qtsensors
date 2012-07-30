TEMPLATE = subdirs

SUBDIRS += lib plugin console_app

!isEmpty(QT.quick.name): SUBDIRS += import qml.pro

plugin.depends = lib
import.depends = lib

