use std::{error::Error, io, thread, time::Duration};
use tinkerforge::{dc_brick::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let dc = DcBrick::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    dc.set_drive_mode(DC_BRICK_DRIVE_MODE_DRIVE_COAST).recv()?;
    dc.set_pwm_frequency(10000).recv()?; // Use PWM frequency of 10 kHz
    dc.set_acceleration(4096).recv()?; // Slow acceleration (12.5 %/s)
    dc.set_velocity(32767).recv()?; // Full speed forward (100 %)
    dc.enable().recv()?; // Enable motor power

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;

    // Stop motor before disabling motor power
    dc.set_acceleration(16384).recv()?; // Fast decceleration (50 %/s) for stopping
    dc.set_velocity(0).recv()?; // Request motor stop
    thread::sleep(Duration::from_millis(2000)); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    dc.disable().recv()?; // Disable motor power

    ipcon.disconnect();
    Ok(())
}
