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
/**
 * @brief  RCC peripheral and domain reset control state enumeration.
 * @note   Generic 1-bit Read/Write control type used across RCC reset registers
 *         (such as RCC_AHB1RSTR, RCC_APB1RSTR, RCC_APB2RSTR, and RCC_BDCR_BDRST)
 *         to hold a peripheral or domain in normal operation or force a hardware reset.
 * @warning When asserting @ref PLAY32_RCC_RESET, the bit is not cleared by hardware;
 *          software must explicitly write @ref PLAY32_RCC_KEEP back to release the
 *          peripheral or Backup domain from the reset state.
 * @see    PLAY32_RCC_Switch
 */
typedef enum {
    PLAY32_RCC_KEEP  = 0U, /**< Keep normal operation (do not reset the peripheral or domain). */
    PLAY32_RCC_RESET = 1U  /**< Force hardware reset of the target peripheral or domain. */
} PLAY32_RCC_Reset;
/**
 * @brief  RCC hardware status and reset flag state enumeration.
 * @note   Generic 1-bit status type used across RCC status and interrupt registers
 *         (such as RCC_CSR reset flags and RCC_CIR interrupt flags) to indicate
 *         whether a specific hardware event or reset condition has occurred.
 * @warning Most hardware flags are read-only and remain latched until cleared by writing
 *          to a dedicated clear bit (such as RMVF in RCC_CSR or the *C bits in RCC_CIR);
 *          writing @ref PLAY32_RCC_FLAG_NOT_SET directly to the status bit has no effect.
 * @see    PLAY32_RCC_Ready
 * @see    PLAY32_RCC_Switch
 */
typedef enum {
    PLAY32_RCC_FLAG_NOT_SET = 0U, /**< Flag is cleared (no event or reset condition occurred). */
    PLAY32_RCC_FLAG_SET     = 1U  /**< Flag is set (hardware event or reset condition occurred). */
} PLAY32_RCC_Flag;
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
#define PLAY32_RCC_AHB2ENR_OTGFSEN_POS     (7U)
#pragma endregion
#pragma region RCC_AHB2ENR_REGISTER_MASK
#define PLAY32_RCC_AHB2ENR_OTGFSEN_MSK     (1UL << PLAY32_RCC_AHB2ENR_OTGFSEN_POS)
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

#pragma region RCC_APB2ENR_REGISTER
#pragma region RCC_APB2ENR_REGISTER_POSITION
#define PLAY32_RCC_APB2ENR_TIM1EN_POS      (0U)
#define PLAY32_RCC_APB2ENR_USART1EN_POS    (4U)
#define PLAY32_RCC_APB2ENR_USART6EN_POS    (5U)
#define PLAY32_RCC_APB2ENR_ADC1EN_POS      (8U)
#define PLAY32_RCC_APB2ENR_SDIOEN_POS      (11U)
#define PLAY32_RCC_APB2ENR_SPI1EN_POS      (12U)
#define PLAY32_RCC_APB2ENR_SPI4EN_POS      (13U)
#define PLAY32_RCC_APB2ENR_SYSCFGEN_POS    (14U)
#define PLAY32_RCC_APB2ENR_TIM9EN_POS      (16U)
#define PLAY32_RCC_APB2ENR_TIM10EN_POS     (17U)
#define PLAY32_RCC_APB2ENR_TIM11EN_POS     (18U)
#pragma endregion
#pragma region RCC_APB2ENR_REGISTER_MASK
#define PLAY32_RCC_APB2ENR_TIM1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_TIM1EN_POS)
#define PLAY32_RCC_APB2ENR_USART1EN_MSK    (1UL << PLAY32_RCC_APB2ENR_USART1EN_POS)
#define PLAY32_RCC_APB2ENR_USART6EN_MSK    (1UL << PLAY32_RCC_APB2ENR_USART6EN_POS)
#define PLAY32_RCC_APB2ENR_ADC1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_ADC1EN_POS)
#define PLAY32_RCC_APB2ENR_SDIOEN_MSK      (1UL << PLAY32_RCC_APB2ENR_SDIOEN_POS)
#define PLAY32_RCC_APB2ENR_SPI1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_SPI1EN_POS)
#define PLAY32_RCC_APB2ENR_SPI4EN_MSK      (1UL << PLAY32_RCC_APB2ENR_SPI4EN_POS)
#define PLAY32_RCC_APB2ENR_SYSCFGEN_MSK    (1UL << PLAY32_RCC_APB2ENR_SYSCFGEN_POS)
#define PLAY32_RCC_APB2ENR_TIM9EN_MSK      (1UL << PLAY32_RCC_APB2ENR_TIM9EN_POS)
#define PLAY32_RCC_APB2ENR_TIM10EN_MSK     (1UL << PLAY32_RCC_APB2ENR_TIM10EN_POS)
#define PLAY32_RCC_APB2ENR_TIM11EN_MSK     (1UL << PLAY32_RCC_APB2ENR_TIM11EN_POS)
#pragma endregion
#pragma region RCC_APB2ENR_REGISTER_ENUM
/**
 * @brief  Advanced-control Timer 1 (TIM1) clock enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_APB2ENR, TIM1EN) used to enable or disable
 *         the APB2 bus clock for the TIM1 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing TIM1 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_Timer1Enable;
/**
 * @brief  USART1 clock enable state type.
 * @note   Read/Write control bit (bit 4 of RCC_APB2ENR, USART1EN) used to enable or disable
 *         the APB2 bus clock for the USART1 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing USART1 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_USART1Enable;
/**
 * @brief  USART6 clock enable state type.
 * @note   Read/Write control bit (bit 5 of RCC_APB2ENR, USART6EN) used to enable or disable
 *         the APB2 bus clock for the USART6 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing USART6 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_USART6Enable;
/**
 * @brief  Analog-to-Digital Converter 1 (ADC1) clock enable state type.
 * @note   Read/Write control bit (bit 8 of RCC_APB2ENR, ADC1EN) used to enable or disable
 *         the APB2 bus clock for the ADC1 peripheral.
 * @warning Ensure the ADC prescaler (ADCPRE in ADC_CCR) is configured so the ADC clock
 *          does not exceed the maximum allowed frequency (36 MHz) before enabling.
 *          A 2-cycle APB2 bus delay is required after enabling.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_AnalogDigitalConverter1Enable;
/**
 * @brief  Secure Digital Input/Output (SDIO) clock enable state type.
 * @note   Read/Write control bit (bit 11 of RCC_APB2ENR, SDIOEN) used to enable or disable
 *         the APB2 bus clock for the SDIO peripheral.
 * @warning Requires a dedicated 48 MHz clock (SDIOCLK) generated by the main PLL (via PLLQ)
 *          to operate properly. A 2-cycle APB2 bus delay is required after enabling.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_SecureDigitalInputOutputEnable;
/**
 * @brief  SPI1 clock enable state type.
 * @note   Read/Write control bit (bit 12 of RCC_APB2ENR, SPI1EN) used to enable or disable
 *         the APB2 bus clock for the SPI1 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing SPI1 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_SPI1Enable;
/**
 * @brief  SPI4 clock enable state type.
 * @note   Read/Write control bit (bit 13 of RCC_APB2ENR, SPI4EN) used to enable or disable
 *         the APB2 bus clock for the SPI4 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing SPI4 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_SPI4Enable;
/**
 * @brief  System Configuration Controller (SYSCFG) clock enable state type.
 * @note   Read/Write control bit (bit 14 of RCC_APB2ENR, SYSCFGEN) used to enable or disable
 *         the APB2 bus clock for the SYSCFG peripheral.
 * @warning Must be enabled before configuring external interrupt (EXTI) line mappings
 *          or I/O compensation cell settings. A 2-cycle APB2 bus delay is required after enabling.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_SystemConfigEnable;
/**
 * @brief  General-purpose Timer 9 (TIM9) clock enable state type.
 * @note   Read/Write control bit (bit 16 of RCC_APB2ENR, TIM9EN) used to enable or disable
 *         the APB2 bus clock for the TIM9 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing TIM9 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_Timer9Enable;
/**
 * @brief  General-purpose Timer 10 (TIM10) clock enable state type.
 * @note   Read/Write control bit (bit 17 of RCC_APB2ENR, TIM10EN) used to enable or disable
 *         the APB2 bus clock for the TIM10 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing TIM10 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_Timer10Enable;
/**
 * @brief  General-purpose Timer 11 (TIM11) clock enable state type.
 * @note   Read/Write control bit (bit 18 of RCC_APB2ENR, TIM11EN) used to enable or disable
 *         the APB2 bus clock for the TIM11 peripheral.
 * @warning A 2-cycle APB2 bus delay is required after enabling the peripheral clock
 *          before accessing TIM11 registers.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2ENR_Timer11Enable;
#pragma endregion
#pragma endregion

#pragma region RCC_AHB1LPENR_REGISTER
#pragma region RCC_AHB1LPENR_REGISTER_POSITION
#define PLAY32_RCC_AHB1LPENR_GPIOALPEN_POS     (0U)
#define PLAY32_RCC_AHB1LPENR_GPIOBLPEN_POS     (1U)
#define PLAY32_RCC_AHB1LPENR_GPIOCLPEN_POS     (2U)
#define PLAY32_RCC_AHB1LPENR_GPIODLPEN_POS     (3U)
#define PLAY32_RCC_AHB1LPENR_GPIOELPEN_POS     (4U)
#define PLAY32_RCC_AHB1LPENR_GPIOHLPEN_POS     (7U)
#define PLAY32_RCC_AHB1LPENR_CRCLPEN_POS       (12U)
#define PLAY32_RCC_AHB1LPENR_DMA1LPEN_POS      (21U)
#define PLAY32_RCC_AHB1LPENR_DMA2LPEN_POS      (22U)
#pragma endregion
#pragma region RCC_AHB1LPENR_REGISTER_MASK
#define PLAY32_RCC_AHB1LPENR_GPIOALPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOALPEN_POS)
#define PLAY32_RCC_AHB1LPENR_GPIOBLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOBLPEN_POS)
#define PLAY32_RCC_AHB1LPENR_GPIOCLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOCLPEN_POS)
#define PLAY32_RCC_AHB1LPENR_GPIODLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIODLPEN_POS)
#define PLAY32_RCC_AHB1LPENR_GPIOELPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOELPEN_POS)
#define PLAY32_RCC_AHB1LPENR_GPIOHLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOHLPEN_POS)
#define PLAY32_RCC_AHB1LPENR_CRCLPEN_MSK       (1UL << PLAY32_RCC_AHB1LPENR_CRCLPEN_POS)
#define PLAY32_RCC_AHB1LPENR_DMA1LPEN_MSK      (1UL << PLAY32_RCC_AHB1LPENR_DMA1LPEN_POS)
#define PLAY32_RCC_AHB1LPENR_DMA2LPEN_MSK      (1UL << PLAY32_RCC_AHB1LPENR_DMA2LPEN_POS)
#pragma endregion
#pragma region RCC_AHB1LPENR_REGISTER_ENUM
/**
 * @brief  IO port A (GPIOA) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 0 of RCC_AHB1LPENR, GPIOALPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOA peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOA pin state updates and
 *          wake-up interrupt detection through GPIOA lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIOALowPowerEnable;
/**
 * @brief  IO port B (GPIOB) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 1 of RCC_AHB1LPENR, GPIOBLPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOB peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOB pin state updates and
 *          wake-up interrupt detection through GPIOB lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIOBLowPowerEnable;
/**
 * @brief  IO port C (GPIOC) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 2 of RCC_AHB1LPENR, GPIOCLPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOC peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOC pin state updates and
 *          wake-up interrupt detection through GPIOC lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIOCLowPowerEnable;
/**
 * @brief  IO port D (GPIOD) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 3 of RCC_AHB1LPENR, GPIODLPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOD peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOD pin state updates and
 *          wake-up interrupt detection through GPIOD lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIODLowPowerEnable;
/**
 * @brief  IO port E (GPIOE) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 4 of RCC_AHB1LPENR, GPIOELPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOE peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOE pin state updates and
 *          wake-up interrupt detection through GPIOE lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIOELowPowerEnable;
/**
 * @brief  IO port H (GPIOH) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB1LPENR, GPIOHLPEN) used to enable or disable
 *         the AHB1 bus clock for the GPIOH peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode prevents GPIOH pin state updates and
 *          wake-up interrupt detection through GPIOH lines.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_GPIOHLowPowerEnable;
/**
 * @brief  CRC calculation unit clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 12 of RCC_AHB1LPENR, CRCLPEN) used to enable or disable
 *         the AHB1 bus clock for the CRC peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if active DMA-to-CRC memory transfers are scheduled to run
 *          while the CPU core is in Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_CyclicRedundancyCheckLowPowerEnable;
/**
 * @brief  DMA1 controller clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 21 of RCC_AHB1LPENR, DMA1LPEN) used to enable or disable
 *         the AHB1 bus clock for the DMA1 controller when the CPU enters Sleep mode.
 * @warning Disabling this bit halts all ongoing DMA1 stream transfers and prevents DMA1
 *          transfer-complete interrupts from waking the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_DirectMemoryAccess1LowPowerEnable;
/**
 * @brief  DMA2 controller clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 22 of RCC_AHB1LPENR, DMA2LPEN) used to enable or disable
 *         the AHB1 bus clock for the DMA2 controller when the CPU enters Sleep mode.
 * @warning Disabling this bit halts all ongoing DMA2 stream transfers and prevents DMA2
 *          transfer-complete interrupts from waking the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB1LPENR_DirectMemoryAccess2LowPowerEnable;
#pragma endregion
#pragma endregion

#pragma region RCC_AHB2LPENR_REGISTER
#pragma region RCC_AHB2LPENR_REGISTER_POSITION
#define PLAY32_RCC_AHB2LPENR_OTGFSLPEN_POS     (7U)
#pragma endregion
#pragma region RCC_AHB2LPENR_REGISTER_MASK
#define PLAY32_RCC_AHB2LPENR_OTGFSLPEN_MSK     (1UL << PLAY32_RCC_AHB2LPENR_OTGFSLPEN_POS)
#pragma endregion
#pragma region RCC_AHB2LPENR_REGISTER_ENUM
/**
 * @brief  USB OTG Full-Speed (OTG_FS) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB2LPENR, OTGFSLPEN) used to enable or disable
 *         the AHB2 bus clock for the USB On-The-Go Full-Speed peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if USB remote wake-up detection or ongoing USB transfers
 *          are required while the CPU is in Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB2LPENR_USBOneTheGoFullSpeedLowPowerEnable;
#pragma endregion
#pragma endregion

#pragma region RCC_APB1LPENR_REGISTER
#pragma region RCC_APB1LPENR_REGISTER_POSITION
#define PLAY32_RCC_APB1LPENR_TIM2LPEN_POS      (0U)
#define PLAY32_RCC_APB1LPENR_TIM3LPEN_POS      (1U)
#define PLAY32_RCC_APB1LPENR_TIM4LPEN_POS      (2U)
#define PLAY32_RCC_APB1LPENR_TIM5LPEN_POS      (3U)
#define PLAY32_RCC_APB1LPENR_WWDGLPEN_POS      (11U)
#define PLAY32_RCC_APB1LPENR_SPI2LPEN_POS      (14U)
#define PLAY32_RCC_APB1LPENR_SPI3LPEN_POS      (15U)
#define PLAY32_RCC_APB1LPENR_USART2LPEN_POS    (17U)
#define PLAY32_RCC_APB1LPENR_I2C1LPEN_POS      (21U)
#define PLAY32_RCC_APB1LPENR_I2C2LPEN_POS      (22U)
#define PLAY32_RCC_APB1LPENR_I2C3LPEN_POS      (23U)
#define PLAY32_RCC_APB1LPENR_PWRLPEN_POS       (28U)
#pragma endregion
#pragma region RCC_APB1LPENR_REGISTER_MASK
#define PLAY32_RCC_APB1LPENR_TIM2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM2LPEN_POS)
#define PLAY32_RCC_APB1LPENR_TIM3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM3LPEN_POS)
#define PLAY32_RCC_APB1LPENR_TIM4LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM4LPEN_POS)
#define PLAY32_RCC_APB1LPENR_TIM5LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM5LPEN_POS)
#define PLAY32_RCC_APB1LPENR_WWDGLPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_WWDGLPEN_POS)
#define PLAY32_RCC_APB1LPENR_SPI2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_SPI2LPEN_POS)
#define PLAY32_RCC_APB1LPENR_SPI3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_SPI3LPEN_POS)
#define PLAY32_RCC_APB1LPENR_USART2LPEN_MSK    (1UL << PLAY32_RCC_APB1LPENR_USART2LPEN_POS)
#define PLAY32_RCC_APB1LPENR_I2C1LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C1LPEN_POS)
#define PLAY32_RCC_APB1LPENR_I2C2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C2LPEN_POS)
#define PLAY32_RCC_APB1LPENR_I2C3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C3LPEN_POS)
#define PLAY32_RCC_APB1LPENR_PWRLPEN_MSK       (1UL << PLAY32_RCC_APB1LPENR_PWRLPEN_POS)
#pragma endregion
#pragma region RCC_APB1LPENR_REGISTER_ENUM
/**
 * @brief  General-purpose Timer 2 (TIM2) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 0 of RCC_APB1LPENR, TIM2LPEN) used to enable or disable
 *         the APB1 bus clock for the TIM2 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM2 counting and prevents timer
 *          interrupts or DMA requests from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_Timer2LowPowerEnable;
/**
 * @brief  General-purpose Timer 3 (TIM3) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 1 of RCC_APB1LPENR, TIM3LPEN) used to enable or disable
 *         the APB1 bus clock for the TIM3 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM3 counting and prevents timer
 *          interrupts or DMA requests from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_Timer3LowPowerEnable;
/**
 * @brief  General-purpose Timer 4 (TIM4) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 2 of RCC_APB1LPENR, TIM4LPEN) used to enable or disable
 *         the APB1 bus clock for the TIM4 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM4 counting and prevents timer
 *          interrupts or DMA requests from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_Timer4LowPowerEnable;
/**
 * @brief  General-purpose Timer 5 (TIM5) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 3 of RCC_APB1LPENR, TIM5LPEN) used to enable or disable
 *         the APB1 bus clock for the TIM5 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM5 counting and prevents timer
 *          interrupts or DMA requests from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_Timer5LowPowerEnable;
/**
 * @brief  Window Watchdog (WWDG) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 11 of RCC_APB1LPENR, WWDGLPEN) used to enable or disable
 *         the APB1 bus clock for the WWDG peripheral when the CPU enters Sleep mode.
 * @warning If the WWDG is active and this bit remains enabled during Sleep mode, the counter
 *          continues decrementing and will trigger a system reset unless the CPU wakes up
 *          to refresh it before timeout.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_WindowWatchdogLowPowerEnable;
/**
 * @brief  SPI2 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 14 of RCC_APB1LPENR, SPI2LPEN) used to enable or disable
 *         the APB1 bus clock for the SPI2 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if SPI2 slave reception or DMA-driven transfers are expected
 *          to continue or wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_SPI2LowPowerEnable;
/**
 * @brief  SPI3 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 15 of RCC_APB1LPENR, SPI3LPEN) used to enable or disable
 *         the APB1 bus clock for the SPI3 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if SPI3 slave reception or DMA-driven transfers are expected
 *          to continue or wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_SPI3LowPowerEnable;
/**
 * @brief  USART2 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 17 of RCC_APB1LPENR, USART2LPEN) used to enable or disable
 *         the APB1 bus clock for the USART2 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if incoming UART data or RXNE/IDLE interrupts are used
 *          to wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_USART2LowPowerEnable;
/**
 * @brief  I2C1 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 21 of RCC_APB1LPENR, I2C1LPEN) used to enable or disable
 *         the APB1 bus clock for the I2C1 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if I2C1 address-match wake-up or ongoing DMA transfers
 *          are required during Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_I2C1LowPowerEnable;
/**
 * @brief  I2C2 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 22 of RCC_APB1LPENR, I2C2LPEN) used to enable or disable
 *         the APB1 bus clock for the I2C2 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if I2C2 address-match wake-up or ongoing DMA transfers
 *          are required during Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_I2C2LowPowerEnable;
/**
 * @brief  I2C3 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 23 of RCC_APB1LPENR, I2C3LPEN) used to enable or disable
 *         the APB1 bus clock for the I2C3 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if I2C3 address-match wake-up or ongoing DMA transfers
 *          are required during Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_I2C3LowPowerEnable;
/**
 * @brief  Power interface (PWR) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 28 of RCC_APB1LPENR, PWRLPEN) used to enable or disable
 *         the APB1 bus clock for the Power controller when the CPU enters Sleep mode.
 * @warning Keep enabled if Programmable Voltage Detector (PVD) interrupts or power
 *          regulator state transitions must remain active during Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB1LPENR_PowerLowPowerEnable;
#pragma endregion
#pragma endregion

#pragma region RCC_APB2LPENR_REGISTER
#pragma region RCC_APB2LPENR_REGISTER_POSITION
#define PLAY32_RCC_APB2LPENR_TIM1LPEN_POS      (0U)
#define PLAY32_RCC_APB2LPENR_USART1LPEN_POS    (4U)
#define PLAY32_RCC_APB2LPENR_USART6LPEN_POS    (5U)
#define PLAY32_RCC_APB2LPENR_ADC1LPEN_POS      (8U)
#define PLAY32_RCC_APB2LPENR_SDIOLPEN_POS      (11U)
#define PLAY32_RCC_APB2LPENR_SPI1LPEN_POS      (12U)
#define PLAY32_RCC_APB2LPENR_SPI4LPEN_POS      (13U)
#define PLAY32_RCC_APB2LPENR_SYSCFGLPEN_POS    (14U)
#define PLAY32_RCC_APB2LPENR_TIM9LPEN_POS      (16U)
#define PLAY32_RCC_APB2LPENR_TIM10LPEN_POS     (17U)
#define PLAY32_RCC_APB2LPENR_TIM11LPEN_POS     (18U)
#pragma endregion
#pragma region RCC_APB2LPENR_REGISTER_MASK
#define PLAY32_RCC_APB2LPENR_TIM1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_TIM1LPEN_POS)
#define PLAY32_RCC_APB2LPENR_USART1LPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_USART1LPEN_POS)
#define PLAY32_RCC_APB2LPENR_USART6LPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_USART6LPEN_POS)
#define PLAY32_RCC_APB2LPENR_ADC1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_ADC1LPEN_POS)
#define PLAY32_RCC_APB2LPENR_SDIOLPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SDIOLPEN_POS)
#define PLAY32_RCC_APB2LPENR_SPI1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SPI1LPEN_POS)
#define PLAY32_RCC_APB2LPENR_SPI4LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SPI4LPEN_POS)
#define PLAY32_RCC_APB2LPENR_SYSCFGLPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_SYSCFGLPEN_POS)
#define PLAY32_RCC_APB2LPENR_TIM9LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_TIM9LPEN_POS)
#define PLAY32_RCC_APB2LPENR_TIM10LPEN_MSK     (1UL << PLAY32_RCC_APB2LPENR_TIM10LPEN_POS)
#define PLAY32_RCC_APB2LPENR_TIM11LPEN_MSK     (1UL << PLAY32_RCC_APB2LPENR_TIM11LPEN_POS)
#pragma endregion
#pragma region RCC_APB2LPENR_REGISTER_ENUM
/**
 * @brief  Advanced-control Timer 1 (TIM1) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 0 of RCC_APB2LPENR, TIM1LPEN) used to enable or disable
 *         the APB2 bus clock for the TIM1 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM1 counting and prevents timer
 *          interrupts or DMA requests from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_Timer1LowPowerEnable;
/**
 * @brief  USART1 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 4 of RCC_APB2LPENR, USART1LPEN) used to enable or disable
 *         the APB2 bus clock for the USART1 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if incoming UART data or RXNE/IDLE interrupts are used
 *          to wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_USART1LowPowerEnable;
/**
 * @brief  USART6 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 5 of RCC_APB2LPENR, USART6LPEN) used to enable or disable
 *         the APB2 bus clock for the USART6 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if incoming UART data or RXNE/IDLE interrupts are used
 *          to wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_USART6LowPowerEnable;
/**
 * @brief  Analog-to-Digital Converter 1 (ADC1) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 8 of RCC_APB2LPENR, ADC1LPEN) used to enable or disable
 *         the APB2 bus clock for the ADC1 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if timer-triggered ADC conversions or DMA transfers are
 *          scheduled to run while the CPU core is in Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_AnalogDigitalConverter1LowPowerEnable;
/**
 * @brief  Secure Digital Input/Output (SDIO) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 11 of RCC_APB2LPENR, SDIOLPEN) used to enable or disable
 *         the APB2 bus clock for the SDIO peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if active SDIO data transfers or SDIO card interrupts are
 *          expected to continue or wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_SecureDigitalInputOutputLowPowerEnable;
/**
 * @brief  SPI1 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 12 of RCC_APB2LPENR, SPI1LPEN) used to enable or disable
 *         the APB2 bus clock for the SPI1 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if SPI1 slave reception or DMA-driven transfers are expected
 *          to continue or wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_SPI1LowPowerEnable;
/**
 * @brief  SPI4 clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 13 of RCC_APB2LPENR, SPI4LPEN) used to enable or disable
 *         the APB2 bus clock for the SPI4 peripheral when the CPU enters Sleep mode.
 * @warning Must remain enabled if SPI4 slave reception or DMA-driven transfers are expected
 *          to continue or wake the CPU from Sleep mode.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_SPI4LowPowerEnable;
/**
 * @brief  System Configuration Controller (SYSCFG) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 14 of RCC_APB2LPENR, SYSCFGLPEN) used to enable or disable
 *         the APB2 bus clock for the SYSCFG peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode may interfere with external interrupt (EXTI)
 *          routing or compensation cell behavior depending on system power configuration.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_SystemConfigLowPowerEnable;
/**
 * @brief  General-purpose Timer 9 (TIM9) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 16 of RCC_APB2LPENR, TIM9LPEN) used to enable or disable
 *         the APB2 bus clock for the TIM9 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM9 counting and prevents timer
 *          interrupts from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_Timer9LowPowerEnable;
/**
 * @brief  General-purpose Timer 10 (TIM10) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 17 of RCC_APB2LPENR, TIM10LPEN) used to enable or disable
 *         the APB2 bus clock for the TIM10 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM10 counting and prevents timer
 *          interrupts from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_Timer10LowPowerEnable;
/**
 * @brief  General-purpose Timer 11 (TIM11) clock enable during Sleep mode state type.
 * @note   Read/Write control bit (bit 18 of RCC_APB2LPENR, TIM11LPEN) used to enable or disable
 *         the APB2 bus clock for the TIM11 peripheral when the CPU enters Sleep mode.
 * @warning Disabling this clock in Sleep mode stops TIM11 counting and prevents timer
 *          interrupts from waking the CPU.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_APB2LPENR_Timer11LowPowerEnable;
#pragma endregion
#pragma endregion

#pragma region RCC_BDCR_REGISTER
#pragma region RCC_BDCR_REGISTER_POSITION
#define PLAY32_RCC_BDCR_LSEON_POS     (0U)
#define PLAY32_RCC_BDCR_LSERDY_POS    (1U)
#define PLAY32_RCC_BDCR_LSEBYP_POS    (2U)
#define PLAY32_RCC_BDCR_RTCSEL_POS    (8U)
#define PLAY32_RCC_BDCR_RTCEN_POS     (15U)
#define PLAY32_RCC_BDCR_BDRST_POS     (16U)
#pragma endregion
#pragma region RCC_BDCR_REGISTER_MASK
#define PLAY32_RCC_BDCR_LSEON_MSK     (1UL << PLAY32_RCC_BDCR_LSEON_POS)
#define PLAY32_RCC_BDCR_LSERDY_MSK    (1UL << PLAY32_RCC_BDCR_LSERDY_POS)
#define PLAY32_RCC_BDCR_LSEBYP_MSK    (1UL << PLAY32_RCC_BDCR_LSEBYP_POS)
#define PLAY32_RCC_BDCR_RTCSEL_MSK    (1UL << PLAY32_RCC_BDCR_RTCSEL_POS)
#define PLAY32_RCC_BDCR_RTCEN_MSK     (1UL << PLAY32_RCC_BDCR_RTCEN_POS)
#define PLAY32_RCC_BDCR_BDRST_MSK     (1UL << PLAY32_RCC_BDCR_BDRST_POS)
#pragma endregion
#pragma region RCC_BDCR_REGISTER_ENUM
/**
 * @brief  External Low-Speed Oscillator (LSE) enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_BDCR, LSEON) used to enable or disable
 *         the external 32.768 kHz crystal oscillator.
 * @warning Located in the Backup domain; write access requires enabling the PWR clock
 *          and setting the DBP bit in PWR_CR first.
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorReady
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorEnable;
/**
 * @brief  External Low-Speed Oscillator (LSE) clock ready flag type.
 * @note   Read-only status bit (bit 1 of RCC_BDCR, LSERDY) set by hardware to indicate
 *         that the external 32.768 kHz LSE oscillator is stable and ready for use.
 * @warning Do not select LSE as the RTC clock source until this flag reads ready.
 *          After disabling LSE, this bit goes low after 6 LSE clock cycles.
 * @see    PLAY32_RCC_Ready
 * @see    PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorEnable
 */
typedef PLAY32_RCC_Ready PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorReady;
/**
 * @brief  External Low-Speed Oscillator (LSE) bypass mode enumeration.
 * @note   Read/Write control bit (bit 2 of RCC_BDCR, LSEBYP) used to bypass the internal
 *         crystal oscillator driver with an external clock source on the OSC32_IN pin.
 * @warning This bit can only be written while the LSE oscillator is disabled (LSEON = 0)
 *          and Backup domain write protection (PWR_CR.DBP) is unlocked.
 * @see    PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorEnable
 */
typedef enum {
    PLAY32_RCC_BDCR_EXTERNAL_LOW_SPEED_OSCILLATOR_BYPASS_NOT_BYPASSED = 0U, /**< LSE oscillator not bypassed (external 32.768 kHz crystal used). */
    PLAY32_RCC_BDCR_EXTERNAL_LOW_SPEED_OSCILLATOR_BYPASS_BYPASSED     = 1U  /**< LSE oscillator bypassed with an external clock source. */
} PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorBypass;
/**
 * @brief  Real-Time Clock (RTC) clock source selection enumeration.
 * @note   Read/Write 2-bit control field (bits 9:8 of RCC_BDCR, RTCSEL[1:0]) used to select
 *         the clock source fed to the RTC peripheral.
 * @warning Once the RTC clock source has been selected, it cannot be changed anymore unless
 *          the Backup domain is reset via @ref PLAY32_RCC_BDCR_BackupDomainSoftwareReset.
 *          Requires PWR_CR.DBP to be set before writing.
 * @see    PLAY32_RCC_BDCR_RealTimeClockEnable
 * @see    PLAY32_RCC_BDCR_BackupDomainSoftwareReset
 */
typedef enum {
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_LSE = 0U, /**< LSE oscillator clock used as the RTC clock. */
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_LSI = 1U, /**< LSI RC oscillator clock used as the RTC clock. */
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_HSE = 2U  /**< HSE oscillator clock divided by a programmable prescaler (RTCPRE) used as the RTC clock. */
} PLAY32_RCC_BDCR_RealTimeClockSourceSelection;
/**
 * @brief  Real-Time Clock (RTC) clock enable state type.
 * @note   Read/Write control bit (bit 15 of RCC_BDCR, RTCEN) used to enable or disable
 *         the clock supply to the RTC peripheral.
 * @warning Located in the Backup domain; requires PWR_CR.DBP to be set before writing.
 *          Configure @ref PLAY32_RCC_BDCR_RealTimeClockSourceSelection before enabling.
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_BDCR_RealTimeClockSourceSelection
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_BDCR_RealTimeClockEnable;
/**
 * @brief  Backup domain software reset control state type.
 * @note   Read/Write control bit (bit 16 of RCC_BDCR, BDRST) used to reset the entire
 *         Backup domain (including RTC registers and RCC_BDCR).
 * @warning Writing @ref PLAY32_RCC_RESET resets all Backup domain registers and is not
 *          cleared automatically; software must write @ref PLAY32_RCC_KEEP afterward.
 *          Requires PWR_CR.DBP to be set before writing.
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_BDCR_BackupDomainSoftwareReset;

#pragma endregion
#pragma endregion

#pragma region RCC_CSR_REGISTER
#pragma region RCC_CSR_REGISTER_POSITION
#define PLAY32_RCC_CSR_LSION_POS      (0U)
#define PLAY32_RCC_CSR_LSIRDY_POS     (1U)
#define PLAY32_RCC_CSR_RMVF_POS        (24U)
#define PLAY32_RCC_CSR_BORRSTF_POS     (25U)
#define PLAY32_RCC_CSR_PINRSTF_POS     (26U)
#define PLAY32_RCC_CSR_PORRSTF_POS     (27U)
#define PLAY32_RCC_CSR_SFTRSTF_POS     (28U)
#define PLAY32_RCC_CSR_IWDGRSTF_POS    (29U)
#define PLAY32_RCC_CSR_WWDGRSTF_POS    (30U)
#define PLAY32_RCC_CSR_LPWRRSTF_POS    (31U)
#pragma endregion
#pragma region RCC_CSR_REGISTER_MASK
#define PLAY32_RCC_CSR_LSION_MSK       (1UL << PLAY32_RCC_CSR_LSION_POS)
#define PLAY32_RCC_CSR_LSIRDY_MSK      (1UL << PLAY32_RCC_CSR_LSIRDY_POS)
#define PLAY32_RCC_CSR_RMVF_MSK        (1UL << PLAY32_RCC_CSR_RMVF_POS)
#define PLAY32_RCC_CSR_BORRSTF_MSK     (1UL << PLAY32_RCC_CSR_BORRSTF_POS)
#define PLAY32_RCC_CSR_PINRSTF_MSK     (1UL << PLAY32_RCC_CSR_PINRSTF_POS)
#define PLAY32_RCC_CSR_PORRSTF_MSK     (1UL << PLAY32_RCC_CSR_PORRSTF_POS)
#define PLAY32_RCC_CSR_SFTRSTF_MSK     (1UL << PLAY32_RCC_CSR_SFTRSTF_POS)
#define PLAY32_RCC_CSR_IWDGRSTF_MSK    (1UL << PLAY32_RCC_CSR_IWDGRSTF_POS)
#define PLAY32_RCC_CSR_WWDGRSTF_MSK    (1UL << PLAY32_RCC_CSR_WWDGRSTF_POS)
#define PLAY32_RCC_CSR_LPWRRSTF_MSK    (1UL << PLAY32_RCC_CSR_LPWRRSTF_POS)
#pragma endregion
#pragma region RCC_CSR_REGISTER_ENUM
/**
 * @brief  Internal Low-Speed RC Oscillator (LSI) enable state type.
 * @note   Read/Write control bit (bit 0 of RCC_CSR, LSION) used to enable or disable
 *         the internal ~32 kHz RC oscillator used by the IWDG and RTC.
 * @warning LSI cannot be disabled if the Independent Watchdog (IWDG) is running;
 *          hardware forces LSI on whenever IWDG is active.
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_CSR_InternalLowSpeedOscillatorReady
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CSR_InternalLowSpeedOscillatorEnable;
/**
 * @brief  Internal Low-Speed RC Oscillator (LSI) ready flag type.
 * @note   Read-only status bit (bit 1 of RCC_CSR, LSIRDY) set by hardware to indicate
 *         that the internal ~32 kHz LSI RC oscillator is stable and ready for use.
 * @warning Wait until this flag reads ready before relying on LSI for RTC operation.
 *          After disabling LSI, this bit goes low after 3 LSI clock cycles.
 * @see    PLAY32_RCC_Ready
 * @see    PLAY32_RCC_CSR_InternalLowSpeedOscillatorEnable
 */
typedef PLAY32_RCC_Ready PLAY32_RCC_CSR_InternalLowSpeedOscillatorReady;
/**
 * @brief  Remove reset flags control type.
 * @note   Read/Write control bit (bit 24 of RCC_CSR, RMVF) written with @ref PLAY32_RCC_FLAG_SET
 *         by software to clear all hardware reset flags (bits 25 to 31) in RCC_CSR.
 * @warning Clears all reset cause flags simultaneously (BORRSTF, PINRSTF, PORRSTF, SFTRSTF,
 *          IWDGRSTF, WWDGRSTF, and LPWRRSTF). Read and store the reset cause before setting this bit.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_RemoveResetFlag;
/**
 * @brief  Brown-Out Reset (BOR) flag type.
 * @note   Read-only status bit (bit 25 of RCC_CSR, BORRSTF) set by hardware when a POR/PDR
 *         or Brown-Out Reset occurs.
 * @warning Cleared only by a Power-On Reset or by setting @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 *          Note that POR/PDR also sets this bit alongside PORRSTF.
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_BORResetFlag;
/**
 * @brief  NRST pin reset flag type.
 * @note   Read-only status bit (bit 26 of RCC_CSR, PINRSTF) set by hardware when a reset
 *         from the external NRST pin occurs.
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 *          This flag is also set during a Power-On Reset due to the internal pulse on NRST.
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_PINResetFlag;
/**
 * @brief  Power-On / Power-Down Reset (POR/PDR) flag type.
 * @note   Read-only status bit (bit 27 of RCC_CSR, PORRSTF) set by hardware when a
 *         POR/PDR reset occurs.
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_PORPDRResetFlag;
/**
 * @brief  Software reset flag type.
 * @note   Read-only status bit (bit 28 of RCC_CSR, SFTRSTF) set by hardware when a
 *         software reset occurs (via SYSRESETREQ in Cortex-M4 AIRCR).
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_SoftwareResetFlag;
/**
 * @brief  Independent Watchdog (IWDG) reset flag type.
 * @note   Read-only status bit (bit 29 of RCC_CSR, IWDGRSTF) set by hardware when an
 *         Independent Watchdog timeout reset occurs.
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_IndependentWatchdogResetFlag;
/**
 * @brief  Window Watchdog (WWDG) reset flag type.
 * @note   Read-only status bit (bit 30 of RCC_CSR, WWDGRSTF) set by hardware when a
 *         Window Watchdog reset occurs.
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_WindowWatchdogResetFlag;
/**
 * @brief  Low-power management reset flag type.
 * @note   Read-only status bit (bit 31 of RCC_CSR, LPWRRSTF) set by hardware when an
 *         illegal Stop, Standby, or Shutdown mode entry occurs (when nRST_STOP or nRST_STDBY
 *         option bytes are configured to generate a reset).
 * @warning Cleared only by writing @ref PLAY32_RCC_FLAG_SET to @ref PLAY32_RCC_CSR_RemoveResetFlag (RMVF).
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_RemoveResetFlag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_LowPowerResetFlag;
#pragma endregion
#pragma endregion

#pragma region RCC_SSCGR_REGISTER
#pragma region RCC_SSCGR_REGISTER_POSITION
#define PLAY32_RCC_SSCGR_MODPER_POS       (0U)
#define PLAY32_RCC_SSCGR_INCSTEP_POS      (13U)
#define PLAY32_RCC_SSCGR_SPREADSEL_POS    (30U)
#define PLAY32_RCC_SSCGR_SSCGEN_POS       (31U)
#pragma endregion
#pragma region RCC_SSCGR_REGISTER_MASK
#define PLAY32_RCC_SSCGR_MODPER_MSK       (8191UL << PLAY32_RCC_SSCGR_MODPER_POS)
#define PLAY32_RCC_SSCGR_INCSTEP_MSK      (32767UL << PLAY32_RCC_SSCGR_INCSTEP_POS)
#define PLAY32_RCC_SSCGR_SPREADSEL_MSK    (1UL << PLAY32_RCC_SSCGR_SPREADSEL_POS)
#define PLAY32_RCC_SSCGR_SSCGEN_MSK       (1UL << PLAY32_RCC_SSCGR_SSCGEN_POS)
#pragma endregion
#pragma region RCC_SSCGR_REGISTER_ENUM
/**
 * @brief  Spread spectrum modulation period (MODPER) value type.
 * @note   Read/Write 13-bit control field (bits 12:0 of RCC_SSCGR, MODPER[12:0], valid range 0 to 8191)
 *         that sets the triangular modulation period:
 *         \f$\text{MODPER} = \text{round}\left(\frac{f_{\text{PLL\_IN}}}{4 \times f_{\text{MOD}}}\right)\f$,
 *         where \f$f_{\text{MOD}}\f$ is the desired modulation frequency (typically \f$\le 10\text{ kHz}\f$).
 * @warning Must only be written before enabling the main PLL (PLLON = 0 in RCC_CR).
 *          Values above 8191 (0x1FFF) exceed the 13-bit field width and will be masked.
 * @see    PLAY32_RCC_SSCGR_IncrementationStep
 * @see    PLAY32_RCC_SSCGR_SpreadSpectrumModulationEnable
 */
typedef uint16_t PLAY32_RCC_SSCGR_ModulationPeriod;
/**
 * @brief  Spread spectrum incrementation step (INCSTEP) value type.
 * @note   Read/Write 15-bit control field (bits 27:13 of RCC_SSCGR, INCSTEP[14:0], valid range 0 to 32767)
 *         that sets the frequency step added to the PLL feedback divider per modulation clock cycle:
 *         \f$\text{INCSTEP} = \text{round}\left(\frac{(2^{15} - 1) \times \text{md} \times \text{PLLN}}{100 \times 5 \times \text{MODPER}}\right)\f$,
 *         where \f$\text{md}\f$ is the peak modulation depth percentage.
 * @warning Must only be written before enabling the main PLL (PLLON = 0 in RCC_CR).
 *          The product \f$\text{INCSTEP} \times \text{MODPER}\f$ must not exceed \f$2^{15} - 1\f$ (32767).
 * @see    PLAY32_RCC_SSCGR_ModulationPeriod
 * @see    PLAY32_RCC_SSCGR_SpreadSpectrumModulationEnable
 */
typedef uint32_t PLAY32_RCC_SSCGR_IncrementationStep;
/**
 * @brief  Spread spectrum modulation profile selection enumeration.
 * @note   Read/Write control bit (bit 30 of RCC_SSCGR, SPREADSEL) used to select between
 *         center-spread and down-spread frequency modulation around the nominal PLL frequency.
 * @warning Must only be written before enabling the main PLL (PLLON = 0 in RCC_CR).
 * @see    PLAY32_RCC_SSCGR_SpreadSpectrumModulationEnable
 */
typedef enum {
    PLAY32_RCC_SSCGR_SPREAD_SELECT_CENTER = 0U, /**< Center-spread modulation (frequency varies symmetrically above and below nominal). */
    PLAY32_RCC_SSCGR_SPREAD_SELECT_DOWN   = 1U  /**< Down-spread modulation (frequency varies only below nominal). */
} PLAY32_RCC_SSCGR_SpreadSelect;
/**
 * @brief  Spread spectrum clock generation (SSCG) enable state type.
 * @note   Read/Write control bit (bit 31 of RCC_SSCGR, SSCGEN) used to enable or disable
 *         triangular spread spectrum modulation on the main PLL output to reduce EMI.
 * @warning Must only be written while the main PLL is disabled (PLLON = 0 in RCC_CR).
 *          Ensure @ref PLAY32_RCC_SSCGR_ModulationPeriod, @ref PLAY32_RCC_SSCGR_IncrementationStep,
 *          and @ref PLAY32_RCC_SSCGR_SpreadSelect are configured prior to enabling.
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_SSCGR_ModulationPeriod
 * @see    PLAY32_RCC_SSCGR_IncrementationStep
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_SSCGR_SpreadSpectrumModulationEnable;

#pragma endregion
#pragma endregion

#pragma region RCC_PLLI2SCFGR_REGISTER
#pragma region RCC_PLLI2SCFGR_REGISTER_POSITION
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SN_POS    (6U)
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SR_POS    (28U)
#pragma endregion
#pragma region RCC_PLLI2SCFGR_REGISTER_MASK
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SN_MSK    (511UL << PLAY32_RCC_PLLI2SCFGR_PLLI2SN_POS)
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SR_MSK    (7UL << PLAY32_RCC_PLLI2SCFGR_PLLI2SR_POS)
#pragma endregion
#pragma region RCC_PLLI2SCFGR_REGISTER_VALUE
/**
 * @brief  PLLI2S VCO multiplication factor (PLLI2SN) value type.
 * @note   Read/Write 9-bit control field (bits 14:6 of RCC_PLLI2SCFGR, PLLI2SN[8:0], valid range 50 to 432)
 *         that sets the multiplication factor for the PLLI2S VCO output frequency:
 *         \f$f_{\text{VCO\_I2S}} = f_{\text{PLL\_IN}} \times \text{PLLI2SN}\f$.
 * @warning Must only be written when PLLI2S is disabled (PLLI2SON = 0 in RCC_CR).
 *          Ensure the resulting VCO frequency remains within the specified hardware range
 *          (typically 100 MHz to 432 MHz). Note that values above 255 require a 16-bit type.
 * @see    PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SDivision
 */
typedef uint8_t PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SMultiplication;

/**
 * @brief  PLLI2S division factor for I2S clocks (PLLI2SR) value type.
 * @note   Read/Write 3-bit control field (bits 30:28 of RCC_PLLI2SCFGR, PLLI2SR[2:0], valid range 2 to 7)
 *         that divides the PLLI2S VCO output to generate the I2S peripheral clock:
 *         \f$f_{\text{I2S\_CLK}} = \frac{f_{\text{VCO\_I2S}}}{\text{PLLI2SR}}\f$.
 * @warning Must only be written when PLLI2S is disabled (PLLI2SON = 0 in RCC_CR).
 *          Values 0 and 1 are forbidden by hardware; ensure the resulting I2S clock
 *          does not exceed the maximum allowed frequency (192 MHz).
 * @see    PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SMultiplication
 */
typedef uint16_t PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SDivision;
#pragma endregion
#pragma endregion

#pragma endregion

#endif //PLAY32_RCC_TYPES_H
