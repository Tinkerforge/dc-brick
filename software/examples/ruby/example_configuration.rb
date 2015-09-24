#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_dc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XXYYZZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
dc = BrickDC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

dc.set_drive_mode BrickDC::DRIVE_MODE_DRIVE_COAST
dc.set_pwm_frequency 10000 # Use PWM frequency of 10kHz
dc.set_acceleration 5000 # Slow acceleration
dc.set_velocity 32767 # Full speed forward
dc.enable # Enable motor power

puts 'Press key to exit'
$stdin.gets
dc.disable # Disable motor power
ipcon.disconnect
