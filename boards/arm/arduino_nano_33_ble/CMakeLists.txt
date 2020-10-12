# Copyright (c) 2020 Jefferson Lee.
# SPDX-License-Identifier: Apache-2.0

zephyr_library_named("arduino_nano_33_ble")
target_include_directories(${ZEPHYR_CURRENT_LIBRARY} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")

if(CONFIG_BOARD_ARDUINO_NANO_33_BLE_INIT_ARDUINO_STYLE)
  zephyr_library_sources("${CMAKE_CURRENT_SOURCE_DIR}/src/init_arduino_style.c")
else()
  message(WARNING "you have not enabled the internal I2C sensors. They will be unavailable")
endif()
