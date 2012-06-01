TEMPLATE = aux

app.files = \
    $$files(*.qml) \
    info.json \
    icon.png

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.qmlsensorgestures
    INSTALLS = app
}

