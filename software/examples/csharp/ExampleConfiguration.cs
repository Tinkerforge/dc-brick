using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "aetiNB3mX2u"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickDC dc = new BrickDC(UID); // Create device object
		ipcon.AddDevice(dc); // Add device to IP connection
		// Don't use device before it is added to a connection

		dc.SetPWMFrequency(10000); // Use PWM frequency of 10khz
		dc.SetDriveMode(1); // Use 1 = Drive/Coast instead of 0 = Drive/Brake

		dc.Enable();
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
		ipcon.Destroy();
	}
}
