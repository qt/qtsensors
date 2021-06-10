TEMPLATE = app
TARGET = detect_grue
CONFIG += console
CONFIG -= app_bundle
QT = core sensors

DESTDIR = $$OUT_PWD/..

SOURCES = main.cpp

grue_plugin_base_dir = ..
include(../use_grue_static_plugin.pri)

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/grue
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
