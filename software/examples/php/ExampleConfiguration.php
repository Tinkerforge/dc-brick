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
$dc->setPWMFrequency(10000); // Use PWM frequency of 10kHz
$dc->setAcceleration(5000); // Slow acceleration
$dc->setVelocity(32767); // Full speed forward
$dc->enable(); // Enable motor power

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$dc->disable(); // Disable motor power
$ipcon->disconnect();

?>
