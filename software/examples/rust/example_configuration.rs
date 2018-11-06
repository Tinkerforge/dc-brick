use std::{error::Error, io};

use tinkerforge::{dc_brick::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let dc_brick = DCBrick::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    dc_brick.set_drive_mode(DC_BRICK_DRIVE_MODE_DRIVE_COAST);
    dc_brick.set_pwm_frequency(10000); // Use PWM frequency of 10kHz
    dc_brick.set_acceleration(5000); // Slow acceleration
    dc_brick.set_velocity(32767); // Full speed forward
    dc_brick.enable(); // Enable motor power

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    dc_brick.disable(); // Disable motor power
    ipcon.disconnect();
    Ok(())
}
