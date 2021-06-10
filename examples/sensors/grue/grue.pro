TEMPLATE = subdirs

SUBDIRS += plugin

# Gui-less apps don't make sense for these platforms
!uikit:!android:!wasm: SUBDIRS += console_app

# There console app is not a macos bundle, so the shared library plugin wouldn't be found
macos:qtConfig(shared): SUBDIRS -= console_app

qtHaveModule(quick): SUBDIRS += qml.pro


