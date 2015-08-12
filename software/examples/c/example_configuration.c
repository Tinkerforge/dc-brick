#include <stdio.h>

#include "ip_connection.h"
#include "brick_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DC dc;
	dc_create(&dc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	dc_set_pwm_frequency(&dc, 10000); // Use PWM frequency of 10kHz
	dc_set_drive_mode(&dc, 1); // Use 1 = Drive/Coast instead of 0 = Drive/Brake

	dc_enable(&dc);
	dc_set_acceleration(&dc, 5000); // Slow acceleration
	dc_set_velocity(&dc, 32767); // Full speed forward

	printf("Press key to exit\n");
	getchar();
	dc_disable(&dc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
