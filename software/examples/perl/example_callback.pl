#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '61TqTK'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
our $dc = BrickDC->new(&UID, $ipcon); # Create device object

# Use velocity reached callback to swing back and forth between
# full speed forward and full speed backward
sub cb_reached
{
    my ($velocity) = @_;

    if($velocity == 32767)
    {
        print("\nVelocity: Full Speed forward, turning backward\n");
        $dc->set_velocity(-32767);
    }   
    elsif($velocity == -32767)
    {
        print("\nVelocity: Full Speed backward, turning forward\n");
        $dc->set_velocity(32767);
    }    
    else
    {
        print("\nError\n") # Can only happen if another program sets velocity
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register "velocity reached callback" to cb_reached
# cb_reached will be called every time a velocity set with
# set_velocity is reached
$dc->register_callback($dc->CALLBACK_VELOCITY_REACHED, 'cb_reached');

$dc->enable();
# The acceleration has to be smaller or equal to the maximum acceleration
# of the dc motor, otherwise cb_reached will be called too early
$dc->set_acceleration(5000); # Slow acceleration
$dc->set_velocity(32767); # Full speed forward

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
