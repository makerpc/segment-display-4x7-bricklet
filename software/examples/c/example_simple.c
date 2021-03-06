#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_segment_display_4x7.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

const uint8_t digits[] = {0x3f,0x06,0x5b,0x4f,
                          0x66,0x6d,0x7d,0x07,
                          0x7f,0x6f,0x77,0x7c,
                          0x39,0x5e,0x79,0x71}; // 0~9,A,b,C,d,E,F

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SegmentDisplay4x7 sd4x7;
	segment_display_4x7_create(&sd4x7, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Write "4223" to the display with full brightness without colon
	uint8_t segments[4] = {digits[4], digits[2], digits[2], digits[3]};
	segment_display_4x7_set_segments(&sd4x7, segments, 7, false);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
