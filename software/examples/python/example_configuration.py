#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "apaYPikNHEj" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_dc import DC

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = DC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.set_pwm_frequency(10000) # Use PWM frequency of 10kHz
    dc.set_drive_mode(1) # Use 1 = Drive/Coast instead of 0 = Drive/Brake

    dc.enable()
    dc.set_acceleration(5000) # Slow acceleration
    dc.set_velocity(32767) # Full speed forward

    raw_input('Press key to exit\n') # Use input() in Python 3
    dc.disable()
    ipcon.disconnect()
