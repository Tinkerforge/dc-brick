#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change XXYYZZ to the UID of your DC Brick

tinkerforge call dc-brick $uid set-drive-mode drive-mode-drive-coast
tinkerforge call dc-brick $uid set-pwm-frequency 10000 # Use PWM frequency of 10kHz
tinkerforge call dc-brick $uid set-acceleration 5000 # Slow acceleration
tinkerforge call dc-brick $uid set-velocity 32767 # Full speed forward
tinkerforge call dc-brick $uid enable # Enable motor power

echo "Press key to exit"; read dummy

tinkerforge call dc-brick $uid disable # Disable motor power
