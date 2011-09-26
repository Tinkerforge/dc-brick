using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "aetiNB3mX2u"; // Change to your UID

	private static BrickDC dc;

	// Use velocity reached callback to swing back and forth between
	// full speed forward and full speed backward
	static void ReachedCB(short velocity)
	{
		if(velocity == 32767)
		{
			System.Console.WriteLine("Velocity: Full Speed forward, turning backward");
			dc.SetVelocity(-32767);
		}
		else if(velocity == -32767)
		{
			System.Console.WriteLine("Velocity: Full Speed backward, turning forward");
			dc.SetVelocity(32767);
		}
		else
		{
			// Can only happen if another program sets velocity
			System.Console.WriteLine("Error");
		}
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		dc = new BrickDC(UID); // Create device object
		ipcon.AddDevice(dc); // Add device to ip connection
		// Don't use device before it is added to a connection


		// Register "velocity reached callback" to ReachedCB
		// cb_reached will be called every time a velocity set with
		// set_velocity is reached
		dc.RegisterCallback(new BrickDC.VelocityReached(ReachedCB));

		dc.Enable();
		// The acceleration has to be smaller or equal to the maximum acceleration
		// of the dc motor, otherwise ReachedCB will be called too early
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
