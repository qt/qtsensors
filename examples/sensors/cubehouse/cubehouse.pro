TEMPLATE = aux

app.files = \
    $$files(*.qml) \
    icon.png \
    images \
    info.json \
    mesh

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.cubehouse
    INSTALLS = app
}

