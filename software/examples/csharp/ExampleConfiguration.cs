using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		dc.SetDriveMode(BrickDC.DRIVE_MODE_DRIVE_COAST);
		dc.SetPWMFrequency(10000); // Use PWM frequency of 10 kHz
		dc.SetAcceleration(4096); // Slow acceleration (12.5 %/s)
		dc.SetVelocity(32767); // Full speed forward (100 %)
		dc.Enable(); // Enable motor power

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();

		// Stop motor before disabling motor power
		dc.SetAcceleration(16384); // Fast decceleration (50 %/s) for stopping
		dc.SetVelocity(0); // Request motor stop
		Thread.Sleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
		dc.Disable(); // Disable motor power

		ipcon.Disconnect();
	}
}
