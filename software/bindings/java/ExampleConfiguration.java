import com.tinkerforge.BrickDC;
import com.tinkerforge.IPConnection;

public class ExampleConfiguration {
	private static final String host = new String("localhost");
	private static final int port = 4223;
	private static final String UID = new String("aetiNB3mX2u"); // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(host, port); // Create connection to brickd (Can throw IOException)

		BrickDC dc = new BrickDC(UID); // Create device object
		ipcon.addDevice(dc); // Add device to ip connection (Can throw IPConnection.TimeoutException)
		// Don't use device before it is added to a connection
		

		dc.setPWMFrequency(10000); // Use PWM frequency of 10khz
		dc.setDriveMode((short)1); // use 1 = Drive/Coast instead of 0 = Drive/Brake

		dc.enable();
		dc.setAcceleration(5000); // Slow acceleration
		dc.setVelocity((short)32767); // Full speed forward
		
		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
