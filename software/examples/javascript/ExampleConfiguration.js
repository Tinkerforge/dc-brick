var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your DC Brick

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var dc = new Tinkerforge.BrickDC(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        dc.setDriveMode(Tinkerforge.BrickDC.DRIVE_MODE_DRIVE_COAST);
        dc.setPWMFrequency(10000); // Use PWM frequency of 10kHz
        dc.setAcceleration(5000); // Slow acceleration
        dc.setVelocity(32767); // Full speed forward
        dc.enable(); // Enable motor power
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        dc.disable(); // Disable motor power
        ipcon.disconnect();
        process.exit(0);
    }
);
