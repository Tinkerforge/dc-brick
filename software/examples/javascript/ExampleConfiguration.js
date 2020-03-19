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
        dc.setPWMFrequency(10000); // Use PWM frequency of 10 kHz
        dc.setAcceleration(4096); // Slow acceleration (12.5 %/s)
        dc.setVelocity(32767); // Full speed forward (100 %)
        dc.enable(); // Enable motor power
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        // Stop motor before disabling motor power
        dc.setAcceleration(16384); // Fast decceleration (50 %/s) for stopping
        dc.setVelocity(0); // Request motor stop

        setTimeout(function () {
            dc.disable(); // Disable motor power

            ipcon.disconnect();
            process.exit(0);
        }, 2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    }
);
