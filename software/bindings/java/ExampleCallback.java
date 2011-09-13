import com.tinkerforge.BrickDC;
import com.tinkerforge.IPConnection;

public class ExampleCallback {
	private static final String host = new String("localhost");
	private static final int port = 4223;
	private static final String UID = new String("aetiNB3mX2u"); // Change to your UID

	// Declare dc static, so the listener can use it. In a real program you probably
	// want to make a real listener class (not the anonym inner class) and pass the dc
	// reference to it. But we want to keep the examples as short es possible.
	static BrickDC dc;
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(host, port); // Create connection to brickd (Can throw IOException)

		dc = new BrickDC(UID); // Create device object
		ipcon.addDevice(dc); // Add device to ip connection (Can throw IPConnection.TimeoutException)
		// Don't use device before it is added to a connection
		

		// Add and implement velocity reached listener 
		// (called if velocity set by set_velocity is reached)
		dc.addListener(new BrickDC.VelocityReachedListener() {
			public void velocityReached(short velocity) {
				if(velocity == 32767) {
					System.out.println("Velocity: Full Speed forward, turning backward");
					ExampleCallback.dc.setVelocity((short)-32767);
				} else if(velocity == -32767) {
					System.out.println("Velocity: Full Speed backward, turning forward");
					ExampleCallback.dc.setVelocity((short)32767);
				} else {
					System.out.println("Error"); // Can only happen if another program sets velocity
				}
			}
		});

		dc.enable();
		// The acceleration has to be smaller or equal to the maximum acceleration
		// of the dc motor, otherwise cb_reached will be called too early
		dc.setAcceleration(5000); // Slow acceleration
		dc.setVelocity((short)32767); // Full speed forward
		
		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
