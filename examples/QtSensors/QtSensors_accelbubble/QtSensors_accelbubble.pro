TEMPLATE = aux

app.files = \
    info.json \
    QtSensors_accelbubble.qml \
    icon.png \
    content \
    images

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.accelbubble
    INSTALLS = app
}

