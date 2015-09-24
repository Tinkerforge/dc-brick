using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XXYYZZ"; // Change to your UID

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
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward

		// Register velocity reached callback to function VelocityReachedCB
		dc.VelocityReached += VelocityReachedCB;

		// Enable motor power
		dc.Enable();

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		dc.Disable(); // Disable motor power
		ipcon.Disconnect();
	}
}
