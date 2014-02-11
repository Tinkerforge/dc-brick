var IPConnection = require('Tinkerforge/IPConnection');
var BrickDC = require('Tinkerforge/BrickDC');

var HOST = 'localhost';
var PORT = 4223;
var UID = '6rGntQ';// Change to your UID

var ipcon = new IPConnection();// Create IP connection
var dc = new BrickDC(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        if(error === IPConnection.ERROR_ALREADY_CONNECTED) {
            console.log('Error: Already connected');        
        }
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        dc.enable();
        // The acceleration has to be smaller or equal to the maximum acceleration
        // of the dc motor, otherwise callback "velocity reached callback" will be called too early
        dc.setAcceleration(5000);// Slow acceleration
        dc.setVelocity(32767);// Full speed forward
    }
);

// Register "velocity reached callback"
// This callback will be called every time a velocity set with
// setVelocity is reached
dc.on(BrickDC.CALLBACK_VELOCITY_REACHED,
    // Use velocity reached callback to swing back and forth between
    // full speed forward and full speed backward
    function(velocity) {
        if(velocity == 32767) {
            console.log('Velocity: Full Speed forward, turning backward');
            dc.setVelocity(-32767);
        }
        else if(velocity === -32767) {
            console.log('Velocity: Full Speed backward, turning forward');
            dc.setVelocity(32767);
        }
        else {
            console.log('Error');// Can only happen if another program sets velocity
        }
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data', function(data) {
	    ipcon.disconnect(
            function(error) {
                if(error === IPConnection.ERROR_NOT_CONNECTED) {
                    console.log('Error: Not connected');        
                }
            }
        );
process.exit(0);
});

