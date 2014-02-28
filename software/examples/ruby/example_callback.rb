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

# Use velocity reached callback to swing back and forth between
# full speed forward and full speed backward
dc.register_callback(BrickDC::CALLBACK_VELOCITY_REACHED) do |velocity|
  if velocity == 32767
    puts 'Velocity: Full Speed forward, turning backward'
    dc.set_velocity(-32767)
  elsif velocity == -32767
    puts 'Velocity: Full Speed backward, turning forward'
    dc.set_velocity 32767
  else
    puts 'Error' # Can only happen if another program sets velocity
  end
end

dc.enable
# The acceleration has to be smaller or equal to the maximum acceleration
# of the DC motor, otherwise cb_reached will be called too early
dc.set_acceleration 5000 # Slow acceleration
dc.set_velocity 32767 # Full speed forward

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
