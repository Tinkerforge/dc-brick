#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_dc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XXYYZZ' # Change XXYYZZ to the UID of your DC Brick

ipcon = IPConnection.new # Create IP connection
dc = BrickDC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

dc.set_drive_mode BrickDC::DRIVE_MODE_DRIVE_COAST
dc.set_pwm_frequency 10000 # Use PWM frequency of 10 kHz
dc.set_acceleration 4096 # Slow acceleration (12.5 %/s)
dc.set_velocity 32767 # Full speed forward (100 %)
dc.enable # Enable motor power

puts 'Press key to exit'
$stdin.gets

# Stop motor before disabling motor power
dc.set_acceleration 16384 # Fast decceleration (50 %/s) for stopping
dc.set_velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
dc.disable # Disable motor power

ipcon.disconnect
