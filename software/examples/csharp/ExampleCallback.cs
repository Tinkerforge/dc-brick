using System;
using System.Threading;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XXYYZZ"; // Change XXYYZZ to the UID of your DC Brick

	// Use velocity reached callback to swing back and forth
	// between full speed forward and full speed backward
	static void VelocityReachedCB(BrickDC sender, short velocity)
	{
		if(velocity == 32767)
		{
			Console.WriteLine("Velocity: Full speed forward, now turning backward");
			sender.SetVelocity(-32767);
		}
		else if(velocity == -32767)
		{
			Console.WriteLine("Velocity: Full speed backward, now turning forward");
			sender.SetVelocity(32767);
		}
		else
		{
			// Can only happen if another program sets velocity
			Console.WriteLine("Error");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// The acceleration has to be smaller or equal to the maximum
		// acceleration of the DC motor, otherwise the velocity reached
		// callback will be called too early
		dc.SetAcceleration(4096); // Slow acceleration (12.5 %/s)
		dc.SetVelocity(32767); // Full speed forward (100 %)

		// Register velocity reached callback to function VelocityReachedCB
		dc.VelocityReachedCallback += VelocityReachedCB;

		// Enable motor power
		dc.Enable();

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
