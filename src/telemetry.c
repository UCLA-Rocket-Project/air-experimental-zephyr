#include "telemetry.h"
#include <string.h>

K_MUTEX_DEFINE(telemetryMutex);
volatile float telemetry[__COUNT] = {0};

void telemetry_packetize(uint8_t buf[sizeof(float)*__COUNT+2]) {
	k_mutex_lock(&telemetryMutex, K_FOREVER);
	memcpy(buf+1, telemetry, sizeof(float)*__COUNT);
	k_mutex_unlock(&telemetryMutex);

	// begin COBS encoding
	// last byte is zero
	buf[sizeof(float)*__COUNT+1] = 0;
	uint8_t *zeroPtr = buf;
	for(int i = 1; i < sizeof(float)*__COUNT+2; i++) {
		if(buf[i] != 0) {
			continue;
		}
		*zeroPtr = (buf+i) - zeroPtr;
		zeroPtr = buf+i;
	}
}