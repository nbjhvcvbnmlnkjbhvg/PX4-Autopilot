/****************************************************************************
 *
 *   Copyright (c) 2026 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <nuttx/config.h>

#include "arm_internal.h"
#include "chip.h"

#include "nvic.h"
#include "hardware/stm32_wdg.h"
#include "hardware/stm32h7xxx_dbgmcu.h"

void watchdog_pet(void)
{
	putreg32(IWDG_KR_KEY_RELOAD, STM32_IWDG_KR);
}

void watchdog_init(void)
{
	/* Freeze the IWDG while halted under a debugger. */
	putreg32(getreg32(STM32_DBGMCU_APB4LFZ1) | DBGMCU_APB4FZ1_IIWDG1STOP, STM32_DBGMCU_APB4LFZ1);

	/* Unlock watchdog registers. */
	putreg32(IWDG_KR_KEY_ENABLE, STM32_IWDG_KR);

	/* Set the prescale value. */
	putreg32(IWDG_PR_DIV16, STM32_IWDG_PR);

	/* Set the reload value. */
	putreg32(IWDG_RLR_MAX, STM32_IWDG_RLR);

	/* Start the watchdog and immediately pet it. */
	putreg32(IWDG_KR_KEY_START, STM32_IWDG_KR);
	watchdog_pet();
}
