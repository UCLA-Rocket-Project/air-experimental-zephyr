set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(air_experimental_zephyr)

target_sources(app PRIVATE src/main.c)
target_link_libraries(app PUBLIC arduino_nano_33_ble)