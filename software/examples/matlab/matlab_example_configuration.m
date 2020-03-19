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
    dc.setPWMFrequency(10000); % Use PWM frequency of 10 kHz
    dc.setAcceleration(4096); % Slow acceleration (12.5 %/s)
    dc.setVelocity(32767); % Full speed forward (100 %)
    dc.enable(); % Enable motor power

    input('Press key to exit\n', 's');

    % Stop motor before disabling motor power
    dc.setAcceleration(16384); % Fast decceleration (50 %/s) for stopping
    dc.setVelocity(0); % Request motor stop
    pause(2); % Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    dc.disable(); % Disable motor power

    ipcon.disconnect();
end
