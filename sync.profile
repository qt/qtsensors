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
    "qtbase" => "67fc1b893d6bbcd135497341cfaa4ea74ffeb29b",
    "qtdeclarative" => "refs/heads/master",
    "qtjsbackend" => "refs/heads/master",
);

# Compile tests
%configtests = (
    # Blackberry tests
    "bbsensor_header" => {},
);

