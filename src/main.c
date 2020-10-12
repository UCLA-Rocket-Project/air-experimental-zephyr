#include <device.h>
#include <devicetree.h>
#include <logging/log.h>
#include <usb/usb_device.h>
#include <arduino_nano_33_ble.h>
#include <stdbool.h>
#include <arch/arm/aarch32/exc.h>
#include <fatal.h>
#include <drivers/sensor.h>
LOG_MODULE_REGISTER(cdc_acm_echo, LOG_LEVEL_DBG);

#define HTS221 DT_INST(0, st_hts221)

#if DT_NODE_HAS_STATUS(HTS221, okay)
#define HTS221_LABEL DT_LABEL(HTS221)
#else
#error Your devicetree has no enabled nodes with compatible "st_lps22hb_press"
#define LPS22HB_LABEL "<none>"
#endif



static struct arduino_gpio_t gpio;

// setup the logging interface spawn worker threads
void main() {
	arduino_gpio_init(&gpio);
	arduino_gpio_pinMode(&gpio, ARDUINO_LEDR, GPIO_OUTPUT);
	arduino_gpio_digitalWrite(&gpio, ARDUINO_LEDR, 1);
	const struct device *dev = device_get_binding("CDC_ACM_0");
	usb_enable(NULL);

	// pull in the sensors
	const struct device *tempSensor = device_get_binding(HTS221_LABEL);
	const struct sensor_value temperature;
	if(!tempSensor) {
		while(1) {
			printk("Failed to get device\n");
			k_sleep(K_SECONDS(5));
		}
	}


	bool ledOn = false;
	while(1) {
		ledOn = !ledOn;
		arduino_gpio_digitalWrite(&gpio, ARDUINO_LEDR, ledOn);
		sensor_sample_fetch(tempSensor);
		sensor_channel_get(tempSensor, SENSOR_CHAN_AMBIENT_TEMP, &temperature);

		printk("in Centigrade: %ld.%ld\n", temperature.val1, temperature.val2);

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