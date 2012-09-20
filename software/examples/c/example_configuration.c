
#include <stdio.h>

#include "ip_connection.h"
#include "brick_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "apaYPikNHEj" // Change to your UID

int main() {
	// Create IP connection to brickd
	IPConnection ipcon;
	if(ipcon_create(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not create connection\n");
		exit(1);
	}

	// Create device object
	DC dc;
	dc_create(&dc, UID); 

	// Add device to IP connection
	if(ipcon_add_device(&ipcon, &dc) < 0) {
		fprintf(stderr, "Could not connect to Brick\n");
		exit(1);
	}
	// Don't use device before it is added to a connection

	dc_set_pwm_frequency(&dc, 10000); // Use PWM frequency of 10khz
	dc_set_drive_mode(&dc, 1); // Use 1 = Drive/Coast instead of 0 = Drive/Brake

	dc_enable(&dc);
	dc_set_acceleration(&dc, 5000); // Slow acceleration
	dc_set_velocity(&dc, 32767); // Full speed forward

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon);
}
