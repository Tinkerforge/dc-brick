using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "aetiNB3mX2u"; // Change to your UID


	// Use velocity reached callback to swing back and forth between
	// full speed forward and full speed backward
	static void ReachedCB(BrickDC sender, short velocity)
	{
		if(velocity == 32767)
		{
			System.Console.WriteLine("Velocity: Full Speed forward, turning backward");
			sender.SetVelocity(-32767);
		}
		else if(velocity == -32767)
		{
			System.Console.WriteLine("Velocity: Full Speed backward, turning forward");
			sender.SetVelocity(32767);
		}
		else
		{
			// Can only happen if another program sets velocity
			System.Console.WriteLine("Error");
		}
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register "velocity reached callback" to ReachedCB
		// ReachedCB will be called every time a velocity set with
		// SetVelocity is reached
		dc.VelocityReached += ReachedCB;

		dc.Enable();
		// The acceleration has to be smaller or equal to the maximum acceleration
		// of the dc motor, otherwise ReachedCB will be called too early
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
		ipcon.Disconnect();
	}
}
