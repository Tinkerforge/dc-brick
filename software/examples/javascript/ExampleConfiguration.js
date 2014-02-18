var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = '6rGntQ';// Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var dc = new Tinkerforge.BrickDC(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        dc.setPWMFrequency(10000);//Use PWM frequency of 10khz
        dc.setDriveMode(1);//Use 1 = Drive/Coast instead of 0 = Drive/Brake
        dc.enable();
        dc.setAcceleration(5000);//Slow acceleration
        dc.setVelocity(32767);//Full speed forward     
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

