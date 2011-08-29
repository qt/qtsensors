%modules = ( # path to module name map
    "QtSensors" => "$basedir/src/sensors",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
    "qtsensorsversion.h" => "QtSensorsVersion",
);
%mastercontent = (
);
%modulepris = (
    "QtSensors" => "$basedir/modules/qt_sensors.pri",
);
%dependencies = (
    "qtbase" => "refs/heads/master",
    "qtscript" => "refs/heads/master",
    "qtsvg" => "refs/heads/master",
    "qtxmlpatterns" => "refs/heads/master",
    "qtdeclarative" => "refs/heads/master",
);
