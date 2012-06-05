#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/brick_dc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'a4GePuz3m29' # Change to your UID

ipcon = IPConnection.new HOST, PORT # Create IP connection to brickd
dc = BrickDC.new UID # Create device object
ipcon.add_device dc # Add device to IP connection
# Don't use device before it is added to a connection

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
# of the dc motor, otherwise cb_reached will be called too early
dc.set_acceleration 5000 # Slow acceleration
dc.set_velocity 32767 # Full speed forward

puts 'Press key to exit'
$stdin.gets
ipcon.destroy
