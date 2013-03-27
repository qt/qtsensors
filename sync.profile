%modules = ( # path to module name map
    "QtSensors" => "$basedir/src/sensors",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%dependencies = (
    "qtbase" => "refs/heads/dev",
    "qtxmlpatterns" => "refs/heads/dev",
    "qtdeclarative" => "refs/heads/dev",
    "qtjsbackend" => "refs/heads/dev",
);
