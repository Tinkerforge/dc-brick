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
        // The acceleration has to be smaller or equal to the maximum
        // acceleration of the DC motor, otherwise the velocity reached
        // callback will be called too early
        dc.setAcceleration(5000); // Slow acceleration
        dc.setVelocity(32767); // Full speed forward

        // Enable motor power
        dc.enable();
    }
);

// Register velocity reached callback
dc.on(Tinkerforge.BrickDC.CALLBACK_VELOCITY_REACHED,
    // Use velocity reached callback to swing back and forth
    // between full speed forward and full speed backward
    function (velocity) {
        if(velocity == 32767) {
            console.log('Velocity: Full speed forward, now turning backward');
            dc.setVelocity(-32767);
        }
        else if(velocity === -32767) {
            console.log('Velocity: Full speed backward, now turning forward');
            dc.setVelocity(32767);
        }
        else {
            console.log('Error'); // Can only happen if another program sets velocity
        }
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
