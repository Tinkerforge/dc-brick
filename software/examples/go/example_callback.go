package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
    "github.com/Tinkerforge/go-api-bindings/dc_brick"
)

const ADDR string = "localhost:4223"
const UID string = "XXYYZZ" // Change XXYYZZ to the UID of your DC Brick.

func main() {
	ipcon := ipconnection.New()
    defer ipcon.Close()
	dc, _ := dc_brick.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
    defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// The acceleration has to be smaller or equal to the maximum
	// acceleration of the DC motor, otherwise the velocity reached
	// callback will be called too early
	dc.SetAcceleration(5000) // Slow acceleration
	dc.SetVelocity(32767)    // Full speed forward

	dc.RegisterVelocityReachedCallback(func(velocity int16) {
		if velocity == 32767 {
			fmt.Println("Velocity: Full speed forward, now turning backward")
			dc.SetVelocity(-32767)
		} else if velocity == -32767 {
			fmt.Println("Velocity: Full speed backward, now turning forward")
			dc.SetVelocity(32767)
		} else {
			//can only happen if another program sets velocity
			fmt.Println("Error")
		}
	})

	// Enable motor power
	dc.Enable()

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	dc.Disable() // Disable motor power
	ipcon.Disconnect()
}
