function matlab_example_callback
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = '5VF5vG'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    dc = BrickDC(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register "velocity reached callback" to cb_reached
    % cb_reached will be called every time a velocity set with
    % set_velocity is reached
    set(dc, 'VelocityReachedCallback', @(h, e) cb_reached(e));

    dc.enable();
    % The acceleration has to be smaller or equal to the maximum acceleration
    % of the dc motor, otherwise cb_reached will be called too early
    dc.setAcceleration(5000); % Slow acceleration
    dc.setVelocity(32767); % Full speed forward

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Use velocity reached callback to swing back and forth between
% full speed forward and full speed backward
function cb_reached(e)
    dc = e.getSource();

    if e.velocity == 32767
        fprintf('Velocity: Full Speed forward, turning backward\n');
        dc.setVelocity(-32767);
    elseif e.velocity == -32767
        fprintf('Velocity: Full Speed backward, turning forward\n');
        dc.setVelocity(32767);
    else
        fprintf('Error\n'); % Can only happen if another program sets velocity
    end
end
