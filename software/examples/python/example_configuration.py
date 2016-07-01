#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XXYYZZ" # Change XXYYZZ to the UID of your DC Brick

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_dc import BrickDC

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.set_drive_mode(dc.DRIVE_MODE_DRIVE_COAST)
    dc.set_pwm_frequency(10000) # Use PWM frequency of 10kHz
    dc.set_acceleration(5000) # Slow acceleration
    dc.set_velocity(32767) # Full speed forward
    dc.enable() # Enable motor power

    raw_input("Press key to exit\n") # Use input() in Python 3
    dc.disable() # Disable motor power
    ipcon.disconnect()
