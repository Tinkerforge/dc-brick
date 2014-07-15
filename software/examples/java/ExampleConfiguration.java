import com.tinkerforge.BrickDC;
import com.tinkerforge.IPConnection;

public class ExampleConfiguration {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "aetiNB3mX2u"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		dc.setPWMFrequency(10000); // Use PWM frequency of 10kHz
		dc.setDriveMode((short)1); // Use 1 = Drive/Coast instead of 0 = Drive/Brake

		dc.enable();
		dc.setAcceleration(5000); // Slow acceleration
		dc.setVelocity((short)32767); // Full speed forward

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
