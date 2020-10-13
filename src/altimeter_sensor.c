#include "altimeter_sensor.h"
#include <devicetree.h>
#include "sensor_float.h"

#define HTS221 DT_INST(0, st_hts221)
#define HTS221_LABEL DT_LABEL(HTS221)
#define LPS22HB DT_INST(0, st_lps22hb_press)
#define LPS22HB_LABEL DT_LABEL(LPS22HB)

int altimeter_sensor_init(struct altimeter_sensor *sensor) {
	sensor->humid_temp_sensor = device_get_binding(HTS221_LABEL);
	sensor->baro_sensor = device_get_binding(LPS22HB_LABEL);
	if(!sensor->humid_temp_sensor || !sensor->baro_sensor) {
		return -1;
	}
	return 0;
}

int altimeter_sensor_update(struct altimeter_sensor *sensor) {
	int ret;
	ret = sensor_sample_fetch(sensor->humid_temp_sensor);
	if(ret != 0) {
		return ret;
	}
	ret = sensor_sample_fetch(sensor->baro_sensor);
	if(ret != 0) {
		return ret;
	}
	sensor_channel_get(sensor->humid_temp_sensor, SENSOR_CHAN_HUMIDITY, &sensor->humidity);
	sensor_channel_get(sensor->humid_temp_sensor, SENSOR_CHAN_AMBIENT_TEMP, &sensor->temp);
	sensor_channel_get(sensor->baro_sensor, SENSOR_CHAN_PRESS, &sensor->press);

	float alt = altitude_equation(sensor_val_to_float(&sensor->press),
	                              sensor_val_to_float(&sensor->temp),
	                              sensor_val_to_float(&sensor->humidity));
	float_to_sensor_value(alt, &sensor->altitude);
}