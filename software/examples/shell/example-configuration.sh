#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# use PWM frequency of 10kHz
tinkerforge call dc-brick $uid set-pwm-frequency 10000

# use drive/coast instead of drive/brake
tinkerforge call dc-brick $uid set-drive-mode drive-coast

# enable motor controller
tinkerforge call dc-brick $uid enable

# slow acceleration
tinkerforge call dc-brick $uid set-acceleration 5000

# full speed forward
tinkerforge call dc-brick $uid set-velocity 32767
