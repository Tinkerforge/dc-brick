use std::{error::Error, io, thread};
use tinkerforge::{dc_brick::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let dc_brick = DCBrick::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // The acceleration has to be smaller or equal to the maximum
    // acceleration of the DC motor, otherwise the velocity reached
    // callback will be called too early
    dc_brick.set_acceleration(5000); // Slow acceleration
    dc_brick.set_velocity(32767); // Full speed forward

    //Create listener for velocity reached events.
    let velocity_reached_listener = dc_brick.get_velocity_reached_receiver();
    // Spawn thread to handle received events. This thread ends when the dc_brick
    // is dropped, so there is no need for manual cleanup.
    let dc_brick_copy = dc_brick.clone(); //Device objects don't implement Sync, so they can't be shared between threads (by reference). So clone the device and move the copy.
    thread::spawn(move || {
        for event in velocity_reached_listener {
            if event == 32767 {
                println!("Velocity: Full speed forward, now turning backward");
                dc_brick_copy.set_velocity(-32767);
            } else if event == -32767 {
                println!("Velocity: Full speed backward, now turning forward");
                dc_brick_copy.set_velocity(32767);
            } else {
                //can only happen if another program sets velocity
                panic!("Error");
            }
        }
    });

    // Enable motor power
    dc_brick.enable();

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    dc_brick.disable(); // Disable motor power
    ipcon.disconnect();
    Ok(())
}
