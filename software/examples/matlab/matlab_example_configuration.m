function matlab_example_configuration()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XXYYZZ'; % Change XXYYZZ to the UID of your DC Brick

    ipcon = IPConnection(); % Create IP connection
    dc = handle(BrickDC(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    dc.setDriveMode(BrickDC.DRIVE_MODE_DRIVE_COAST);
    dc.setPWMFrequency(10000); % Use PWM frequency of 10kHz
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward
    dc.enable(); % Enable motor power

    input('Press key to exit\n', 's');
    dc.disable(); % Disable motor power
    ipcon.disconnect();
end
