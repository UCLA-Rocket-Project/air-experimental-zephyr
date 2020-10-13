#pragma once
#include <stdint.h>
#include <kernel.h>

enum TELEMETRY_FIELD: uint8_t {
	X_ACCEL,
	Y_ACCEL,
	Z_ACCEL,

	X_ROT,
	Y_ROT,
	Z_ROT,

	X_MAG,
	Y_MAG,
	Z_MAG,

	PRESS,
	TEMP,
	HUMIDITY,
	MAX_PRED_ALT,

	__COUNT
};

volatile extern float telemetry[__COUNT];
extern struct k_mutex telemetryMutex;
void telemetry_packetize(uint8_t buf[sizeof(float)*__COUNT+2]);