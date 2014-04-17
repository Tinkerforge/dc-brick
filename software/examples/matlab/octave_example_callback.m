function octave_example_callback
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "5VF5vG"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    dc = java_new("com.tinkerforge.BrickDC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register "velocity reached callback" to cb_reached
    % cb_reached will be called every time a velocity set with
    % set_velocity is reached
    dc.addVelocityReachedCallback(@cb_reached);

    dc.enable();
    % The acceleration has to be smaller or equal to the maximum acceleration
    % of the dc motor, otherwise cb_reached will be called too early
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Use velocity reached callback to swing back and forth between
% full speed forward and full speed backward
function cb_reached(e)
    dc = e.getSource();

    if str2num(e.velocity.toString()) == 32767
        fprintf("Velocity: Full Speed forward, turning backward\n");
        dc.setVelocity(-32767);
    elseif str2num(e.velocity.toString()) == -32767
        fprintf("Velocity: Full Speed backward, turning forward\n");
        dc.setVelocity(32767);
    else
        fprintf("Error\n"); % Can only happen if another program sets velocity
    end
end
