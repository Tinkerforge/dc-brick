function matlab_example_configuration
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = '5VF5vG'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    global dc;
    dc = BrickDC(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    dc.setPWMFrequency(10000); % Use PWM frequency of 10kHz
    dc.setDriveMode(1); % Use 1 = Drive/Coast instead of 0 = Drive/Brake

    dc.enable();
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward

    input('\nPress any key to exit...\n', 's');
    ipcon.disconnect();
end
