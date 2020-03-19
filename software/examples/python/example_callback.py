#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XXYYZZ" # Change XXYYZZ to the UID of your DC Brick

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_dc import BrickDC

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
def cb_velocity_reached(velocity, dc):
    if velocity == 32767:
        print('Velocity: Full speed forward, now turning backward')
        dc.set_velocity(-32767)
    elif velocity == -32767:
        print('Velocity: Full speed backward, now turning forward')
        dc.set_velocity(32767)
    else:
        print('Error') # Can only happen if another program sets velocity

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # The acceleration has to be smaller or equal to the maximum
    # acceleration of the DC motor, otherwise the velocity reached
    # callback will be called too early
    dc.set_acceleration(4096) # Slow acceleration (12.5 %/s)
    dc.set_velocity(32767) # Full speed forward (100 %)

    # Register velocity reached callback to function cb_velocity_reached
    dc.register_callback(dc.CALLBACK_VELOCITY_REACHED,
                         lambda x: cb_velocity_reached(x, dc))

    # Enable motor power
    dc.enable()

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    dc.set_acceleration(16384) # Fast decceleration (50 %/s) for stopping
    dc.set_velocity(0) # Request motor stop
    time.sleep(2) # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    dc.disable() # Disable motor power

    ipcon.disconnect()
