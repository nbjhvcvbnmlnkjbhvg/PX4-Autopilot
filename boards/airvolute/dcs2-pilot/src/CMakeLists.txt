############################################################################
#
# Airvolute DCS2.Pilot STM32H743 DroneCAN node board support
#
############################################################################

if("${PX4_BOARD_LABEL}" STREQUAL  "canbootloader")

	add_library(drivers_board
		boot_config.h
		boot.c
	)
	target_link_libraries(drivers_board
		PRIVATE
			nuttx_arch
			nuttx_drivers
			canbootloader
	)
	target_include_directories(drivers_board PRIVATE ${PX4_SOURCE_DIR}/platforms/nuttx/src/canbootloader)

else()
	add_library(drivers_board
		can.c
		i2c.cpp
		init.c
		spi.cpp
		timer_config.cpp
	)

	target_link_libraries(drivers_board
		PRIVATE
			arch_io_pins
			arch_spi
			drivers__device
			nuttx_arch
			nuttx_drivers
			px4_layer
	)
endif()
