#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XXYYZZ" # Change XXYYZZ to the UID of your DC Brick

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_dc import BrickDC

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.set_drive_mode(dc.DRIVE_MODE_DRIVE_COAST)
    dc.set_pwm_frequency(10000) # Use PWM frequency of 10 kHz
    dc.set_acceleration(4096) # Slow acceleration (12.5 %/s)
    dc.set_velocity(32767) # Full speed forward (100 %)
    dc.enable() # Enable motor power

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    dc.set_acceleration(16384) # Fast decceleration (50 %/s) for stopping
    dc.set_velocity(0) # Request motor stop
    time.sleep(2) # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    dc.disable() # Disable motor power

    ipcon.disconnect()
