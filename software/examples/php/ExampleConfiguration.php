<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickDC;

$host = 'localhost';
$port = 4223;
$uid = 'a4GePuz3m29'; // Change to your UID

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$dc = new BrickDC($uid); // Create device object

$ipcon->addDevice($dc); // Add device to IP connection
// Don't use device before it is added to a connection

$dc->setPwmFrequency(10000); // Use PWM frequency of 10khz
$dc->setDriveMode(1); // use 1 = Drive/Coast instead of 0 = Drive/Brake

$dc->enable();
$dc->setAcceleration(5000); // Slow acceleration
$dc->setVelocity(32767); // Full speed forward

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
