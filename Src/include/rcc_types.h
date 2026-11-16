/**
 * @file    timx_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for General-Purpose Input-Output (GPIOA-GPIOH) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-08
 *
 * @note    This file provides a strict compile-time type-safe interface
 *          for hardware registers manipulation without runtime overhead.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_RCC_TYPES_H
#define PLAY32_RCC_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#define PLAY32_AHB1_PERIPHERAL    ((1UL << 30) | (1UL << 17)) // 0x40020000
#define PLAY32_BLOCK_SIZE         (1UL << 10)                 // 0x0400
#define PLAY32_RCC_BASE_POS       (14U)                       // 14 * 0x0400 = 0x3800
#define PLAY32_RCC_BASE           (PLAY32_AHB1_PERIPHERAL + (PLAY32_RCC_BASE_POS * PLAY32_BLOCK_SIZE))

typedef struct {
    volatile uint32_t CR;             /*!< Offset: 0x00 - Clock control register */
    volatile uint32_t PLLCFGR;        /*!< Offset: 0x04 - PLL configuration register */
    volatile uint32_t CFGR;           /*!< Offset: 0x08 - Clock configuration register */
    volatile uint32_t CIR;            /*!< Offset: 0x0C - Clock interrupt register */
    volatile uint32_t AHB1RSTR;       /*!< Offset: 0x10 - AHB1 peripheral reset register */
    volatile uint32_t AHB2RSTR;       /*!< Offset: 0x14 - AHB2 peripheral reset register */
    uint32_t          RESERVED0[2];   /*!< Offset: 0x18-0x1C - Reserved */
    volatile uint32_t APB1RSTR;       /*!< Offset: 0x20 - APB1 peripheral reset register */
    volatile uint32_t APB2RSTR;       /*!< Offset: 0x24 - APB2 peripheral reset register */
    uint32_t          RESERVED1[2];   /*!< Offset: 0x28-0x2C - Reserved */
    volatile uint32_t AHB1ENR;        /*!< Offset: 0x30 - AHB1 peripheral clock enable register */
    volatile uint32_t AHB2ENR;        /*!< Offset: 0x34 - AHB2 peripheral clock enable register */
    uint32_t          RESERVED2[2];   /*!< Offset: 0x38-0x3C - Reserved */
    volatile uint32_t APB1ENR;        /*!< Offset: 0x40 - APB1 peripheral clock enable register */
    volatile uint32_t APB2ENR;        /*!< Offset: 0x44 - APB2 peripheral clock enable register */
    uint32_t          RESERVED3[2];   /*!< Offset: 0x48-0x4C - Reserved */
    volatile uint32_t AHB1LPENR;      /*!< Offset: 0x50 - AHB1 peripheral clock enable in low power mode */
    volatile uint32_t AHB2LPENR;      /*!< Offset: 0x54 - AHB2 peripheral clock enable in low power mode */
    uint32_t          RESERVED4[2];   /*!< Offset: 0x58-0x5C - Reserved */
    volatile uint32_t APB1LPENR;      /*!< Offset: 0x60 - APB1 peripheral clock enable in low power mode */
    volatile uint32_t APB2LPENR;      /*!< Offset: 0x64 - APB2 peripheral clock enable in low power mode */
    uint32_t          RESERVED5[2];   /*!< Offset: 0x68-0x6C - Reserved */
    volatile uint32_t BDCR;           /*!< Offset: 0x70 - Backup domain control register */
    volatile uint32_t CSR;            /*!< Offset: 0x74 - Clock control & status register */
    uint32_t          RESERVED6[2];   /*!< Offset: 0x78-0x7C - Reserved */
    volatile uint32_t SSCGR;          /*!< Offset: 0x80 - Spread spectrum clock generation register */
    volatile uint32_t PLLI2SCFGR;     /*!< Offset: 0x84 - PLLI2S configuration register */
    uint32_t          RESERVED7;      /*!< Offset: 0x88 - Reserved */
    volatile uint32_t DCKCFGR;        /*!< Offset: 0x8C - Dedicated Clocks Configuration Register */
} PLAY32_RCC_TypeDef;

#define PLAY32_RCC ((PLAY32_RCC_TypeDef *)PLAY32_RCC_BASE)

#pragma region RCC_COMMON_ENUM
/**
 * @brief  Standard active-high control switch states for RCC peripheral and clock bits.
 * @note   Used across RCC control and enable registers where logic '1' activates
 *         a clock source, peripheral clock, or feature, and logic '0' disables it.
 */
typedef enum {
    PLAY32_RCC_SWITCH_DISABLED = 0U, /*!< Peripheral, clock, or feature disabled (0) */
    PLAY32_RCC_SWITCH_ENABLED  = 1U  /*!< Peripheral, clock, or feature enabled (1) */
} PLAY32_RCC_Switch;
/**
 * @brief  Inverted active-low control switch states for RCC configuration bits.
 * @note   Used for hardware control bits with inverted logic where logic '0'
 *         enables the feature or mode and logic '1' disables it.
 */
typedef enum {
    PLAY32_RCC_SWITCH_INVERTED_DISABLED = 1U, /*!< Feature or mode disabled (1) */
    PLAY32_RCC_SWITCH_INVERTED_ENABLED  = 0U  /*!< Feature or mode enabled (0) */
} PLAY32_RCC_InvertedSwitch;
/**
 * @brief  Hardware stabilization and readiness status flags for RCC clock sources.
 * @note   Used with read-only status bits (e.g., HSIRDY, HSERDY, PLLRDY, PLLI2SRDY)
 *         to poll whether an oscillator or PLL has locked and is safe to use.
 */
typedef enum {
    PLAY32_RCC_NOT_READY = 0U, /*!< Clock source or PLL is unstable, locked off, or disabled (0) */
    PLAY32_RCC_READY     = 1U  /*!< Clock source or PLL is stabilized, locked, and ready (1) */
} PLAY32_RCC_Ready;
#pragma endregion
#pragma region RCC_CR_REGISTER
#pragma region RCC_CR_REGISTER_POSITION
#define PLAY32_RCC_CR_HSION_POS        (0U)
#define PLAY32_RCC_CR_HSIRDY_POS       (1U)
#define PLAY32_RCC_CR_HSITRIM_POS      (3U)
#define PLAY32_RCC_CR_HSICAL_POS       (8U)
#define PLAY32_RCC_CR_HSEON_POS        (16U)
#define PLAY32_RCC_CR_HSERDY_POS       (17U)
#define PLAY32_RCC_CR_HSEBYP_POS       (18U)
#define PLAY32_RCC_CR_CSSON_POS        (19U)
#define PLAY32_RCC_CR_PLLON_POS        (24U)
#define PLAY32_RCC_CR_PLLRDY_POS       (25U)
#define PLAY32_RCC_CR_PLLI2SON_POS     (26U)
#define PLAY32_RCC_CR_PLLI2SRDY_POS    (27U)
#pragma endregion
#pragma region RCC_CR_REGISTER_MASK
#define PLAY32_RCC_CR_HSION_MSK        (1UL << PLAY32_RCC_CR_HSION_POS)
#define PLAY32_RCC_CR_HSIRDY_MSK       (1UL << PLAY32_RCC_CR_HSIRDY_POS)
#define PLAY32_RCC_CR_HSITRIM_MSK      (31UL << PLAY32_RCC_CR_HSITRIM_POS)
#define PLAY32_RCC_CR_HSICAL_MSK       (7UL << PLAY32_RCC_CR_HSICAL_POS)
#define PLAY32_RCC_CR_HSEON_MSK        (1UL << PLAY32_RCC_CR_HSEON_POS)
#define PLAY32_RCC_CR_HSERDY_MSK       (1UL << PLAY32_RCC_CR_HSERDY_POS)
#define PLAY32_RCC_CR_HSEBYP_MSK       (1UL << PLAY32_RCC_CR_HSEBYP_POS)
#define PLAY32_RCC_CR_CSSON_MSK        (1UL << PLAY32_RCC_CR_CSSON_POS)
#define PLAY32_RCC_CR_PLLON_MSK        (1UL << PLAY32_RCC_CR_PLLON_POS)
#define PLAY32_RCC_CR_PLLRDY_MSK       (1UL << PLAY32_RCC_CR_PLLRDY_POS)
#define PLAY32_RCC_CR_PLLI2SON_MSK     (1UL << PLAY32_RCC_CR_PLLI2SON_POS)
#define PLAY32_RCC_CR_PLLI2SRDY_MSK    (1UL << PLAY32_RCC_CR_PLLI2SRDY_POS)
#pragma endregion
#pragma region RCC_CR_REGISTER_ENUM
/**
 * @brief  High-Speed Internal (HSI) clock enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_CR, HSION) used to enable or disable
 *         the internal 16 MHz RC oscillator. Set automatically by hardware when
 *         leaving Stop or Standby modes, or when HSE fails if CSS is enabled.
 * @warning Cannot be disabled if HSI is selected directly or indirectly as the system clock.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_HighSpeedInternalClockEnable;
/**
 * @brief  High-Speed Internal (HSI) clock ready flag states.
 * @note   Read-only hardware status bit (bit 1 of RCC_CR) indicating whether
 *         the 16 MHz HSI oscillator is stable and ready for use.
 *         When disabling HSI, this flag remains set for 6 HSI clock cycles.
 */
typedef enum {
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_NOT_READY = 0U,
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_READY     = 1U
} PLAY32_RCC_CR_HighSpeedInternalClockReady;
/**
 * @brief  High-Speed Internal (HSI) clock trimming step values (0 to 31).
 * @note   User-programmable 5-bit offset added to the factory calibration value
 *         to form the final @ref PLAY32_RCC_CR_HighSpeedInternalClockCalibration.
 *         Each step shifts the 16 MHz HSI frequency by approximately 40 kHz.
 *         Default value at reset is @ref PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_DEFAULT (16).
 */
typedef enum {
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_16 = 0U,   /*!< ~ -640 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_15 = 1U,   /*!< ~ -600 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_14 = 2U,   /*!< ~ -560 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_13 = 3U,   /*!< ~ -520 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_12 = 4U,   /*!< ~ -480 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_11 = 5U,   /*!< ~ -440 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_10 = 6U,   /*!< ~ -400 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_9  = 7U,   /*!< ~ -360 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_8  = 8U,   /*!< ~ -320 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_7  = 9U,   /*!< ~ -280 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_6  = 10U,  /*!< ~ -240 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_5  = 11U,  /*!< ~ -200 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_4  = 12U,  /*!< ~ -160 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_3  = 13U,  /*!< ~ -120 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_2  = 14U,  /*!< ~ -80 kHz  */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_1  = 15U,  /*!< ~ -40 kHz  */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_DEFAULT  = 16U,  /*!< 0 kHz (Reset value, 16 MHz) */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_1   = 17U,  /*!< ~ +40 kHz  */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_2   = 18U,  /*!< ~ +80 kHz  */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_3   = 19U,  /*!< ~ +120 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_4   = 20U,  /*!< ~ +160 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_5   = 21U,  /*!< ~ +200 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_6   = 22U,  /*!< ~ +240 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_7   = 23U,  /*!< ~ +280 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_8   = 24U,  /*!< ~ +320 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_9   = 25U,  /*!< ~ +360 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_10  = 26U,  /*!< ~ +400 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_11  = 27U,  /*!< ~ +440 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_12  = 28U,  /*!< ~ +480 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_13  = 29U,  /*!< ~ +520 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_14  = 30U,  /*!< ~ +560 kHz */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_15  = 31U   /*!< ~ +600 kHz */
} PLAY32_RCC_CR_HighSpeedInternalClockTrim;
/**
 * @brief  High-Speed Internal (HSI) clock calibration value type (0x00 to 0xFF).
 * @note   Read-only 8-bit hardware value representing the actual sum of the
 *         factory calibration and the user-defined @ref PLAY32_RCC_CR_HighSpeedInternalClockTrim
 *         value. Automatically updated by hardware upon trimming changes.
 */
typedef uint8_t PLAY32_RCC_CR_HighSpeedInternalClockCalibration;
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_HighSpeedExternalClockEnable;
/**
 * @brief  High-Speed External (HSE) clock ready flag states.
 * @note   Read-only hardware status bit (bit 17 of RCC_CR) indicating whether
 *         the external crystal/ceramic resonator or external clock source is stable.
 *         When disabling HSE, this flag remains set for 6 HSE clock cycles.
 */
typedef PLAY32_RCC_Ready PLAY32_RCC_CR_HighSpeedExternalClockReady;
/**
 * @brief  High-Speed External (HSE) clock bypass mode states.
 * @note   Read/Write control bit (bit 18 of RCC_CR) used to bypass the internal
 *         oscillator driver with an external clock source (e.g., an active oscillator
 *         or clock signal fed directly into the OSC_IN pin).
 * @warning This bit can only be modified when the HSE oscillator is disabled
 *          (@ref PLAY32_RCC_CR_HighSpeedExternalClockEnable).
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_HighSpeedExternalClockBypass;
/**
 * @brief  Clock Security System (CSS) enable state type.
 * @note   Read/Write control bit (bit 19 of RCC_CR) used to enable or disable the
 *         hardware clock failure detector on the High-Speed External (HSE) oscillator.
 *         When enabled, if an HSE clock failure is detected, the system clock is
 *         automatically switched to HSI, the HSE oscillator is disabled, and an NMI
 *         (Non-Maskable Interrupt) is generated.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_ClockSecuritySystemEnable;
/**
 * @brief  Main Phase-Locked Loop (PLL) enable state type.
 * @note   Read/Write control bit (bit 24 of RCC_CR, PLLON) used to enable or disable
 *         the main system PLL. Cleared automatically by hardware when entering Stop
 *         or Standby modes.
 * @warning Cannot be disabled if the PLL clock is currently selected as the system clock.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_PhaseLockedLoopEnable;
/**
 * @brief  Main Phase-Locked Loop (PLL) clock ready flag type.
 * @note   Read-only hardware status bit (bit 25 of RCC_CR, PLLRDY) set by hardware
 *         to indicate that the main PLL is locked and stable for use.
 * @see    PLAY32_RCC_Ready
 */
typedef PLAY32_RCC_Ready PLAY32_RCC_CR_PhaseLockedLoopReady;
/**
 * @brief  Audio Phase-Locked Loop (PLLI2S) enable state type.
 * @note   Read/Write control bit (bit 26 of RCC_CR, PLLI2SON) used to enable or disable
 *         the dedicated I2S clock multiplier. Cleared automatically by hardware when
 *         entering Stop or Standby modes.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_PhaseLockedLoopI2SEnable;
/**
 * @brief  Audio Phase-Locked Loop (PLLI2S) clock ready flag type.
 * @note   Read-only hardware status bit (bit 27 of RCC_CR, PLLI2SRDY) set by hardware
 *         to indicate that the dedicated PLLI2S clock generator is locked and stable.
 * @see    PLAY32_RCC_Ready
 */
typedef PLAY32_RCC_Ready PLAY32_RCC_CR_PhaseLockedLoopI2SReady;
#pragma endregion

#pragma region RCC_PLLCFGR_REGISTER
#pragma region RCC_PLLCFGR_REGISTER_POSITION
#define PLAY32_RCC_PLLCFGR_PLLM_POS     (0U)
#define PLAY32_RCC_PLLCFGR_PLLN_POS       (6U)
#define PLAY32_RCC_PLLCFGR_PLLP_POS      (16U)
#define PLAY32_RCC_PLLCFGR_PLLSRC_POS     (22U)
#define PLAY32_RCC_PLLCFGR_PLLQ0_POS      (24U)
#define PLAY32_RCC_PLLCFGR_PLLQ1_POS      (25U)
#define PLAY32_RCC_PLLCFGR_PLLQ2_POS      (26U)
#define PLAY32_RCC_PLLCFGR_PLLQ3_POS      (27U)
#pragma endregion
#pragma region RCC_PLLCFGR_REGISTER_MASK
#define PLAY32_RCC_PLLCFGR_PLLM_MSK       (63UL << PLAY32_RCC_PLLCFGR_PLLM_POS)
#define PLAY32_RCC_PLLCFGR_PLLN_MSK       (511UL << PLAY32_RCC_PLLCFGR_PLLN_POS)
#define PLAY32_RCC_PLLCFGR_PLLP_MSK       (3UL << PLAY32_RCC_PLLCFGR_PLLP_POS)
#define PLAY32_RCC_PLLCFGR_PLLSRC_MSK     (1UL << PLAY32_RCC_PLLCFGR_PLLSRC_POS)
#define PLAY32_RCC_PLLCFGR_PLLQ0_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ0_POS)
#define PLAY32_RCC_PLLCFGR_PLLQ1_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ1_POS)
#define PLAY32_RCC_PLLCFGR_PLLQ2_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ2_POS)
#define PLAY32_RCC_PLLCFGR_PLLQ3_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ3_POS)
#pragma endregion
#pragma endregion
#pragma region RCC_PLLCFGR_REGISTER_VALUE
typedef uint8_t PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainDivider;
typedef uint16_t PLAY32_RCC_PLLCFGR_PhaseLockedLoopNumberMultiplicator;
/** TODO: implement rest of PPLCFGR reg **/
#pragma endregion

#pragma region RCC_CIR_REGISTER
/** TODO: implement CIR reg **/
#pragma endregion

#pragma region RCC_AHB1RSTR_REGISTER
/** TODO: implement AHB1RSTR reg **/
#pragma endregion

#pragma region RCC_AHB2RSTR_REGISTER
/** TODO: implement AHB2RSTR reg **/
#pragma endregion

#pragma region RCC_APB1RSTR_REGISTER
/** TODO: implement AHB1RSTR reg **/
#pragma endregion

#pragma region RCC_APB2RSTR_REGISTER
/** TODO: implement AHB2RSTR reg **/
#pragma endregion

#pragma region RCC_AHB1ENR_REGISTER
#pragma region RCC_AHB1ENR_REGISTER_POSITION
#define PLAY32_RCC_AHB1ENR_GPIOAEN_POS     (0U)
#define PLAY32_RCC_AHB1ENR_GPIOBEN_POS     (1U)
#define PLAY32_RCC_AHB1ENR_GPIOCEN_POS     (2U)
#define PLAY32_RCC_AHB1ENR_GPIODEN_POS     (3U)
#define PLAY32_RCC_AHB1ENR_GPIOEEN_POS     (4U)
#define PLAY32_RCC_AHB1ENR_GPIOHEN_POS     (7U)
#define PLAY32_RCC_AHB1ENR_CRCEN_POS       (12U)
#define PLAY32_RCC_AHB1ENR_DMA1EN_POS      (21U)
#define PLAY32_RCC_AHB1ENR_DMA2EN_POS      (22U)
#pragma endregion
#pragma region RCC_AHB1ENR_REGISTER_MASK
#define PLAY32_RCC_AHB1ENR_GPIOAEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOAEN_POS)
#define PLAY32_RCC_AHB1ENR_GPIOBEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOBEN_POS)
#define PLAY32_RCC_AHB1ENR_GPIOCEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOCEN_POS)
#define PLAY32_RCC_AHB1ENR_GPIODEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIODEN_POS)
#define PLAY32_RCC_AHB1ENR_GPIOEEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOEEN_POS)
#define PLAY32_RCC_AHB1ENR_GPIOHEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOHEN_POS)
#define PLAY32_RCC_AHB1ENR_CRCEN_MSK       (1UL << PLAY32_RCC_AHB1ENR_CRCEN_POS)
#define PLAY32_RCC_AHB1ENR_DMA1EN_MSK      (1UL << PLAY32_RCC_AHB1ENR_DMA1EN_POS)
#define PLAY32_RCC_AHB1ENR_DMA2EN_MSK      (1UL << PLAY32_RCC_AHB1ENR_DMA2EN_POS)
#pragma endregion
#pragma region RCC_AHB1ENR_REGISTER_ENUM
/**
 * @brief  IO port A clock enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_AHB1ENR, GPIOAEN) used to enable or disable
 *         the AHB1 bus clock for GPIOA.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOA registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIOAEnable;
/**
 * @brief  IO port B clock enable state type.
 * @note   Read/Write control bit (bit 1 of RCC_AHB1ENR, GPIOBEN) used to enable or disable
 *         the AHB1 bus clock for GPIOB.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOB registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIOBEnable;
/**
 * @brief  IO port C clock enable state type.
 * @note   Read/Write control bit (bit 2 of RCC_AHB1ENR, GPIOCEN) used to enable or disable
 *         the AHB1 bus clock for GPIOC.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOC registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIOCEnable;
/**
 * @brief  IO port D clock enable state type.
 * @note   Read/Write control bit (bit 3 of RCC_AHB1ENR, GPIODEN) used to enable or disable
 *         the AHB1 bus clock for GPIOD.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOD registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIODEnable;
/**
 * @brief  IO port E clock enable state type.
 * @note   Read/Write control bit (bit 4 of RCC_AHB1ENR, GPIOEEN) used to enable or disable
 *         the AHB1 bus clock for GPIOE.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOE registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIOEEnable;
/**
 * @brief  IO port H clock enable state type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB1ENR, GPIOHEN) used to enable or disable
 *         the AHB1 bus clock for GPIOH.
 * @warning A 2-cycle AHB1 bus delay (or dummy read of RCC_AHB1ENR) is required after enabling
 *          before accessing any GPIOH registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_GPIOHEnable;
/**
 * @brief  CRC calculation unit clock enable state type.
 * @note   Read/Write control bit (bit 12 of RCC_AHB1ENR, CRCEN) used to enable or disable
 *         the AHB1 bus clock for the hardware Cyclic Redundancy Check unit.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_CyclicRedundancyCheckEnable;
/**
 * @brief  DMA1 controller clock enable state type.
 * @note   Read/Write control bit (bit 21 of RCC_AHB1ENR, DMA1EN) used to enable or disable
 *         the AHB1 bus clock for the DMA1 controller.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_DirectMemoryAccess1Enable;
/**
 * @brief  DMA2 controller clock enable state type.
 * @note   Read/Write control bit (bit 22 of RCC_AHB1ENR, DMA2EN) used to enable or disable
 *         the AHB1 bus clock for the DMA2 controller.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1ENR_DirectMemoryAccess2Enable;
#pragma endregion
#pragma endregion

#pragma region RCC_AHB2ENR_REGISTER
#pragma region RCC_AHB2ENR_REGISTER_POSITION
#define PLAY32_RCC_AHB2ENR_OTGFS_POS     (7U)
#pragma endregion
#pragma region RCC_AHB2ENR_REGISTER_MASK
#define PLAY32_RCC_AHB2ENR_OTGFS_MSK     (1UL << PLAY32_RCC_AHB2ENR_OTGFS_POS)
#pragma endregion
#pragma region RCC_AHB2ENR_REGISTER_ENUM
/**
 * @brief  USB OTG Full-Speed (OTG_FS) clock enable state type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB2ENR, OTGFSEN) used to enable or disable
 *         the AHB2 bus clock for the USB On-The-Go Full-Speed peripheral.
 * @warning Requires a dedicated 48 MHz clock generated by the main PLL (via PLLQ)
 *          to operate properly. A 2-cycle bus delay is required after enabling.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB2ENR_USBOneTheGoFullSpeedEnable;
#pragma endregion
#pragma endregion

#pragma region RCC_APB1ENR_REGISTER
#pragma region RCC_APB1ENR_REGISTER_POSITION
#define PLAY32_RCC_APB1ENR_TIM2EN_POS      (0U)
#define PLAY32_RCC_APB1ENR_TIM3EN_POS      (1U)
#define PLAY32_RCC_APB1ENR_TIM4EN_POS      (2U)
#define PLAY32_RCC_APB1ENR_TIM5EN_POS      (3U)
#define PLAY32_RCC_APB1ENR_WWDGEN_POS      (11U)
#define PLAY32_RCC_APB1ENR_SPI2EN_POS      (14U)
#define PLAY32_RCC_APB1ENR_SPI3EN_POS      (15U)
#define PLAY32_RCC_APB1ENR_USART2EN_POS    (17U)
#define PLAY32_RCC_APB1ENR_I2C1EN_POS      (21U)
#define PLAY32_RCC_APB1ENR_I2C2EN_POS      (22U)
#define PLAY32_RCC_APB1ENR_I2C3EN_POS      (23U)
#define PLAY32_RCC_APB1ENR_PWREN_POS       (28U)
#pragma endregion
#pragma region RCC_APB1ENR_REGISTER_MASK
#define PLAY32_RCC_APB1ENR_TIM2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM2EN_POS)
#define PLAY32_RCC_APB1ENR_TIM3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM3EN_POS)
#define PLAY32_RCC_APB1ENR_TIM4EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM4EN_POS)
#define PLAY32_RCC_APB1ENR_TIM5EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM5EN_POS)
#define PLAY32_RCC_APB1ENR_WWDGEN_MSK      (1UL << PLAY32_RCC_APB1ENR_WWDGEN_POS)
#define PLAY32_RCC_APB1ENR_SPI2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_SPI2EN_POS)
#define PLAY32_RCC_APB1ENR_SPI3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_SPI3EN_POS)
#define PLAY32_RCC_APB1ENR_USART2EN_MSK    (1UL << PLAY32_RCC_APB1ENR_USART2EN_POS)
#define PLAY32_RCC_APB1ENR_I2C1EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C1EN_POS)
#define PLAY32_RCC_APB1ENR_I2C2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C2EN_POS)
#define PLAY32_RCC_APB1ENR_I2C3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C3EN_POS)
#define PLAY32_RCC_APB1ENR_PWREN_MSK       (1UL << PLAY32_RCC_APB1ENR_PWREN_POS)
#pragma endregion
#pragma region RCC_APB1ENR_REGISTER_ENUM
/**
 * @brief  TIM2 general-purpose timer clock enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_APB1ENR, TIM2EN) used to enable or disable
 *         the APB1 bus clock for Timer 2.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_Timer2Enable;
/**
 * @brief  TIM3 general-purpose timer clock enable state type.
 * @note   Read/Write control bit (bit 1 of RCC_APB1ENR, TIM3EN) used to enable or disable
 *         the APB1 bus clock for Timer 3.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_Timer3Enable;
/**
 * @brief  TIM4 general-purpose timer clock enable state type.
 * @note   Read/Write control bit (bit 2 of RCC_APB1ENR, TIM4EN) used to enable or disable
 *         the APB1 bus clock for Timer 4.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_Timer4Enable;
/**
 * @brief  TIM5 general-purpose timer clock enable state type.
 * @note   Read/Write control bit (bit 3 of RCC_APB1ENR, TIM5EN) used to enable or disable
 *         the APB1 bus clock for Timer 5.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_Timer5Enable;
/**
 * @brief  Window Watchdog (WWDG) clock enable state type.
 * @note   Read/Write control bit (bit 11 of RCC_APB1ENR, WWDGEN) used to enable or disable
 *         the APB1 bus clock for the Window Watchdog peripheral.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_WindowWatchdogEnable;
/**
 * @brief  SPI2 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 14 of RCC_APB1ENR, SPI2EN) used to enable or disable
 *         the APB1 bus clock for Serial Peripheral Interface 2.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_SPI2Enable;
/**
 * @brief  SPI3 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 15 of RCC_APB1ENR, SPI3EN) used to enable or disable
 *         the APB1 bus clock for Serial Peripheral Interface 3.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_SPI3Enable;
/**
 * @brief  USART2 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 17 of RCC_APB1ENR, USART2EN) used to enable or disable
 *         the APB1 bus clock for Universal Synchronous/Asynchronous Receiver Transmitter 2.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_USART2Enable;
/**
 * @brief  I2C1 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 21 of RCC_APB1ENR, I2C1EN) used to enable or disable
 *         the APB1 bus clock for Inter-Integrated Circuit interface 1.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_I2C1Enable;
/**
 * @brief  I2C2 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 22 of RCC_APB1ENR, I2C2EN) used to enable or disable
 *         the APB1 bus clock for Inter-Integrated Circuit interface 2.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_I2C2Enable;
/**
 * @brief  I2C3 peripheral clock enable state type.
 * @note   Read/Write control bit (bit 23 of RCC_APB1ENR, I2C3EN) used to enable or disable
 *         the APB1 bus clock for Inter-Integrated Circuit interface 3.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_I2C3Enable;
/**
 * @brief  Power interface (PWR) clock enable state type.
 * @note   Read/Write control bit (bit 28 of RCC_APB1ENR, PWREN) used to enable or disable
 *         the APB1 bus clock for the power controller peripheral.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1ENR_PowerEnable;
#pragma endregion
#pragma endregion

#pragma endregion

#endif //PLAY32_RCC_TYPES_H
