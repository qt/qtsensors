load(qt_module)

symbian:load(qt_plugin)
TEMPLATE = lib
CONFIG += qt plugin

win32|mac:!wince*:!win32-msvc:!macx-xcode:CONFIG += debug_and_release

isEmpty(TARGETPATH) {
    error("qimportbase.pri: You must provide a TARGETPATH!")
}
isEmpty(TARGET) {
    error("qimportbase.pri: You must provide a TARGET!")
}

TARGET = $$qtLibraryTarget($$TARGET)
contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

load(qt_targets)

wince*:LIBS += $$QMAKE_LIBS_GUI

symbian: {
    TARGET.EPOCALLOWDLLDATA=1
    TARGET.CAPABILITY = All -Tcb
    load(armcc_warnings)
}
