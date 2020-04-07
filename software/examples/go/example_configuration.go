package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/dc_brick"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"time"
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
	dc.SetPWMFrequency(10000) // Use PWM frequency of 10 kHz
	dc.SetAcceleration(4096)  // Slow acceleration (12.5 %/s)
	dc.SetVelocity(32767)     // Full speed forward (100 %)
	dc.Enable()               // Enable motor power

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	// Stop motor before disabling motor power
	dc.SetAcceleration(16384)           // Fast decceleration (50 %/s) for stopping
	dc.SetVelocity(0)                   // Request motor stop
	time.Sleep(2000 * time.Millisecond) // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	dc.Disable()                        // Disable motor power
}
