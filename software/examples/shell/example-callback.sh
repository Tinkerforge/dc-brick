#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# enable motor controller
tinkerforge call dc-brick $uid enable

# the acceleration has to be smaller or equal to the maximum acceleration
# of the dc motor, otherwise the velocity-reached will be triggered too early

# slow acceleration
tinkerforge call dc-brick $uid set-acceleration 5000

# full speed forward
tinkerforge call dc-brick $uid set-velocity 32767

# this will be triggerd every time a velocity set with set-velocity is reached
tinkerforge dispatch dc-brick $uid velocity-reached\
 --execute "if   [ {velocity} -eq  32767 ]; then tinkerforge call dc-brick $uid set-velocity -32767;
            elif [ {velocity} -eq -32767 ]; then tinkerforge call dc-brick $uid set-velocity  32767;
            else echo error; fi"
