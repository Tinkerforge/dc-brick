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
        dc.setPWMFrequency(10000);//Use PWM frequency of 10khz
        dc.setDriveMode(1);//Use 1 = Drive/Coast instead of 0 = Drive/Brake
        dc.enable();
        dc.setAcceleration(5000);//Slow acceleration
        dc.setVelocity(32767);//Full speed forward     
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

