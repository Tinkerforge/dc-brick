
#include <stdio.h>

#include "ip_connection.h"
#include "brick_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "apaYPikNHEj" // Change to your UID

// Use velocity reached callback to swing back and forth
void cb_reached(int16_t velocity, void *user_data) {
	DC *dc = (DC *)user_data;

	if(velocity == 32767) {
		printf("Velocity: Full Speed forward, turning backward\n");
		dc_set_velocity(dc, -32767);
	} else if(velocity == -32767) {
		printf("Velocity: Full Speed backward, turning forward\n");
		dc_set_velocity(dc, 32767);
	} else {
		printf("Error\n"); // Can only happen if another program sets velocity
	}
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DC dc;
	dc_create(&dc, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Register "velocity reached callback" to cb_reached
	// cb_reached will be called every time a velocity set with
	// set_velocity is reached
	dc_register_callback(&dc, 
	                     DC_CALLBACK_VELOCITY_REACHED, 
	                     (void *)cb_reached,
	                     &dc);

	dc_enable(&dc);

	// The acceleration has to be smaller or equal to the maximum acceleration
	// of the dc motor, otherwise cb_reached will be called too early
	dc_set_acceleration(&dc, 5000); // Slow acceleration
	dc_set_velocity(&dc, 32767); // Full speed forward

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
