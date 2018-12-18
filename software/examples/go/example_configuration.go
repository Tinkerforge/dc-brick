package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/dc_brick"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
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

	dc.SetDriveMode(dc_brick.DriveModeDriveCoast)
	dc.SetPWMFrequency(10000) // Use PWM frequency of 10kHz
	dc.SetAcceleration(5000)  // Slow acceleration
	dc.SetVelocity(32767)     // Full speed forward
	dc.Enable()               // Enable motor power

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	dc.Disable() // Disable motor power
}
