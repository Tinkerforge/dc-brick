function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XXYYZZ'; % Change XXYYZZ to the UID of your DC Brick

    ipcon = IPConnection(); % Create IP connection
    dc = handle(BrickDC(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % The acceleration has to be smaller or equal to the maximum
    % acceleration of the DC motor, otherwise the velocity reached
    % callback will be called too early
    dc.setAcceleration(4096); % Slow acceleration (12.5 %/s)
    dc.setVelocity(32767); % Full speed forward (100 %)

    % Register velocity reached callback to function cb_velocity_reached
    set(dc, 'VelocityReachedCallback', @(h, e) cb_velocity_reached(e));

    % Enable motor power
    dc.enable();

    input('Press key to exit\n', 's');

    % Stop motor before disabling motor power
    dc.setAcceleration(16384); % Fast decceleration (50 %/s) for stopping
    dc.setVelocity(0); % Request motor stop
    pause(2); % Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
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
