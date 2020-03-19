#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change XXYYZZ to the UID of your DC Brick

tinkerforge call dc-brick $uid set-drive-mode drive-mode-drive-coast
tinkerforge call dc-brick $uid set-pwm-frequency 10000 # Use PWM frequency of 10 kHz
tinkerforge call dc-brick $uid set-acceleration 4096 # Slow acceleration (12.5 %/s)
tinkerforge call dc-brick $uid set-velocity 32767 # Full speed forward (100 %)
tinkerforge call dc-brick $uid enable # Enable motor power

echo "Press key to exit"; read dummy

# Stop motor before disabling motor power
tinkerforge call dc-brick $uid set-acceleration 16384 # Fast decceleration (50 %/s) for stopping
tinkerforge call dc-brick $uid set-velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
tinkerforge call dc-brick $uid disable # Disable motor power
