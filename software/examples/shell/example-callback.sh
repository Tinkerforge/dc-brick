#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change XXYYZZ to the UID of your DC Brick

# The acceleration has to be smaller or equal to the maximum
# acceleration of the DC motor, otherwise the velocity reached
# callback will be called too early
tinkerforge call dc-brick $uid set-acceleration 4096 # Slow acceleration (12.5 %/s)
tinkerforge call dc-brick $uid set-velocity 32767 # Full speed forward (100 %)

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
tinkerforge dispatch dc-brick $uid velocity-reached\
 --execute "if   [ {velocity} -eq  32767 ]; then tinkerforge call dc-brick $uid set-velocity -32767;
            elif [ {velocity} -eq -32767 ]; then tinkerforge call dc-brick $uid set-velocity  32767;
            else echo error; fi" &

# Enable motor power
tinkerforge call dc-brick $uid enable

echo "Press key to exit"; read dummy

# Stop motor before disabling motor power
tinkerforge call dc-brick $uid set-acceleration 16384 # Fast decceleration (50 %/s) for stopping
tinkerforge call dc-brick $uid set-velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
tinkerforge call dc-brick $uid disable # Disable motor power

kill -- -$$ # Stop callback dispatch in background
