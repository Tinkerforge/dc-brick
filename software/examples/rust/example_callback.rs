use std::{error::Error, io, thread};
use tinkerforge::{dc_brick::*, ip_connection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let dc = DcBrick::new(UID, &ipcon); // Create device object

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd
                                          // Don't use device before ipcon is connected

    // The acceleration has to be smaller or equal to the maximum
    // acceleration of the DC motor, otherwise the velocity reached
    // callback will be called too early
    dc.set_acceleration(5000); // Slow acceleration
    dc.set_velocity(32767); // Full speed forward

    
    let velocity_reached_receiver = dc.get_velocity_reached_callback_receiver();
    
    // Spawn thread to handle received callback messages. This thread ends when the dc
    // is dropped, so there is no need for manual cleanup.
    let dc_copy = dc.clone(); //Device objects don't implement Sync, so they can't be shared between threads (by reference). So clone the device and move the copy.
    thread::spawn(move || {
        for velocity_reached in velocity_reached_receiver {
            if velocity_reached == 32767 {
                println!("Velocity: Full speed forward, now turning backward");
                dc_copy.set_velocity(-32767);
            } else if velocity_reached == -32767 {
                println!("Velocity: Full speed backward, now turning forward");
                dc_copy.set_velocity(32767);
            } else {
                //can only happen if another program sets velocity
                panic!("Error");
            }
        }
    });

    // Enable motor power
    dc.enable();

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    dc.disable(); // Disable motor power
    ipcon.disconnect();
    Ok(())
}
