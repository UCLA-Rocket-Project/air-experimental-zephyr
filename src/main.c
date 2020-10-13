#include <device.h>
#include <logging/log.h>
#include <usb/usb_device.h>
#include <arduino_nano_33_ble.h>
#include <stdbool.h>
#include <arch/arm/aarch32/exc.h>
#include <fatal.h>
#include <drivers/sensor.h>
#include "altimeter_sensor.h"
#include "sensor_float.h"
#include <stdio.h>
LOG_MODULE_REGISTER(main_loop, LOG_LEVEL_DBG);

static struct arduino_gpio_t gpio;

// setup the logging interface spawn worker threads
void main() {
	arduino_gpio_init(&gpio);
	arduino_gpio_pinMode(&gpio, ARDUINO_LEDR, GPIO_OUTPUT);
	arduino_gpio_digitalWrite(&gpio, ARDUINO_LEDR, 1);
	const struct device *dev = device_get_binding("CDC_ACM_0");
	usb_enable(NULL);

	// pull in the sensors
	struct altimeter_sensor altimeter;
	altimeter_sensor_init(&altimeter);

	bool ledOn = false;
	while(1) {
		ledOn = !ledOn;
		arduino_gpio_digitalWrite(&gpio, ARDUINO_LEDR, ledOn);
		altimeter_sensor_update(&altimeter);
		float alt = sensor_val_to_float(&altimeter.altitude);

		printf("Altitude: %f (m)\n", alt);

		k_sleep(K_SECONDS(1));
	}
}
// handler for k_fatal_halt's
void k_sys_fatal_error_handler(unsigned int reason, const z_arch_esf_t *esf) {
	/*
	 * if we're here, theres a good chance everything is broken.
	 * Hopefully, the GPIO driver survived.
	 */
	arduino_gpio_digitalWrite(&gpio, ARDUINO_LEDR, 0);
	while(1) {
		LOG_ERR("Failed: %d\n", reason);
		k_sleep(K_SECONDS(5));
	}
}