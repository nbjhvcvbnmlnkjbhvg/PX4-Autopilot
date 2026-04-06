/**
 * @file board_config.h
 *
 * Airvolute DCS2.Pilot STM32H743 DroneCAN node board definitions
 *
 * Pin mapping derived from ArduPilot Airvolute-DCS2 hwdef (board ID 5200)
 * MCU: STM32H743, LQFP144, 16 MHz HSE crystal
 *
 * CAN1: PD0 (RX) / PD1 (TX), silent = PA15 (active LOW)
 * SPI1: PA5 (CLK) / PA6 (MISO) / PB5 (MOSI)
 *   BMI088 Accel CS = PC15, DRDY = PB11
 *   BMI088 Gyro  CS = PD2,  DRDY = PB12
 *   BMP390       CS = PB4
 * PWM: PE9/PE11/PE13/PE14 on TIM1 CH1-4
 */

#pragma once

#include <px4_platform_common/px4_config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/* CAN1 silent mode control — PA15, active LOW */
#define GPIO_CAN1_SILENT_S0   /* PA15 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN15)

/* No CAN termination GPIO — check hardware for built-in termination */

/* SPI1 chip selects */
#define GPIO_SPI1_CS_ACCEL    /* PC15 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTC|GPIO_PIN15)
#define GPIO_SPI1_CS_GYRO     /* PD2  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTD|GPIO_PIN2)
#define GPIO_SPI1_CS_BARO     /* PB4  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTB|GPIO_PIN4)

/* SPI1 data ready signals */
#define GPIO_SPI1_DRDY_ACCEL  /* PB11 */ (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTB|GPIO_PIN11|GPIO_EXTI)
#define GPIO_SPI1_DRDY_GYRO   /* PB12 */ (GPIO_INPUT|GPIO_FLOAT|GPIO_PORTB|GPIO_PIN12|GPIO_EXTI)

/* PWM Outputs — TIM1 CH1-4 */
#define BOARD_NUM_IO_TIMERS         1
#define DIRECT_PWM_OUTPUT_CHANNELS  4

#define GPIO_TIM1_CH1_RESET   /* PE9  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN9)
#define GPIO_TIM1_CH2_RESET   /* PE11 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN11)
#define GPIO_TIM1_CH3_RESET   /* PE13 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN13)
#define GPIO_TIM1_CH4_RESET   /* PE14 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN14)

/* Flash-based parameter storage */
#define FLASH_BASED_PARAMS

/* High-resolution timer */
#define HRT_TIMER                    5  /* use timer 5 for the HRT */
#define HRT_TIMER_CHANNEL            1  /* use capture/compare channel 1 */

#define PX4_GPIO_INIT_LIST { \
		GPIO_CAN1_SILENT_S0,          \
		GPIO_SPI1_CS_ACCEL,           \
		GPIO_SPI1_CS_GYRO,            \
		GPIO_SPI1_CS_BARO,            \
		GPIO_CAN1_TX,                 \
		GPIO_CAN1_RX,                 \
	}

__BEGIN_DECLS

#define BOARD_HAS_N_S_RGB_LED       0
#define BOARD_MAX_LEDS              0

#ifndef __ASSEMBLY__

extern void stm32_spiinitialize(void);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
