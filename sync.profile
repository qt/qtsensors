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
    "qtdeclarative" => "refs/heads/master",
    "qtjsbackend" => "refs/heads/master",
);

# Compile tests
%configtests = (
    # Blackberry tests
    "bbsensor_header" => {},
);

