%modules = ( # path to module name map
    "QtSensors" => "$basedir/src/sensors",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
    "qtsensorsversion.h" => "QtSensorsVersion",
);
%mastercontent = (
    "declarative" => "#include <QtDeclarative/qdeclarative.h>\n",
);
%modulepris = (
    "QtSensors" => "$basedir/modules/qt_sensors.pri",
);
# Modules and programs, and their dependencies.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - "LATEST_REVISION", to always test against the latest revision.
#   - "LATEST_RELEASE", to always test against the latest public release.
#   - "THIS_REPOSITORY", to indicate that the module is in this repository.
%dependencies = (
    "QtSensors" => {
        "QtCore" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtDeclarative" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
    },
);
