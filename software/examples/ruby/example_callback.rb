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

# The acceleration has to be smaller or equal to the maximum
# acceleration of the DC motor, otherwise the velocity reached
# callback will be called too early
dc.set_acceleration 4096 # Slow acceleration (12.5 %/s)
dc.set_velocity 32767 # Full speed forward (100 %)

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
dc.register_callback(BrickDC::CALLBACK_VELOCITY_REACHED) do |velocity|
  if velocity == 32767
    puts 'Velocity: Full speed forward, now turning backward'
    dc.set_velocity(-32767)
  elsif velocity == -32767
    puts 'Velocity: Full speed backward, now turning forward'
    dc.set_velocity 32767
  else
    puts 'Error' # Can only happen if another program sets velocity
  end
end

# Enable motor power
dc.enable

puts 'Press key to exit'
$stdin.gets

# Stop motor before disabling motor power
dc.set_acceleration 16384 # Fast decceleration (50 %/s) for stopping
dc.set_velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
dc.disable # Disable motor power

ipcon.disconnect
