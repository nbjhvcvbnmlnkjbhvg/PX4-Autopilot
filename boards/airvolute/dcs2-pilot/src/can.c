/**
 * @file can.c
 *
 * DCS2.Pilot CAN bus initialization
 */

#include <px4_platform_common/px4_config.h>

#include <stdbool.h>
#include <stdio.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/can/can.h>

#include <stm32_fdcan.h>
#include <arch/board/board.h>

#ifdef CONFIG_CAN

int stm32_can_initialize(void)
{
	static bool initialized = false;
	struct can_dev_s *can;
	int ret;

	if (!initialized) {
		can = stm32_fdcaninitialize(1);

		if (can == NULL) {
			canerr("ERROR: Failed to get CAN1 interface\n");
			return -ENODEV;
		}

		ret = can_register("/dev/can0", can);

		if (ret < 0) {
			canerr("ERROR: Failed to register CAN1 driver: %d\n", ret);
			return ret;
		}

		initialized = true;
	}

	return OK;
}

#endif
