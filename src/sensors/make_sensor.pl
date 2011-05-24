#!/usr/bin/perl
#############################################################################
##
## Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
## All rights reserved.
## Contact: Nokia Corporation (qt-info@nokia.com)
##
## This file is part of the Qt Mobility Components.
##
## $QT_BEGIN_LICENSE:LGPL$
## GNU Lesser General Public License Usage
## This file may be used under the terms of the GNU Lesser General Public
## License version 2.1 as published by the Free Software Foundation and
## appearing in the file LICENSE.LGPL included in the packaging of this
## file. Please review the following information to ensure the GNU Lesser
## General Public License version 2.1 requirements will be met:
## http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Nokia gives you certain additional
## rights. These rights are described in the Nokia Qt LGPL Exception
## version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU General
## Public License version 3.0 as published by the Free Software Foundation
## and appearing in the file LICENSE.GPL included in the packaging of this
## file. Please review the following information to ensure the GNU General
## Public License version 3.0 requirements will be met:
## http://www.gnu.org/copyleft/gpl.html.
##
## Other Usage
## Alternatively, this file may be used in accordance with the terms and
## conditions contained in a signed written agreement between you and Nokia.
##
##
##
##
##
## $QT_END_LICENSE$
##
#############################################################################

use strict;
use warnings;

use Carp;
local $Carp::CarpLevel;# = 1;

my $sensor = get_arg();
my $sensorbase = $sensor;
$sensorbase =~ s/Sensor$//;
my $reading = $sensorbase.'Reading';
my $reading_private = $reading.'Private';
my $filter = $sensorbase.'Filter';

my $filebase;
eval {
    $filebase = get_arg();
};
if ($@) {
    $filebase = lc($sensor);
}

my $pheader = $filebase."_p.h";
my $header = $filebase.".h";
my $source = $filebase.".cpp";

my $pguard = uc($pheader);
$pguard =~ s/\./_/g;

my $guard = uc($header);
$guard =~ s/\./_/g;

if (! -e $pheader) {
    print "Creating $pheader\n";
    open OUT, ">$pheader" or die $!;
    print OUT '
#ifndef '.$pguard.'
#define '.$pguard.'

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

class '.$reading_private.'
{
public:
    '.$reading_private.'()
        : myprop(0)
    {
    }

    /*
     * Note that this class is copied so you may need to implement
     * a copy constructor if you have complex types or pointers
     * as values.
     */

    qreal myprop;
};

QT_END_NAMESPACE

#endif
';
    close OUT;
}

if (! -e $header) {
    print "Creating $header\n";
    open OUT, ">$header" or die $!;
    print OUT '
#ifndef '.$guard.'
#define '.$guard.'

#include <qsensor.h>

QT_BEGIN_NAMESPACE

class '.$reading_private.';

class Q_SENSORS_EXPORT '.$reading.' : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal myprop READ myprop)
    DECLARE_READING('.$reading.')
public:
    qreal myprop() const;
    void setMyprop(qreal myprop);
};

class Q_SENSORS_EXPORT '.$filter.' : public QSensorFilter
{
public:
    virtual bool filter('.$reading.' *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<'.$reading.'*>(reading)); }
};

class Q_SENSORS_EXPORT '.$sensor.' : public QSensor
{
    Q_OBJECT
public:
    explicit '.$sensor.'(QObject *parent = 0) : QSensor('.$sensor.'::type, parent) {}
    virtual ~'.$sensor.'() {}
    '.$reading.' *reading() const { return static_cast<'.$reading.'*>(QSensor::reading()); }
    static char const * const type;
};

QT_END_NAMESPACE

#endif
';
    close OUT;
}

if (! -e $source) {
    print "Creating $source\n";
    open OUT, ">$source" or die $!;
    print OUT '
#include <'.$header.'>
#include "'.$pheader.'"

QT_BEGIN_NAMESPACE

IMPLEMENT_READING('.$reading.')

/*!
    \class '.$reading.'
    \ingroup sensors_reading
    \inmodule QtSensors

    \brief The '.$reading.' class holds readings from the [X] sensor.

    [Fill this out]

    \section2 '.$reading.' Units

    [Fill this out]
*/

/*!
    \property '.$reading.'::myprop
    \brief [what does it hold?]

    [What are the units?]
    \sa {'.$reading.' Units}
*/

qreal '.$reading.'::myprop() const
{
    return d->myprop;
}

/*!
    Sets [what?] to \a myprop.
*/
void '.$reading.'::setMyprop(qreal myprop)
{
    d->myprop = myprop;
}

// =====================================================================

/*!
    \class '.$filter.'
    \ingroup sensors_filter
    \inmodule QtSensors

    \brief The '.$filter.' class is a convenience wrapper around QSensorFilter.

    The only difference is that the filter() method features a pointer to '.$reading.'
    instead of QSensorReading.
*/

/*!
    \fn '.$filter.'::filter('.$reading.' *reading)

    Called when \a reading changes. Returns false to prevent the reading from propagating.

    \sa QSensorFilter::filter()
*/

char const * const '.$sensor.'::type("'.$sensor.'");

/*!
    \class '.$sensor.'
    \ingroup sensors_type
    \inmodule QtSensors

    \brief The '.$sensor.' class is a convenience wrapper around QSensor.

    The only behavioural difference is that this class sets the type properly.

    This class also features a reading() function that returns a '.$reading.' instead of a QSensorReading.

    For details about how the sensor works, see \l '.$reading.'.

    \sa '.$reading.'
*/

/*!
    \fn '.$sensor.'::'.$sensor.'(QObject *parent)

    Construct the sensor as a child of \a parent.
*/

/*!
    \fn '.$sensor.'::~'.$sensor.'()

    Destroy the sensor. Stops the sensor if it has not already been stopped.
*/

/*!
    \fn '.$sensor.'::reading() const

    Returns the reading class for this sensor.

    \sa QSensor::reading()
*/

#include "moc_'.$source.'"
QT_END_NAMESPACE
';
    close OUT;
}

exit 0;


sub get_arg
{
    if (scalar(@ARGV) == 0) {
        croak "Missing arg(s)";
    }
    return shift(@ARGV);
}

