<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickDC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your DC Brick

// Use velocity reached callback to swing back and forth
// between full speed forward and full speed backward
function cb_velocityReached($velocity, $user_data)
{
    $dc = $user_data;

    if ($velocity == 32767) {
        echo "Velocity: Full speed forward, now turning backward\n";
        $dc->setVelocity(-32767);
    } elseif ($velocity == -32767) {
        echo "Velocity: Full speed backward, now turning forward\n";
        $dc->setVelocity(32767);
    } else {
        echo "Error\n"; // Can only happen if another program sets velocity
    }
}

$ipcon = new IPConnection(); // Create IP connection
$dc = new BrickDC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// The acceleration has to be smaller or equal to the maximum
// acceleration of the DC motor, otherwise the velocity reached
// callback will be called too early
$dc->setAcceleration(5000); // Slow acceleration
$dc->setVelocity(32767); // Full speed forward

// Register velocity reached callback to function cb_velocityReached
$dc->registerCallback(BrickDC::CALLBACK_VELOCITY_REACHED, 'cb_velocityReached', $dc);

// Enable motor power
$dc->enable();

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
