# Need to manually link to the plugin when using a static Qt build.
qtConfig(static) {
    SOURCES += $$grue_plugin_base_dir/grue_plugin_import_custom.cpp
    LIBS += -L$$grue_plugin_base_dir/sensors
    # For iOS, xcode takes care of the debug suffix
    macx-xcode {
        LIBS += -lplugins_sensors_qtsensors_grue$($${QMAKE_XCODE_LIBRARY_SUFFIX_SETTING})
    # For desktop platforms we need to do it per-platform.
    } else {
        lib_to_link = plugins_sensors_qtsensors_grue
        if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
            macos:lib_to_link = $${lib_to_link}_debug
            win32:lib_to_link = $${lib_to_link}d
        }
        LIBS += -l$$lib_to_link
    }
}
