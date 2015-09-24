function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XXYYZZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    dc = BrickDC(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % The acceleration has to be smaller or equal to the maximum
    % acceleration of the DC motor, otherwise the velocity reached
    % callback will be called too early
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward

    % Register velocity reached callback to function cb_velocity_reached
    set(dc, 'VelocityReachedCallback', @(h, e) cb_velocity_reached(e));

    % Enable motor power
    dc.enable();

    input('Press key to exit\n', 's');
    dc.disable(); % Disable motor power
    ipcon.disconnect();
end

% Use velocity reached callback to swing back and forth
% between full speed forward and full speed backward
function cb_velocity_reached(e)
    dc = e.getSource();

    if e.velocity == 32767
        fprintf('Velocity: Full speed forward, now turning backward\n');
        dc.setVelocity(-32767);
    elseif e.velocity == -32767
        fprintf('Velocity: Full speed backward, now turning forward\n');
        dc.setVelocity(32767);
    else
        fprintf('Error\n'); % Can only happen if another program sets velocity
    end
end
