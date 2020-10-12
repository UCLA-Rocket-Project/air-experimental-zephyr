#pragma once

#include <device.h>
#include <drivers/sensor.h>

struct altimeter_sensor {
	const struct device *baro_sensor;
	const struct device *humid_temp_sensor;
	struct sensor_value press, temp, humidity, altitude;
};

int altimeter_sensor_init(struct altimeter_sensor *sensor);
int altimeter_sensor_update(struct altimeter_sensor *sensor);

#include <math.h>

const static float P0 = 101.325f;
// TODO: replace with a function that takes into account air density (humidity)
static inline float altitude_equation(float press, float temp, float humidity) {
	return (float)( (temp + 273.15) * log(P0 / press) );
}