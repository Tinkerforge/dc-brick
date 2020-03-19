<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickDC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your DC Brick

$ipcon = new IPConnection(); // Create IP connection
$dc = new BrickDC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

$dc->setDriveMode(BrickDC::DRIVE_MODE_DRIVE_COAST);
$dc->setPWMFrequency(10000); // Use PWM frequency of 10 kHz
$dc->setAcceleration(4096); // Slow acceleration (12.5 %/s)
$dc->setVelocity(32767); // Full speed forward (100 %)
$dc->enable(); // Enable motor power

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));

// Stop motor before disabling motor power
$dc->setAcceleration(16384); // Fast decceleration (50 %/s) for stopping
$dc->setVelocity(0); // Request motor stop
sleep(2); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$dc->disable(); // Disable motor power

$ipcon->disconnect();

?>
