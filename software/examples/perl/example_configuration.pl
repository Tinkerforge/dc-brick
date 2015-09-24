#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XXYYZZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $dc = Tinkerforge::BrickDC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

$dc->set_drive_mode($dc->DRIVE_MODE_DRIVE_COAST);
$dc->set_pwm_frequency(10000); # Use PWM frequency of 10kHz
$dc->set_acceleration(5000); # Slow acceleration
$dc->set_velocity(32767); # Full speed forward
$dc->enable(); # Enable motor power

print "Press key to exit\n";
<STDIN>;
$dc->disable(); # Disable motor power
$ipcon->disconnect();
