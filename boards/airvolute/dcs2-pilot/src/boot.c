/**
 * @file boot.c
 *
 * DCS2.Pilot STM32H743 CAN bootloader board initialization
 */

#include <px4_config.h>
#include <stdint.h>
#include "boot_config.h"
#include "board.h"

#include <debug.h>
#include <string.h>
#include <arch/board/board.h>
#include <nuttx/board.h>

__EXPORT void stm32_boardinitialize(void)
{
	/* Enable FDCAN1 clock and configure pins */
	stm32_configgpio(GPIO_CAN1_RX);
	stm32_configgpio(GPIO_CAN1_TX);
	stm32_configgpio(GPIO_CAN1_SILENT_S0);
}

void board_deinitialize(void)
{
}

uint8_t board_get_product_name(uint8_t *product_name, size_t maxlen)
{
	DEBUGASSERT(maxlen > UAVCAN_STRLEN(HW_UAVCAN_NAME));
	memcpy(product_name, HW_UAVCAN_NAME, UAVCAN_STRLEN(HW_UAVCAN_NAME));
	return UAVCAN_STRLEN(HW_UAVCAN_NAME);
}

size_t board_get_hardware_version(uavcan_HardwareVersion_t *hw_version)
{
	memset(hw_version, 0, sizeof(uavcan_HardwareVersion_t));
	hw_version->major = HW_VERSION_MAJOR;
	hw_version->minor = HW_VERSION_MINOR;
	return board_get_mfguid(*(mfguid_t *) hw_version->unique_id);
}

void board_indicate(uiindication_t indication)
{
	/* No RGB LED on DCS2.Pilot — could toggle CAN silent pin as indicator */
	(void)indication;
}
