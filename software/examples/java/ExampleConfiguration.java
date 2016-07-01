import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickDC;

public class ExampleConfiguration {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XXYYZZ to the UID of your DC Brick
	private static final String UID = "XXYYZZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		dc.setDriveMode(BrickDC.DRIVE_MODE_DRIVE_COAST);
		dc.setPWMFrequency(10000); // Use PWM frequency of 10kHz
		dc.setAcceleration(5000); // Slow acceleration
		dc.setVelocity((short)32767); // Full speed forward
		dc.enable(); // Enable motor power

		System.out.println("Press key to exit"); System.in.read();
		dc.disable(); // Disable motor power
		ipcon.disconnect();
	}
}
