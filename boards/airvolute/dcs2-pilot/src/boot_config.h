/**
 * @file boot_config.h
 *
 * DCS2.Pilot STM32H743 CAN bootloader configuration
 *
 * STM32H743: 2MB flash, 1MB SRAM
 * Bootloader: 128KB at 0x08000000
 * Application: 1920KB at 0x08020000
 */

#pragma once

#include "board_config.h"
#include "uavcan.h"
#include <nuttx/compiler.h>
#include <stdint.h>

#define OPT_PREFERRED_NODE_ID ANY_NODE_ID

#define OPT_TBOOT_MS                    3000
#define OPT_NODE_STATUS_RATE_MS         800
#define OPT_NODE_INFO_RATE_MS           50
#define OPT_BL_NUMBER_TIMERS            7

#define OPT_WAIT_FOR_GETNODEINFO                    0
#define OPT_WAIT_FOR_GETNODEINFO_JUMPER_GPIO_INVERT 1

#define OPT_ENABLE_WD           1

#define OPT_RESTART_TIMEOUT_MS          20000

/* 128KB reserved for bootloader on H743 (larger sectors) */
#define OPT_BOOTLOADER_SIZE_IN_K        (1024*128)

#define OPT_APPLICATION_RESERVER_IN_K    0

#define OPT_APPLICATION_IMAGE_OFFSET    OPT_BOOTLOADER_SIZE_IN_K
#define OPT_APPLICATION_IMAGE_LENGTH    (FLASH_SIZE-(OPT_BOOTLOADER_SIZE_IN_K+OPT_APPLICATION_RESERVER_IN_K))

#define FLASH_BASE              STM32_FLASH_BASE
#define FLASH_SIZE              STM32_FLASH_SIZE

#define APPLICATION_LOAD_ADDRESS (FLASH_BASE + OPT_APPLICATION_IMAGE_OFFSET)
#define APPLICATION_SIZE (FLASH_SIZE-OPT_APPLICATION_IMAGE_OFFSET)
#define APPLICATION_LAST_8BIT_ADDRRESS  ((uint8_t *)((APPLICATION_LOAD_ADDRESS+APPLICATION_SIZE)-sizeof(uint8_t)))
#define APPLICATION_LAST_32BIT_ADDRRESS ((uint32_t *)((APPLICATION_LOAD_ADDRESS+APPLICATION_SIZE)-sizeof(uint32_t)))
#define APPLICATION_LAST_64BIT_ADDRRESS ((uint64_t *)((APPLICATION_LOAD_ADDRESS+APPLICATION_SIZE)-sizeof(uint64_t)))

#define OPT_USE_YIELD
