#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_dc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'a4GePuz3m29' # Change to your UID

ipcon = IPConnection.new # Create IP connection
dc = BrickDC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

dc.set_pwm_frequency 10000 # Use PWM frequency of 10khz
dc.set_drive_mode 1 # Use 1 = Drive/Coast instead of 0 = Drive/Brake

dc.enable
dc.set_acceleration 5000 # Slow acceleration
dc.set_velocity 32767 # Full speed forward

puts 'Press key to exit'
$stdin.gets
