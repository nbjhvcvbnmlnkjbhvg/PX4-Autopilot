/**
 * @file init.c
 *
 * DCS2.Pilot STM32H743 board initialization for DroneCAN node firmware
 */

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <errno.h>
#include <syslog.h>

#include <nuttx/board.h>

#include <stm32.h>
#include "board_config.h"
#include <stm32_uart.h>

#include <arch/board/board.h>

#include <drivers/drv_hrt.h>
#include <drivers/drv_board_led.h>
#include <drivers/drv_watchdog.h>

#include <systemlib/px4_macros.h>

#include <px4_platform_common/init.h>
#include <px4_platform/gpio.h>

#include <px4_arch/io_timer.h>

#if defined(FLASH_BASED_PARAMS)
#  include <parameters/flashparams/flashfs.h>
#endif

__EXPORT void board_on_reset(int status)
{
	for (int i = 0; i < DIRECT_PWM_OUTPUT_CHANNELS; ++i) {
		px4_arch_configgpio(io_timer_channel_get_gpio_output(i));
	}

	if (status >= 0) {
		up_mdelay(400);
	}
}

__EXPORT void stm32_boardinitialize(void)
{
	board_on_reset(-1);

	watchdog_init();

	const uint32_t gpio[] = PX4_GPIO_INIT_LIST;
	px4_gpio_init(gpio, arraySize(gpio));

	stm32_spiinitialize();
}

__EXPORT int board_app_initialize(uintptr_t arg)
{
	px4_platform_init();

#if defined(SERIAL_HAVE_RXDMA)
	static struct hrt_call serial_dma_call;
	hrt_call_every(&serial_dma_call, 1000, 1000, (hrt_callout)stm32_serial_dma_poll, NULL);
#endif

#if defined(FLASH_BASED_PARAMS)
	/* STM32H743 flash sectors are 128KB each
	 * Sector 2: 0x08040000 (128KB) — params primary
	 * Sector 3: 0x08060000 (128KB) — params backup
	 */
	static sector_descriptor_t params_sector_map[] = {
		{2, 128 * 1024, 0x08040000},
		{3, 128 * 1024, 0x08060000},
		{0, 0, 0},
	};

	int result = parameter_flashfs_init(params_sector_map, NULL, 0);

	if (result != OK) {
		syslog(LOG_ERR, "[boot] FAILED to init params in FLASH %d\n", result);
	}

#endif

	return OK;
}
