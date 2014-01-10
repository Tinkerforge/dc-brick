#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '61TqTK'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
my $dc = BrickDC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

$dc->set_pwm_frequency(10000); # Use PWM frequency of 10khz
$dc->set_drive_mode(1); # Use 1 = Drive/Coast instead of 0 = Drive/Brake

$dc->enable();
$dc->set_acceleration(5000); # Slow acceleration
$dc->set_velocity(32767); # Full speed forward

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
