#pragma once
#include <drivers/sensor.h>
#include <math.h>

static float sensor_val_to_float(struct sensor_value *val) {
	return (float)(val->val1 + val->val2 / 1.00E6);
}
static void float_to_sensor_value(float f, struct sensor_value *val) {
	float intpart, fracpart;
	fracpart = modff(f, &intpart);
	val->val1 = (int32_t)intpart;
	val->val2 = (int32_t)(fracpart * 1e6);
}