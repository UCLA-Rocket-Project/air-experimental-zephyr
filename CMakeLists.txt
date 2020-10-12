set(CMAKE_CXX_STANDARD 11)
set(BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(BOARD "arduino_nano_33_ble")
cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(air_experimental_zephyr C)

target_sources(app PRIVATE src/main.c src/altimeter_sensor.c src/altimeter_sensor.h src/sensor_float.h)
target_link_libraries(app PUBLIC arduino_nano_33_ble)