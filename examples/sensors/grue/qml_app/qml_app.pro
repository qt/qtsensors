TEMPLATE = aux

app.files = \
    icon.png \
    info.json \
    main.qml \
    grue.png

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.grue
    INSTALLS = app
}

