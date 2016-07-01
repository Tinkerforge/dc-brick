import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickDC;
import com.tinkerforge.TinkerforgeException;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XXYYZZ to the UID of your DC Brick
	private static final String UID = "XXYYZZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare dc as final, so the listener can access it
		final BrickDC dc = new BrickDC(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// The acceleration has to be smaller or equal to the maximum
		// acceleration of the DC motor, otherwise the velocity reached
		// callback will be called too early
		dc.setAcceleration(5000); // Slow acceleration
		dc.setVelocity((short)32767); // Full speed forward

		// Use velocity reached callback to swing back and forth
		// between full speed forward and full speed backward
		dc.addVelocityReachedListener(new BrickDC.VelocityReachedListener() {
			public void velocityReached(short velocity) {
				if(velocity == 32767) {
					System.out.println("Velocity: Full speed forward, now turning backward");
					try {
						dc.setVelocity((short)-32767);
					} catch(TinkerforgeException e) {
					}
				} else if(velocity == -32767) {
					System.out.println("Velocity: Full speed backward, now turning forward");
					try {
						dc.setVelocity((short)32767);
					} catch(TinkerforgeException e) {
					}
				} else {
					System.out.println("Error"); // Can only happen if another program sets velocity
				}
			}
		});

		// Enable motor power
		dc.enable();

		System.out.println("Press key to exit"); System.in.read();
		dc.disable(); // Disable motor power
		ipcon.disconnect();
	}
}
