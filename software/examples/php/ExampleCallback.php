<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickDC;

$host = 'localhost';
$port = 4223;
$uid = 'a4GePuz3m29'; // Change to your UID

// Use velocity reached callback to swing back and forth between
// full speed forward and full speed backward
function cb_reached($velocity)
{
    global $dc;

    if ($velocity == 32767) {
        echo "Velocity: Full Speed forward, turning backward\n";
        $dc->setVelocity(-32767);
    } elseif ($velocity == -32767) {
        echo "Velocity: Full Speed backward, turning forward\n";
        $dc->setVelocity(32767);
    } else {
        echo "Error\n"; // Can only happen if another program sets velocity
    }
}

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$dc = new BrickDC($uid); // Create device object

$ipcon->addDevice($dc); // Add device to IP connection
// Don't use device before it is added to a connection

// Register "velocity reached callback" to cb_reached
// cb_reached will be called every time a velocity set with
// set_velocity is reached
$dc->registerCallback(BrickDC::CALLBACK_VELOCITY_REACHED, 'cb_reached');

$dc->enable();
// The acceleration has to be smaller or equal to the maximum acceleration
// of the dc motor, otherwise cb_reached will be called too early
$dc->setAcceleration(5000); // Slow acceleration
$dc->setVelocity(32767); // Full speed forward

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
