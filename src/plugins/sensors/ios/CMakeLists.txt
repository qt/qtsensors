#####################################################################
## IOSSensorPlugin Plugin:
#####################################################################

qt_internal_add_plugin(IOSSensorPlugin
    OUTPUT_NAME qtsensors_ios
    TYPE sensors
    SOURCES
        main.mm
    PUBLIC_LIBRARIES
        ${FWFoundation}
        Qt::Core
        Qt::Sensors
)

#### Keys ignored in scope 1:.:.:ios.pro:<TRUE>:
# OTHER_FILES = "plugin.json"

## Scopes:
#####################################################################

qt_internal_extend_target(IOSSensorPlugin CONDITION IOS AND UIKIT
    SOURCES
        ioscompass.h ioscompass.mm
    DEFINES
        HAVE_COMPASS
    PUBLIC_LIBRARIES
        ${FWCoreLocation}
)

qt_internal_extend_target(IOSSensorPlugin CONDITION UIKIT AND NOT TVOS
    SOURCES
        iosaccelerometer.h iosaccelerometer.mm
        iosgyroscope.h iosgyroscope.mm
        iosmagnetometer.h iosmagnetometer.mm
        iosmotionmanager.h iosmotionmanager.mm
    DEFINES
        HAVE_COREMOTION
    PUBLIC_LIBRARIES
        ${FWCoreMotion}
)

qt_internal_extend_target(IOSSensorPlugin CONDITION UIKIT AND NOT WATCHOS
    SOURCES
        iosproximitysensor.h iosproximitysensor.mm
    DEFINES
        HAVE_UIDEVICE
    PUBLIC_LIBRARIES
        ${FWUIKit}
)
