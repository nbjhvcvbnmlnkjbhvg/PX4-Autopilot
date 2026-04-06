/**
 * @file spi.cpp
 *
 * DCS2.Pilot SPI bus initialization
 * SPI1: BMI088 (accel + gyro) + BMP390 barometer
 */

#include <px4_platform_common/px4_config.h>

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>
#include <unistd.h>

#include <nuttx/spi/spi.h>
#include <arch/board/board.h>

#include <drivers/drv_sensor.h>
#include <stm32_spi.h>

constexpr px4_spi_bus_t px4_spi_buses[SPI_BUS_MAX_BUS_ITEMS] = {
	initSPIBus(SPI::Bus::SPI1, {
		initSPIDevice(DRV_ACC_DEVTYPE_BMI088,  SPI::CS{GPIO_PortC, GPIO_Pin15}, SPI::DRDY{GPIO_PortB, GPIO_Pin11}),
		initSPIDevice(DRV_GYR_DEVTYPE_BMI088,  SPI::CS{GPIO_PortD, GPIO_Pin2},  SPI::DRDY{GPIO_PortB, GPIO_Pin12}),
		initSPIDevice(DRV_BARO_DEVTYPE_BMP388, SPI::CS{GPIO_PortB, GPIO_Pin4}),
	}),
};

constexpr bool external_bus_mode[] = {false};

void stm32_spiinitialize()
{
	stm32_spi1select(NULL, 0, false);
}
