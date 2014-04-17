function octave_example_configuration()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "5VF5vG"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    dc = java_new("com.tinkerforge.BrickDC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    dc.setPWMFrequency(10000); % Use PWM frequency of 10kHz
    dc.setDriveMode(1); % Use 1 = Drive/Coast instead of 0 = Drive/Brake

    dc.enable();
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
