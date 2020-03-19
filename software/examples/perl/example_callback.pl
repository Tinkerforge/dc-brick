#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XXYYZZ'; # Change XXYYZZ to the UID of your DC Brick

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $dc = Tinkerforge::BrickDC->new(&UID, $ipcon); # Create device object

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
sub cb_velocity_reached
{
    my ($velocity) = @_;

    if ($velocity == 32767)
    {
        print "Velocity: Full speed forward, now turning backward\n";
        $dc->set_velocity(-32767);
    }   
    elsif ($velocity == -32767)
    {
        print "Velocity: Full speed backward, now turning forward\n";
        $dc->set_velocity(32767);
    }    
    else
    {
        print "Error\n"; # Can only happen if another program sets velocity
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# The acceleration has to be smaller or equal to the maximum
# acceleration of the DC motor, otherwise the velocity reached
# callback will be called too early
$dc->set_acceleration(4096); # Slow acceleration (12.5 %/s)
$dc->set_velocity(32767); # Full speed forward (100 %)

# Register velocity reached callback to subroutine cb_velocity_reached
$dc->register_callback($dc->CALLBACK_VELOCITY_REACHED, 'cb_velocity_reached');

# Enable motor power
$dc->enable();

print "Press key to exit\n";
<STDIN>;

# Stop motor before disabling motor power
$dc->set_acceleration(16384); # Fast decceleration (50 %/s) for stopping
$dc->set_velocity(0); # Request motor stop
sleep(2); # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$dc->disable(); # Disable motor power

$ipcon->disconnect();
