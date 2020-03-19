#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XXYYZZ'; # Change XXYYZZ to the UID of your DC Brick

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $dc = Tinkerforge::BrickDC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

$dc->set_drive_mode($dc->DRIVE_MODE_DRIVE_COAST);
$dc->set_pwm_frequency(10000); # Use PWM frequency of 10 kHz
$dc->set_acceleration(4096); # Slow acceleration (12.5 %/s)
$dc->set_velocity(32767); # Full speed forward (100 %)
$dc->enable(); # Enable motor power

print "Press key to exit\n";
<STDIN>;

# Stop motor before disabling motor power
$dc->set_acceleration(16384); # Fast decceleration (50 %/s) for stopping
$dc->set_velocity(0); # Request motor stop
sleep(2); # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$dc->disable(); # Disable motor power

$ipcon->disconnect();
