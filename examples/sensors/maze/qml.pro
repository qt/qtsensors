TEMPLATE = aux

app.files = \
    components \
    info.json \
    $$files(*.qml) \
    $$files(*.js) \
    icon.png \
    content

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.maze
    INSTALLS = app
}

