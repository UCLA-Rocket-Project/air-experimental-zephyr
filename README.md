# Air 2021 Experimental
This is an experimental rewrite of the air 2020 software
utilizing the Zephyr RTOS.

This repo includes the source code as well as:
* Board support package for the Arduino Nano BLE 33

## Instructions
### Setup
1. Follow these instructions to setup Zephyr: https://docs.zephyrproject.org/latest/getting_started/index.html
1. Follow these instructions to steal a copy of BOSSAC: [instructions](boards/arm/arduino_nano_33_ble/doc/index.rst)
Make sure you add it into your OS's PATH variable

## First time code setup
1. Run `./compile.sh`

### Flashing
1. Double-tap your Arduino Nano 33 BLE's reset button. 
There should now be a pulsing orange light near the USB port.
1. Run `flash.bat <COM PORT>` for Windows users. I don't have Mac/Linux so you
can figure it out yourselves.
1. Your device should disconnect and reconnect under a new COM Port name, with 
the name of UCLA Rocket Project or something like that