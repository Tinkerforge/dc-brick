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
		dc.SetPWMFrequency(10000); // Use PWM frequency of 10kHz
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward
		dc.Enable(); // Enable motor power

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		dc.Disable(); // Disable motor power
		ipcon.Disconnect();
	}
}
