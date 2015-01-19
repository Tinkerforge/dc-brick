using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "aetiNB3mX2u"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		dc.SetPWMFrequency(10000); // Use PWM frequency of 10kHz
		dc.SetDriveMode(1); // Use 1 = Drive/Coast instead of 0 = Drive/Brake

		dc.Enable();
		dc.SetAcceleration(5000); // Slow acceleration
		dc.SetVelocity(32767); // Full speed forward

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		dc.Disable();
		ipcon.Disconnect();
	}
}
