/**
 * @file    rcc_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for Reset and Clock Control (RCC) of STM32F401 CCU.
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

/**
 * @defgroup PLAY32_RCC Reset and Clock Control (RCC)
 * @brief Hardware register map, base address, bit masks, and type-safe enumerations for RCC.
 * @{
 */

/**
 * @defgroup PLAY32_RCC_Memory_Map Peripheral Base Address and Register Map
 * @brief AHB1 base address calculation and memory-mapped register structure for RCC.
 * @{
 */

/**
 * @brief  Base address of the AHB1 peripheral bus (0x40020000).
 * @note   RCC is mapped onto the AHB1 peripheral bus in STM32F401.
 */
#define PLAY32_AHB1_PERIPHERAL    ((1UL << 30) | (1UL << 17))

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE         (1UL << 10)

/**
 * @brief  AHB1 memory slot index for RCC (offset 14 * 0x0400 = 0x3800).
 * @see    PLAY32_RCC_BASE
 */
#define PLAY32_RCC_BASE_POS       (14U)

/**
 * @brief  RCC peripheral base address (0x40023800).
 * @note   Computed from @ref PLAY32_AHB1_PERIPHERAL and @ref PLAY32_RCC_BASE_POS.
 */
#define PLAY32_RCC_BASE           (PLAY32_AHB1_PERIPHERAL + (PLAY32_RCC_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  Reset and Clock Control (RCC) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 6.3, offsets 0x00-0x8C).
 * @warning Reserved fields (`RESERVED0` through `RESERVED7`) must not be read or written by software.
 *          Registers `BDCR` and `CSR` (RTCSEL/RTCEN/BDRST) reside in the Backup domain and require
 *          unlocking `PWR_CR.DBP` before write access.
 */
typedef struct {
    volatile uint32_t CR;             /**< Offset: 0x00 - Clock control register. */
    volatile uint32_t PLLCFGR;        /**< Offset: 0x04 - PLL configuration register. */
    volatile uint32_t CFGR;           /**< Offset: 0x08 - Clock configuration register. */
    volatile uint32_t CIR;            /**< Offset: 0x0C - Clock interrupt register. */
    volatile uint32_t AHB1RSTR;       /**< Offset: 0x10 - AHB1 peripheral reset register. */
    volatile uint32_t AHB2RSTR;       /**< Offset: 0x14 - AHB2 peripheral reset register. */
    uint32_t          RESERVED0[2];   /**< Offset: 0x18-0x1C - Reserved (do not access). */
    volatile uint32_t APB1RSTR;       /**< Offset: 0x20 - APB1 peripheral reset register. */
    volatile uint32_t APB2RSTR;       /**< Offset: 0x24 - APB2 peripheral reset register. */
    uint32_t          RESERVED1[2];   /**< Offset: 0x28-0x2C - Reserved (do not access). */
    volatile uint32_t AHB1ENR;        /**< Offset: 0x30 - AHB1 peripheral clock enable register. */
    volatile uint32_t AHB2ENR;        /**< Offset: 0x34 - AHB2 peripheral clock enable register. */
    uint32_t          RESERVED2[2];   /**< Offset: 0x38-0x3C - Reserved (do not access). */
    volatile uint32_t APB1ENR;        /**< Offset: 0x40 - APB1 peripheral clock enable register. */
    volatile uint32_t APB2ENR;        /**< Offset: 0x44 - APB2 peripheral clock enable register. */
    uint32_t          RESERVED3[2];   /**< Offset: 0x48-0x4C - Reserved (do not access). */
    volatile uint32_t AHB1LPENR;      /**< Offset: 0x50 - AHB1 peripheral clock enable in low-power mode register. */
    volatile uint32_t AHB2LPENR;      /**< Offset: 0x54 - AHB2 peripheral clock enable in low-power mode register. */
    uint32_t          RESERVED4[2];   /**< Offset: 0x58-0x5C - Reserved (do not access). */
    volatile uint32_t APB1LPENR;      /**< Offset: 0x60 - APB1 peripheral clock enable in low-power mode register. */
    volatile uint32_t APB2LPENR;      /**< Offset: 0x64 - APB2 peripheral clock enable in low-power mode register. */
    uint32_t          RESERVED5[2];   /**< Offset: 0x68-0x6C - Reserved (do not access). */
    volatile uint32_t BDCR;           /**< Offset: 0x70 - Backup domain control register. */
    volatile uint32_t CSR;            /**< Offset: 0x74 - Clock control & status register. */
    uint32_t          RESERVED6[2];   /**< Offset: 0x78-0x7C - Reserved (do not access). */
    volatile uint32_t SSCGR;          /**< Offset: 0x80 - Spread spectrum clock generation register. */
    volatile uint32_t PLLI2SCFGR;     /**< Offset: 0x84 - PLLI2S configuration register. */
    uint32_t          RESERVED7;      /**< Offset: 0x88 - Reserved (do not access). */
    volatile uint32_t DCKCFGR;        /**< Offset: 0x8C - Dedicated clocks configuration register. */
} PLAY32_RCC_TypeDef;

/** @} */ /* End of PLAY32_RCC_Memory_Map */

#define PLAY32_RCC ((PLAY32_RCC_TypeDef *)PLAY32_RCC_BASE)

/**
 * @defgroup PLAY32_RCC_Common_Types Common RCC Enumerations
 * @brief Reusable active-high, active-low, reset, and status flag enumerations across RCC registers.
 * @{
 */
#pragma region RCC_COMMON_ENUM

/**
 * @brief  Standard active-high control switch states for RCC peripheral and clock bits.
 * @note   Used across RCC control and enable registers where logic '1' activates
 *         a clock source, peripheral clock, or feature, and logic '0' disables it.
 * @see    PLAY32_RCC_InvertedSwitch
 */
typedef enum {
    PLAY32_RCC_SWITCH_DISABLED = 0U, /**< Peripheral, clock, or feature disabled (0). */
    PLAY32_RCC_SWITCH_ENABLED  = 1U  /**< Peripheral, clock, or feature enabled (1). */
} PLAY32_RCC_Switch;

/**
 * @brief  Inverted active-low control switch states for RCC configuration bits.
 * @note   Used for hardware control bits with inverted logic where logic '0'
 *         enables the feature or mode and logic '1' disables it.
 * @see    PLAY32_RCC_Switch
 */
typedef enum {
    PLAY32_RCC_SWITCH_INVERTED_DISABLED = 1U, /**< Feature or mode disabled (1). */
    PLAY32_RCC_SWITCH_INVERTED_ENABLED  = 0U  /**< Feature or mode enabled (0). */
} PLAY32_RCC_InvertedSwitch;

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
 * @see    PLAY32_RCC_Switch
 */
typedef enum {
    PLAY32_RCC_FLAG_NOT_SET = 0U, /**< Flag is cleared (no event or reset condition occurred). */
    PLAY32_RCC_FLAG_SET     = 1U  /**< Flag is set (hardware event or reset condition occurred). */
} PLAY32_RCC_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_RCC_Common_Types */


#pragma region RCC_CR_REGISTER
/**
 * @defgroup PLAY32_RCC_CR_Types RCC Clock Control Register (RCC_CR)
 * @brief Bit positions, masks, and oscillator/PLL control types for RCC_CR (offset 0x00).
 * @{
 */
#pragma region RCC_CR_REGISTER

#pragma region RCC_CR_REGISTER_POSITION
#define PLAY32_RCC_CR_HSION_POS        (0U)  /**< Bit 0: Internal high-speed clock enable position. */
#define PLAY32_RCC_CR_HSIRDY_POS       (1U)  /**< Bit 1: Internal high-speed clock ready flag position. */
#define PLAY32_RCC_CR_HSITRIM_POS      (3U)  /**< Bits [7:3]: Internal high-speed clock trimming position. */
#define PLAY32_RCC_CR_HSICAL_POS       (8U)  /**< Bits [15:8]: Internal high-speed clock calibration position. */
#define PLAY32_RCC_CR_HSEON_POS        (16U) /**< Bit 16: HSE clock enable position. */
#define PLAY32_RCC_CR_HSERDY_POS       (17U) /**< Bit 17: HSE clock ready flag position. */
#define PLAY32_RCC_CR_HSEBYP_POS       (18U) /**< Bit 18: HSE clock bypass position. */
#define PLAY32_RCC_CR_CSSON_POS        (19U) /**< Bit 19: Clock security system enable position. */
#define PLAY32_RCC_CR_PLLON_POS        (24U) /**< Bit 24: Main PLL enable position. */
#define PLAY32_RCC_CR_PLLRDY_POS       (25U) /**< Bit 25: Main PLL clock ready flag position. */
#define PLAY32_RCC_CR_PLLI2SON_POS     (26U) /**< Bit 26: PLLI2S enable position. */
#define PLAY32_RCC_CR_PLLI2SRDY_POS    (27U) /**< Bit 27: PLLI2S clock ready flag position. */
#pragma endregion

#pragma region RCC_CR_REGISTER_MASK
#define PLAY32_RCC_CR_HSION_MSK        (1UL << PLAY32_RCC_CR_HSION_POS)     /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_CR_HSIRDY_MSK       (1UL << PLAY32_RCC_CR_HSIRDY_POS)    /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_CR_HSITRIM_MSK      (31UL << PLAY32_RCC_CR_HSITRIM_POS)  /**< Bits [7:3] mask (0x000000F8). */
#define PLAY32_RCC_CR_HSICAL_MSK       (255UL << PLAY32_RCC_CR_HSICAL_POS)  /**< Bits [15:8] mask (0x0000FF00). */
#define PLAY32_RCC_CR_HSEON_MSK        (1UL << PLAY32_RCC_CR_HSEON_POS)     /**< Bit 16 mask (0x00010000). */
#define PLAY32_RCC_CR_HSERDY_MSK       (1UL << PLAY32_RCC_CR_HSERDY_POS)    /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_CR_HSEBYP_MSK       (1UL << PLAY32_RCC_CR_HSEBYP_POS)    /**< Bit 18 mask (0x00040000). */
#define PLAY32_RCC_CR_CSSON_MSK        (1UL << PLAY32_RCC_CR_CSSON_POS)     /**< Bit 19 mask (0x00080000). */
#define PLAY32_RCC_CR_PLLON_MSK        (1UL << PLAY32_RCC_CR_PLLON_POS)     /**< Bit 24 mask (0x01000000). */
#define PLAY32_RCC_CR_PLLRDY_MSK       (1UL << PLAY32_RCC_CR_PLLRDY_POS)    /**< Bit 25 mask (0x02000000). */
#define PLAY32_RCC_CR_PLLI2SON_MSK     (1UL << PLAY32_RCC_CR_PLLI2SON_POS)  /**< Bit 26 mask (0x04000000). */
#define PLAY32_RCC_CR_PLLI2SRDY_MSK    (1UL << PLAY32_RCC_CR_PLLI2SRDY_POS) /**< Bit 27 mask (0x08000000). */
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
 * @note   Read-only hardware status bit (bit 1 of RCC_CR, HSIRDY) indicating whether
 *         the 16 MHz HSI oscillator is stable and ready for use.
 *         When disabling HSI, this flag remains set for 6 HSI clock cycles.
 */
typedef enum {
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_NOT_READY = 0U, /**< HSI oscillator not ready. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_READY     = 1U  /**< HSI oscillator ready and stable. */
} PLAY32_RCC_CR_HighSpeedInternalClockReady;

/**
 * @brief  High-Speed Internal (HSI) clock trimming step values (0 to 31).
 * @note   User-programmable 5-bit offset (bits 7:3 of RCC_CR, HSITRIM[4:0]) added to the factory
 *         calibration value to form the final @ref PLAY32_RCC_CR_HighSpeedInternalClockCalibration.
 *         Each step shifts the 16 MHz HSI frequency by approximately 40 kHz.
 *         Default value at reset is @ref PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_DEFAULT (16).
 */
typedef enum {
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_16 = 0U,   /**< ~ -640 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_15 = 1U,   /**< ~ -600 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_14 = 2U,   /**< ~ -560 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_13 = 3U,   /**< ~ -520 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_12 = 4U,   /**< ~ -480 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_11 = 5U,   /**< ~ -440 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_10 = 6U,   /**< ~ -400 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_9  = 7U,   /**< ~ -360 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_8  = 8U,   /**< ~ -320 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_7  = 9U,   /**< ~ -280 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_6  = 10U,  /**< ~ -240 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_5  = 11U,  /**< ~ -200 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_4  = 12U,  /**< ~ -160 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_3  = 13U,  /**< ~ -120 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_2  = 14U,  /**< ~ -80 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_MINUS_1  = 15U,  /**< ~ -40 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_DEFAULT  = 16U,  /**< 0 kHz (Reset value, 16 MHz). */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_1   = 17U,  /**< ~ +40 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_2   = 18U,  /**< ~ +80 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_3   = 19U,  /**< ~ +120 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_4   = 20U,  /**< ~ +160 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_5   = 21U,  /**< ~ +200 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_6   = 22U,  /**< ~ +240 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_7   = 23U,  /**< ~ +280 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_8   = 24U,  /**< ~ +320 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_9   = 25U,  /**< ~ +360 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_10  = 26U,  /**< ~ +400 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_11  = 27U,  /**< ~ +440 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_12  = 28U,  /**< ~ +480 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_13  = 29U,  /**< ~ +520 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_14  = 30U,  /**< ~ +560 kHz. */
    PLAY32_RCC_CR_HIGH_SPEED_INTERNAL_CLOCK_TRIM_PLUS_15  = 31U   /**< ~ +600 kHz. */
} PLAY32_RCC_CR_HighSpeedInternalClockTrim;

/**
 * @brief  High-Speed Internal (HSI) clock calibration value type (0x00 to 0xFF).
 * @note   Read-only 8-bit hardware value (bits 15:8 of RCC_CR, HSICAL[7:0]) representing the actual
 *         sum of the factory calibration and the user-defined @ref PLAY32_RCC_CR_HighSpeedInternalClockTrim
 *         value. Automatically updated by hardware upon trimming changes.
 */
typedef uint8_t PLAY32_RCC_CR_HighSpeedInternalClockCalibration;

/**
 * @brief  High-Speed External (HSE) clock enable state type.
 * @note   Read/Write control bit (bit 16 of RCC_CR, HSEON) used to enable or disable
 *         the external crystal/ceramic oscillator or clock source. Cleared by hardware
 *         when entering Stop or Standby modes.
 * @warning Cannot be disabled if HSE is selected directly or indirectly (via PLL) as SYSCLK.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_HighSpeedExternalClockEnable;

/**
 * @brief  High-Speed External (HSE) clock ready flag type.
 * @note   Read-only hardware status bit (bit 17 of RCC_CR, HSERDY) indicating whether
 *         the external crystal/ceramic resonator or external clock source is stable.
 *         When disabling HSE, this flag remains set for 6 HSE clock cycles.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CR_HighSpeedExternalClockReady;

/**
 * @brief  High-Speed External (HSE) clock bypass mode state type.
 * @note   Read/Write control bit (bit 18 of RCC_CR, HSEBYP) used to bypass the internal
 *         oscillator driver with an external clock source (e.g., an active oscillator
 *         or clock signal fed directly into the OSC_IN pin).
 * @warning This bit can only be modified when the HSE oscillator is disabled (`HSEON = 0`).
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_CR_HighSpeedExternalClockEnable
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CR_HighSpeedExternalClockBypass;

/**
 * @brief  Clock Security System (CSS) enable state type.
 * @note   Read/Write control bit (bit 19 of RCC_CR, CSSON) used to enable or disable the
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
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CR_PhaseLockedLoopReady;

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
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CR_PhaseLockedLoopI2SReady;
#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_CR_Types */

/**
 * @defgroup PLAY32_RCC_PLLCFGR_Types RCC PLL Configuration Register (RCC_PLLCFGR)
 * @brief Bit positions, masks, and divider/source types for RCC_PLLCFGR (offset 0x04).
 * @{
 */
#pragma region RCC_PLLCFGR_REGISTER

#pragma region RCC_PLLCFGR_REGISTER_POSITION
#define PLAY32_RCC_PLLCFGR_PLLM_POS       (0U)  /**< Bits [5:0]: Division factor for the main PLL and audio PLL (PLLI2S) input clock position. */
#define PLAY32_RCC_PLLCFGR_PLLN_POS       (6U)  /**< Bits [14:6]: Main PLL multiplication factor for VCO position. */
#define PLAY32_RCC_PLLCFGR_PLLP_POS       (16U) /**< Bits [17:16]: Main PLL division factor for main system clock position. */
#define PLAY32_RCC_PLLCFGR_PLLSRC_POS     (22U) /**< Bit 22: Main PLL and audio PLL (PLLI2S) entry clock source position. */
#define PLAY32_RCC_PLLCFGR_PLLQ_POS       (24U) /**< Bits [27:24]: Main PLL division factor for USB OTG FS and SDIO clocks position. */
#define PLAY32_RCC_PLLCFGR_PLLQ0_POS      (24U) /**< Bit 24: PLLQ bit 0 position. */
#define PLAY32_RCC_PLLCFGR_PLLQ1_POS      (25U) /**< Bit 25: PLLQ bit 1 position. */
#define PLAY32_RCC_PLLCFGR_PLLQ2_POS      (26U) /**< Bit 26: PLLQ bit 2 position. */
#define PLAY32_RCC_PLLCFGR_PLLQ3_POS      (27U) /**< Bit 27: PLLQ bit 3 position. */
#pragma endregion

#pragma region RCC_PLLCFGR_REGISTER_MASK
#define PLAY32_RCC_PLLCFGR_PLLM_MSK       (63UL << PLAY32_RCC_PLLCFGR_PLLM_POS)    /**< Bits [5:0] mask (0x0000003F). */
#define PLAY32_RCC_PLLCFGR_PLLN_MSK       (511UL << PLAY32_RCC_PLLCFGR_PLLN_POS)   /**< Bits [14:6] mask (0x00007FC0). */
#define PLAY32_RCC_PLLCFGR_PLLP_MSK       (3UL << PLAY32_RCC_PLLCFGR_PLLP_POS)     /**< Bits [17:16] mask (0x00030000). */
#define PLAY32_RCC_PLLCFGR_PLLSRC_MSK     (1UL << PLAY32_RCC_PLLCFGR_PLLSRC_POS)   /**< Bit 22 mask (0x00400000). */
#define PLAY32_RCC_PLLCFGR_PLLQ_MSK       (15UL << PLAY32_RCC_PLLCFGR_PLLQ_POS)    /**< Bits [27:24] mask (0x0F000000). */
#define PLAY32_RCC_PLLCFGR_PLLQ0_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ0_POS)    /**< Bit 24 mask (0x01000000). */
#define PLAY32_RCC_PLLCFGR_PLLQ1_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ1_POS)    /**< Bit 25 mask (0x02000000). */
#define PLAY32_RCC_PLLCFGR_PLLQ2_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ2_POS)    /**< Bit 26 mask (0x04000000). */
#define PLAY32_RCC_PLLCFGR_PLLQ3_MSK      (1UL << PLAY32_RCC_PLLCFGR_PLLQ3_POS)    /**< Bit 27 mask (0x08000000). */
#pragma endregion

#pragma region RCC_PLLCFGR_REGISTER_ENUM

/**
 * @brief  Main PLL and PLLI2S input clock division factor (PLLM) value type.
 * @note   Read/Write 6-bit field (bits 5:0 of RCC_PLLCFGR, PLLM[5:0], valid range 2 to 63)
 *         that divides the selected entry clock (`PLLSRC`) before feeding the VCO:
 *         \f$f_{\text{VCO\_IN}} = \frac{f_{\text{PLL\_SRC}}}{\text{PLLM}}\f$.
 * @warning Must only be written when both the main PLL and PLLI2S are disabled (`PLLON = 0` and `PLLI2SON = 0`).
 *          Values 0 and 1 are forbidden. Software must configure PLLM so that the VCO input frequency
 *          lies between **1 MHz and 2 MHz** (2 MHz is recommended to limit PLL jitter).
 * @see    PLAY32_RCC_PLLCFGR_PhaseLockedLoopClockSource
 */
typedef uint8_t PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainDivider;

/**
 * @brief  Main PLL VCO multiplication factor (PLLN) value type.
 * @note   Read/Write 9-bit field (bits 14:6 of RCC_PLLCFGR, PLLN[8:0], valid range 50 to 432)
 *         that multiplies the VCO input frequency to generate the VCO output clock:
 *         \f$f_{\text{VCO\_OUT}} = f_{\text{VCO\_IN}} \times \text{PLLN}\f$.
 * @warning Must only be written when the main PLL is disabled (`PLLON = 0`).
 *          Values outside 50..432 are forbidden, and the resulting VCO output frequency
 *          must remain between **192 MHz and 432 MHz** on STM32F401.
 * @see    PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainDivider
 */
typedef uint16_t PLAY32_RCC_PLLCFGR_PhaseLockedLoopNumberMultiplicator;

/**
 * @brief  Main PLL division factor for main system clock (PLLP) enumeration.
 * @note   Read/Write 2-bit field (bits 17:16 of RCC_PLLCFGR, PLLP[1:0]) that divides the VCO
 *         output frequency to produce the main PLL system clock output:
 *         \f$f_{\text{PLL\_OUT}} = \frac{f_{\text{VCO\_OUT}}}{\text{PLLP}}\f$.
 * @warning Must only be written when the main PLL is disabled (`PLLON = 0`).
 *          Do not exceed the maximum allowed `SYSCLK` frequency (**84 MHz** on STM32F401).
 */
typedef enum {
    PLAY32_RCC_PLLCFGR_MAIN_SYSTEM_DIVIDER_BY_2 = 0U, /**< PLLP = 2 (reset value). */
    PLAY32_RCC_PLLCFGR_MAIN_SYSTEM_DIVIDER_BY_4 = 1U, /**< PLLP = 4. */
    PLAY32_RCC_PLLCFGR_MAIN_SYSTEM_DIVIDER_BY_6 = 2U, /**< PLLP = 6. */
    PLAY32_RCC_PLLCFGR_MAIN_SYSTEM_DIVIDER_BY_8 = 3U  /**< PLLP = 8. */
} PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainSystemDivider;

/**
 * @brief  Main PLL and PLLI2S entry clock source (PLLSRC) enumeration.
 * @note   Read/Write control bit (bit 22 of RCC_PLLCFGR, PLLSRC) selecting the reference
 *         oscillator fed into the shared `PLLM` prescaler for both main PLL and PLLI2S.
 * @warning Must only be written when both the main PLL and PLLI2S are disabled (`PLLON = 0` and `PLLI2SON = 0`).
 */
typedef enum {
    PLAY32_RCC_PLLCFGR_CLOCK_SOURCE_HSI = 0U, /**< High-Speed Internal (16 MHz HSI) oscillator selected as PLL/PLLI2S clock entry. */
    PLAY32_RCC_PLLCFGR_CLOCK_SOURCE_HSE = 1U  /**< High-Speed External (HSE) oscillator selected as PLL/PLLI2S clock entry. */
} PLAY32_RCC_PLLCFGR_PhaseLockedLoopClockSource;

/**
 * @brief  Main PLL division factor for USB OTG FS and SDIO clocks (PLLQ) value type.
 * @note   Read/Write 4-bit field (bits 27:24 of RCC_PLLCFGR, PLLQ[3:0], valid range 2 to 15)
 *         that divides the VCO output frequency to generate the 48 MHz peripheral clock:
 *         \f$f_{\text{USB\_SDIO}} = \frac{f_{\text{VCO\_OUT}}}{\text{PLLQ}}\f$.
 * @warning Must only be written when the main PLL is disabled (`PLLON = 0`).
 *          Values 0 and 1 are forbidden. If USB OTG FS is used, `PLLQ` must be chosen so
 *          that the resulting clock equals exactly **48 MHz** (and never exceeds 48 MHz for SDIO).
 */
typedef uint8_t PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainQDivider;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_PLLCFGR_Types */

/**
 * @defgroup PLAY32_RCC_CFGR_Types RCC Clock Configuration Register (RCC_CFGR)
 * @brief Bit positions, masks, and system clock / prescaler / MCO enumerations for RCC_CFGR (offset 0x08).
 * @{
 */
#pragma region RCC_CFGR_REGISTER

#pragma region RCC_CFGR_REGISTER_POSITION
#define PLAY32_RCC_CFGR_SW_POS         (0U)  /**< Bits [1:0]: System clock switch position. */
#define PLAY32_RCC_CFGR_SWS_POS        (2U)  /**< Bits [3:2]: System clock switch status position. */
#define PLAY32_RCC_CFGR_HPRE_POS       (4U)  /**< Bits [7:4]: AHB prescaler position. */
#define PLAY32_RCC_CFGR_PPRE1_POS      (10U) /**< Bits [12:10]: APB1 low-speed prescaler position. */
#define PLAY32_RCC_CFGR_PPRE2_POS      (13U) /**< Bits [15:13]: APB2 high-speed prescaler position. */
#define PLAY32_RCC_CFGR_RTCPRE_POS     (16U) /**< Bits [20:16]: HSE division factor for RTC clock position. */
#define PLAY32_RCC_CFGR_MCO1_POS       (21U) /**< Bits [22:21]: Microcontroller clock output 1 source position. */
#define PLAY32_RCC_CFGR_I2SSRC_POS     (23U) /**< Bit 23: I2S clock selection position. */
#define PLAY32_RCC_CFGR_MCO1PRE_POS    (24U) /**< Bits [26:24]: MCO1 prescaler position. */
#define PLAY32_RCC_CFGR_MCO2PRE_POS    (27U) /**< Bits [29:27]: MCO2 prescaler position. */
#define PLAY32_RCC_CFGR_MCO2_POS       (30U) /**< Bits [31:30]: Microcontroller clock output 2 source position. */
#pragma endregion

#pragma region RCC_CFGR_REGISTER_MASK
#define PLAY32_RCC_CFGR_SW_MSK         (3UL << PLAY32_RCC_CFGR_SW_POS)      /**< Bits [1:0] mask (0x00000003). */
#define PLAY32_RCC_CFGR_SWS_MSK        (3UL << PLAY32_RCC_CFGR_SWS_POS)     /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_RCC_CFGR_HPRE_MSK       (15UL << PLAY32_RCC_CFGR_HPRE_POS)   /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_RCC_CFGR_PPRE1_MSK      (7UL << PLAY32_RCC_CFGR_PPRE1_POS)   /**< Bits [12:10] mask (0x00001C00). */
#define PLAY32_RCC_CFGR_PPRE2_MSK      (7UL << PLAY32_RCC_CFGR_PPRE2_POS)   /**< Bits [15:13] mask (0x0000E000). */
#define PLAY32_RCC_CFGR_RTCPRE_MSK     (31UL << PLAY32_RCC_CFGR_RTCPRE_POS) /**< Bits [20:16] mask (0x001F0000). */
#define PLAY32_RCC_CFGR_MCO1_MSK       (3UL << PLAY32_RCC_CFGR_MCO1_POS)    /**< Bits [22:21] mask (0x00600000). */
#define PLAY32_RCC_CFGR_I2SSRC_MSK     (1UL << PLAY32_RCC_CFGR_I2SSRC_POS)  /**< Bit 23 mask (0x00800000). */
#define PLAY32_RCC_CFGR_MCO1PRE_MSK    (7UL << PLAY32_RCC_CFGR_MCO1PRE_POS) /**< Bits [26:24] mask (0x07000000). */
#define PLAY32_RCC_CFGR_MCO2PRE_MSK    (7UL << PLAY32_RCC_CFGR_MCO2PRE_POS) /**< Bits [29:27] mask (0x38000000). */
#define PLAY32_RCC_CFGR_MCO2_MSK       (3UL << PLAY32_RCC_CFGR_MCO2_POS)    /**< Bits [31:30] mask (0xC0000000). */
#pragma endregion

#pragma region RCC_CFGR_REGISTER_ENUM

/**
 * @brief  System clock switch (SW) selection enumeration.
 * @note   Read/Write 2-bit field (bits 1:0 of RCC_CFGR, SW[1:0]) used to select the
 *         system clock (`SYSCLK`) source.
 * @warning A target clock source can only be selected after its corresponding ready flag
 *          (`HSIRDY`, `HSERDY`, or `PLLRDY`) is set. Poll @ref PLAY32_RCC_CFGR_SystemClockSwitchStatus
 *          (`SWS`) until it matches the selected source.
 * @see    PLAY32_RCC_CFGR_SystemClockSwitchStatus
 */
typedef enum {
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_HSI = 0U, /**< HSI oscillator selected as system clock (reset state). */
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_HSE = 1U, /**< HSE oscillator selected as system clock. */
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_PLL = 2U  /**< Main PLL selected as system clock. */
} PLAY32_RCC_CFGR_SystemClockSwitch;

/**
 * @brief  System clock switch status (SWS) enumeration.
 * @note   Read-only 2-bit hardware status field (bits 3:2 of RCC_CFGR, SWS[1:0]) set and
 *         cleared by hardware to indicate which clock source is currently driving `SYSCLK`.
 * @see    PLAY32_RCC_CFGR_SystemClockSwitch
 */
typedef enum {
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_STATUS_HSI = 0U, /**< HSI oscillator is actively used as the system clock. */
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_STATUS_HSE = 1U, /**< HSE oscillator is actively used as the system clock. */
    PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_STATUS_PLL = 2U  /**< Main PLL is actively used as the system clock. */
} PLAY32_RCC_CFGR_SystemClockSwitchStatus;

/**
 * @brief  AHB prescaler (HPRE) division factor enumeration.
 * @note   Read/Write 4-bit field (bits 7:4 of RCC_CFGR, HPRE[3:0]) controlling the division
 *         factor from `SYSCLK` to the AHB bus clock (`HCLK`).
 * @warning If USB OTG FS or SDIO is used, `HCLK` must be at least **25 MHz** (or >= 14.2 MHz for USB OTG FS).
 */
typedef enum {
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_1   = 0U,  /**< SYSCLK not divided (HCLK = SYSCLK). */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_2   = 8U,  /**< SYSCLK divided by 2. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_4   = 9U,  /**< SYSCLK divided by 4. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_8   = 10U, /**< SYSCLK divided by 8. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_16  = 11U, /**< SYSCLK divided by 16. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_64  = 12U, /**< SYSCLK divided by 64. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_128 = 13U, /**< SYSCLK divided by 128. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_256 = 14U, /**< SYSCLK divided by 256. */
    PLAY32_RCC_CFGR_AHB_PRESCALER_DIV_512 = 15U  /**< SYSCLK divided by 512. */
} PLAY32_RCC_CFGR_AHBPrescaler;

/**
 * @brief  APB1 low-speed prescaler (PPRE1) division factor enumeration.
 * @note   Read/Write 3-bit field (bits 12:10 of RCC_CFGR, PPRE1[2:0]) controlling the division
 *         factor from `HCLK` to the APB1 peripheral clock (`PCLK1`).
 * @warning Software must configure `PPRE1` so that `PCLK1` never exceeds **42 MHz** on STM32F401
 *          (e.g., select `DIV_2` when `HCLK = 84 MHz`).
 */
typedef enum {
    PLAY32_RCC_CFGR_APB1_PRESCALER_DIV_1  = 0U, /**< HCLK not divided (PCLK1 = HCLK). */
    PLAY32_RCC_CFGR_APB1_PRESCALER_DIV_2  = 4U, /**< HCLK divided by 2. */
    PLAY32_RCC_CFGR_APB1_PRESCALER_DIV_4  = 5U, /**< HCLK divided by 4. */
    PLAY32_RCC_CFGR_APB1_PRESCALER_DIV_8  = 6U, /**< HCLK divided by 8. */
    PLAY32_RCC_CFGR_APB1_PRESCALER_DIV_16 = 7U  /**< HCLK divided by 16. */
} PLAY32_RCC_CFGR_APB1Prescaler;

/**
 * @brief  APB2 high-speed prescaler (PPRE2) division factor enumeration.
 * @note   Read/Write 3-bit field (bits 15:13 of RCC_CFGR, PPRE2[2:0]) controlling the division
 *         factor from `HCLK` to the APB2 peripheral clock (`PCLK2`).
 * @warning Software must configure `PPRE2` so that `PCLK2` never exceeds **84 MHz** on STM32F401.
 */
typedef enum {
    PLAY32_RCC_CFGR_APB2_PRESCALER_DIV_1  = 0U, /**< HCLK not divided (PCLK2 = HCLK). */
    PLAY32_RCC_CFGR_APB2_PRESCALER_DIV_2  = 4U, /**< HCLK divided by 2. */
    PLAY32_RCC_CFGR_APB2_PRESCALER_DIV_4  = 5U, /**< HCLK divided by 4. */
    PLAY32_RCC_CFGR_APB2_PRESCALER_DIV_8  = 6U, /**< HCLK divided by 8. */
    PLAY32_RCC_CFGR_APB2_PRESCALER_DIV_16 = 7U  /**< HCLK divided by 16. */
} PLAY32_RCC_CFGR_APB2Prescaler;

/**
 * @brief  HSE division factor for RTC clock (RTCPRE) value type.
 * @note   Read/Write 5-bit field (bits 20:16 of RCC_CFGR, RTCPRE[4:0], valid range 2 to 31)
 *         dividing the HSE clock before feeding the RTC clock multiplexer (`RTCSEL = 11`).
 * @warning Values 0 and 1 disable the HSE-to-RTC clock (`No clock`). Software must configure
 *          `RTCPRE` to yield a **1 MHz** input clock to the RTC when HSE is used.
 * @see    PLAY32_RCC_BDCR_RealTimeClockSourceSelection
 */
typedef uint8_t PLAY32_RCC_CFGR_RTCPrescaler;

/**
 * @brief  Microcontroller clock output 1 (MCO1) source selection enumeration.
 * @note   Read/Write 2-bit field (bits 22:21 of RCC_CFGR, MCO1[1:0]) selecting the clock
 *         signal output onto the `PA8` pin (when configured in AF0 mode).
 * @warning Clock switching on MCO1 may generate glitches; configure before enabling the output pin.
 * @see    PLAY32_RCC_CFGR_MCO1Prescaler
 */
typedef enum {
    PLAY32_RCC_CFGR_MCO1_SOURCE_HSI = 0U, /**< HSI clock selected on MCO1 (PA8). */
    PLAY32_RCC_CFGR_MCO1_SOURCE_LSE = 1U, /**< LSE oscillator clock selected on MCO1 (PA8). */
    PLAY32_RCC_CFGR_MCO1_SOURCE_HSE = 2U, /**< HSE oscillator clock selected on MCO1 (PA8). */
    PLAY32_RCC_CFGR_MCO1_SOURCE_PLL = 3U  /**< Main PLL clock selected on MCO1 (PA8). */
} PLAY32_RCC_CFGR_MCO1Source;

/**
 * @brief  I2S clock source selection (I2SSRC) enumeration.
 * @note   Read/Write control bit (bit 23 of RCC_CFGR, I2SSRC) selecting the clock source
 *         used by the I2S peripherals (SPI2/I2S2 and SPI3/I2S3).
 * @warning Must only be modified when both PLLI2S (`PLLI2SON = 0`) and all I2S peripherals are disabled.
 */
typedef enum {
    PLAY32_RCC_CFGR_I2S_SOURCE_PLLI2S   = 0U, /**< PLLI2S clock used as I2S clock source (default). */
    PLAY32_RCC_CFGR_I2S_SOURCE_EXT_CKIN = 1U  /**< External clock mapped on the I2S_CKIN pin used as I2S clock source. */
} PLAY32_RCC_CFGR_I2SSource;

/**
 * @brief  Microcontroller clock output 1 prescaler (MCO1PRE) enumeration.
 * @note   Read/Write 3-bit field (bits 26:24 of RCC_CFGR, MCO1PRE[2:0]) dividing the
 *         selected MCO1 clock before driving `PA8`.
 * @warning Ensure the divided MCO1 output frequency does not exceed the maximum I/O pin toggle frequency (**100 MHz**).
 */
typedef enum {
    PLAY32_RCC_CFGR_MCO1_PRESCALER_DIV_1 = 0U, /**< No division. */
    PLAY32_RCC_CFGR_MCO1_PRESCALER_DIV_2 = 4U, /**< Division by 2. */
    PLAY32_RCC_CFGR_MCO1_PRESCALER_DIV_3 = 5U, /**< Division by 3. */
    PLAY32_RCC_CFGR_MCO1_PRESCALER_DIV_4 = 6U, /**< Division by 4. */
    PLAY32_RCC_CFGR_MCO1_PRESCALER_DIV_5 = 7U  /**< Division by 5. */
} PLAY32_RCC_CFGR_MCO1Prescaler;

/**
 * @brief  Microcontroller clock output 2 prescaler (MCO2PRE) enumeration.
 * @note   Read/Write 3-bit field (bits 29:27 of RCC_CFGR, MCO2PRE[2:0]) dividing the
 *         selected MCO2 clock before driving `PC9`.
 * @warning Ensure the divided MCO2 output frequency does not exceed the maximum I/O pin toggle frequency (**100 MHz**).
 */
typedef enum {
    PLAY32_RCC_CFGR_MCO2_PRESCALER_DIV_1 = 0U, /**< No division. */
    PLAY32_RCC_CFGR_MCO2_PRESCALER_DIV_2 = 4U, /**< Division by 2. */
    PLAY32_RCC_CFGR_MCO2_PRESCALER_DIV_3 = 5U, /**< Division by 3. */
    PLAY32_RCC_CFGR_MCO2_PRESCALER_DIV_4 = 6U, /**< Division by 4. */
    PLAY32_RCC_CFGR_MCO2_PRESCALER_DIV_5 = 7U  /**< Division by 5. */
} PLAY32_RCC_CFGR_MCO2Prescaler;

/**
 * @brief  Microcontroller clock output 2 (MCO2) source selection enumeration.
 * @note   Read/Write 2-bit field (bits 31:30 of RCC_CFGR, MCO2[1:0]) selecting the clock
 *         signal output onto the `PC9` pin (when configured in AF0 mode).
 * @warning Clock switching on MCO2 may generate glitches; configure before enabling the output pin.
 * @see    PLAY32_RCC_CFGR_MCO2Prescaler
 */
typedef enum {
    PLAY32_RCC_CFGR_MCO2_SOURCE_SYSCLK = 0U, /**< System clock (SYSCLK) selected on MCO2 (PC9). */
    PLAY32_RCC_CFGR_MCO2_SOURCE_PLLI2S = 1U, /**< PLLI2S clock selected on MCO2 (PC9). */
    PLAY32_RCC_CFGR_MCO2_SOURCE_HSE    = 2U, /**< HSE oscillator clock selected on MCO2 (PC9). */
    PLAY32_RCC_CFGR_MCO2_SOURCE_PLL    = 3U  /**< Main PLL clock selected on MCO2 (PC9). */
} PLAY32_RCC_CFGR_MCO2Source;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_CFGR_Types */

/**
 * @defgroup PLAY32_RCC_CIR_Types RCC Clock Interrupt Register (RCC_CIR)
 * @brief Bit positions, masks, and interrupt flag/enable/clear types for RCC_CIR (offset 0x0C).
 * @{
 */
#pragma region RCC_CIR_REGISTER

#pragma region RCC_CIR_REGISTER_POSITION
/* Ready & Clock Security Interrupt Flags (Read-only) */
#define PLAY32_RCC_CIR_LSIRDYF_POS      (0U)  /**< Bit 0: LSI ready interrupt flag position. */
#define PLAY32_RCC_CIR_LSERDYF_POS      (1U)  /**< Bit 1: LSE ready interrupt flag position. */
#define PLAY32_RCC_CIR_HSIRDYF_POS      (2U)  /**< Bit 2: HSI ready interrupt flag position. */
#define PLAY32_RCC_CIR_HSERDYF_POS      (3U)  /**< Bit 3: HSE ready interrupt flag position. */
#define PLAY32_RCC_CIR_PLLRDYF_POS      (4U)  /**< Bit 4: Main PLL ready interrupt flag position. */
#define PLAY32_RCC_CIR_PLLI2SRDYF_POS   (5U)  /**< Bit 5: PLLI2S ready interrupt flag position. */
#define PLAY32_RCC_CIR_CSSF_POS         (7U)  /**< Bit 7: Clock security system interrupt flag position. */

/* Ready Interrupt Enables (Read/Write) */
#define PLAY32_RCC_CIR_LSIRDYIE_POS     (8U)  /**< Bit 8: LSI ready interrupt enable position. */
#define PLAY32_RCC_CIR_LSERDYIE_POS     (9U)  /**< Bit 9: LSE ready interrupt enable position. */
#define PLAY32_RCC_CIR_HSIRDYIE_POS     (10U) /**< Bit 10: HSI ready interrupt enable position. */
#define PLAY32_RCC_CIR_HSERDYIE_POS     (11U) /**< Bit 11: HSE ready interrupt enable position. */
#define PLAY32_RCC_CIR_PLLRDYIE_POS     (12U) /**< Bit 12: Main PLL ready interrupt enable position. */
#define PLAY32_RCC_CIR_PLLI2SRDYIE_POS  (13U) /**< Bit 13: PLLI2S ready interrupt enable position. */

/* Ready & Clock Security Interrupt Clears (Write-only) */
#define PLAY32_RCC_CIR_LSIRDYC_POS      (16U) /**< Bit 16: LSI ready interrupt clear position. */
#define PLAY32_RCC_CIR_LSERDYC_POS      (17U) /**< Bit 17: LSE ready interrupt clear position. */
#define PLAY32_RCC_CIR_HSIRDYC_POS      (18U) /**< Bit 18: HSI ready interrupt clear position. */
#define PLAY32_RCC_CIR_HSERDYC_POS      (19U) /**< Bit 19: HSE ready interrupt clear position. */
#define PLAY32_RCC_CIR_PLLRDYC_POS      (20U) /**< Bit 20: Main PLL ready interrupt clear position. */
#define PLAY32_RCC_CIR_PLLI2SRDYC_POS   (21U) /**< Bit 21: PLLI2S ready interrupt clear position. */
#define PLAY32_RCC_CIR_CSSC_POS         (23U) /**< Bit 23: Clock security system interrupt clear position. */
#pragma endregion

#pragma region RCC_CIR_REGISTER_MASK
#define PLAY32_RCC_CIR_LSIRDYF_MSK      (1UL << PLAY32_RCC_CIR_LSIRDYF_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_CIR_LSERDYF_MSK      (1UL << PLAY32_RCC_CIR_LSERDYF_POS)    /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_CIR_HSIRDYF_MSK      (1UL << PLAY32_RCC_CIR_HSIRDYF_POS)    /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_CIR_HSERDYF_MSK      (1UL << PLAY32_RCC_CIR_HSERDYF_POS)    /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_CIR_PLLRDYF_MSK      (1UL << PLAY32_RCC_CIR_PLLRDYF_POS)    /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_CIR_PLLI2SRDYF_MSK   (1UL << PLAY32_RCC_CIR_PLLI2SRDYF_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_RCC_CIR_CSSF_MSK         (1UL << PLAY32_RCC_CIR_CSSF_POS)       /**< Bit 7 mask (0x00000080). */

#define PLAY32_RCC_CIR_LSIRDYIE_MSK     (1UL << PLAY32_RCC_CIR_LSIRDYIE_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_RCC_CIR_LSERDYIE_MSK     (1UL << PLAY32_RCC_CIR_LSERDYIE_POS)   /**< Bit 9 mask (0x00000200). */
#define PLAY32_RCC_CIR_HSIRDYIE_MSK     (1UL << PLAY32_RCC_CIR_HSIRDYIE_POS)   /**< Bit 10 mask (0x00000400). */
#define PLAY32_RCC_CIR_HSERDYIE_MSK     (1UL << PLAY32_RCC_CIR_HSERDYIE_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_CIR_PLLRDYIE_MSK     (1UL << PLAY32_RCC_CIR_PLLRDYIE_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_CIR_PLLI2SRDYIE_MSK  (1UL << PLAY32_RCC_CIR_PLLI2SRDYIE_POS)/**< Bit 13 mask (0x00002000). */

#define PLAY32_RCC_CIR_LSIRDYC_MSK      (1UL << PLAY32_RCC_CIR_LSIRDYC_POS)    /**< Bit 16 mask (0x00010000). */
#define PLAY32_RCC_CIR_LSERDYC_MSK      (1UL << PLAY32_RCC_CIR_LSERDYC_POS)    /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_CIR_HSIRDYC_MSK      (1UL << PLAY32_RCC_CIR_HSIRDYC_POS)    /**< Bit 18 mask (0x00040000). */
#define PLAY32_RCC_CIR_HSERDYC_MSK      (1UL << PLAY32_RCC_CIR_HSERDYC_POS)    /**< Bit 19 mask (0x00080000). */
#define PLAY32_RCC_CIR_PLLRDYC_MSK      (1UL << PLAY32_RCC_CIR_PLLRDYC_POS)    /**< Bit 20 mask (0x00100000). */
#define PLAY32_RCC_CIR_PLLI2SRDYC_MSK   (1UL << PLAY32_RCC_CIR_PLLI2SRDYC_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_CIR_CSSC_MSK         (1UL << PLAY32_RCC_CIR_CSSC_POS)       /**< Bit 23 mask (0x00800000). */
#pragma endregion

#pragma region RCC_CIR_REGISTER_ENUM

/**
 * @brief  LSI ready interrupt flag (LSIRDYF) state type.
 * @note   Read-only status bit (bit 0 of RCC_CIR, LSIRDYF) set by hardware when the
 *         internal 32 kHz RC oscillator (LSI) becomes stable and `LSIRDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_LowSpeedInternalReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_LowSpeedInternalReadyInterruptFlag;

/**
 * @brief  LSE ready interrupt flag (LSERDYF) state type.
 * @note   Read-only status bit (bit 1 of RCC_CIR, LSERDYF) set by hardware when the
 *         external 32.768 kHz crystal oscillator (LSE) becomes stable and `LSERDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_LowSpeedExternalReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_LowSpeedExternalReadyInterruptFlag;

/**
 * @brief  HSI ready interrupt flag (HSIRDYF) state type.
 * @note   Read-only status bit (bit 2 of RCC_CIR, HSIRDYF) set by hardware when the
 *         16 MHz HSI oscillator becomes stable and `HSIRDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_HighSpeedInternalReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_HighSpeedInternalReadyInterruptFlag;

/**
 * @brief  HSE ready interrupt flag (HSERDYF) state type.
 * @note   Read-only status bit (bit 3 of RCC_CIR, HSERDYF) set by hardware when the
 *         external HSE oscillator becomes stable and `HSERDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_HighSpeedExternalReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_HighSpeedExternalReadyInterruptFlag;

/**
 * @brief  Main PLL ready interrupt flag (PLLRDYF) state type.
 * @note   Read-only status bit (bit 4 of RCC_CIR, PLLRDYF) set by hardware when the
 *         main system PLL locks and `PLLRDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_PhaseLockedLoopReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_PhaseLockedLoopReadyInterruptFlag;

/**
 * @brief  PLLI2S ready interrupt flag (PLLI2SRDYF) state type.
 * @note   Read-only status bit (bit 5 of RCC_CIR, PLLI2SRDYF) set by hardware when the
 *         dedicated audio PLL (PLLI2S) locks and `PLLI2SRDYIE` is set.
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_PhaseLockedLoopI2SReadyInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_PhaseLockedLoopI2SReadyInterruptFlag;

/**
 * @brief  Clock Security System interrupt flag (CSSF) state type.
 * @note   Read-only status bit (bit 7 of RCC_CIR, CSSF) set by hardware when a clock
 *         failure is detected on the HSE oscillator (triggers an NMI).
 * @warning Cleared by software setting @ref PLAY32_RCC_CIR_ClockSecuritySystemInterruptClear.
 * @see    PLAY32_RCC_Flag
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CIR_ClockSecuritySystemInterruptFlag;

/**
 * @brief  LSI ready interrupt enable (LSIRDYIE) state type.
 * @note   Read/Write control bit (bit 8 of RCC_CIR, LSIRDYIE) used to enable or disable
 *         the RCC interrupt request when the LSI oscillator becomes ready.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_LowSpeedInternalReadyInterruptEnable;

/**
 * @brief  LSE ready interrupt enable (LSERDYIE) state type.
 * @note   Read/Write control bit (bit 9 of RCC_CIR, LSERDYIE) used to enable or disable
 *         the RCC interrupt request when the LSE oscillator becomes ready.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_LowSpeedExternalReadyInterruptEnable;

/**
 * @brief  HSI ready interrupt enable (HSIRDYIE) state type.
 * @note   Read/Write control bit (bit 10 of RCC_CIR, HSIRDYIE) used to enable or disable
 *         the RCC interrupt request when the HSI oscillator becomes ready.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_HighSpeedInternalReadyInterruptEnable;

/**
 * @brief  HSE ready interrupt enable (HSERDYIE) state type.
 * @note   Read/Write control bit (bit 11 of RCC_CIR, HSERDYIE) used to enable or disable
 *         the RCC interrupt request when the HSE oscillator becomes ready.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_HighSpeedExternalReadyInterruptEnable;

/**
 * @brief  Main PLL ready interrupt enable (PLLRDYIE) state type.
 * @note   Read/Write control bit (bit 12 of RCC_CIR, PLLRDYIE) used to enable or disable
 *         the RCC interrupt request when the main PLL locks.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_PhaseLockedLoopReadyInterruptEnable;

/**
 * @brief  PLLI2S ready interrupt enable (PLLI2SRDYIE) state type.
 * @note   Read/Write control bit (bit 13 of RCC_CIR, PLLI2SRDYIE) used to enable or disable
 *         the RCC interrupt request when PLLI2S locks.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_PhaseLockedLoopI2SReadyInterruptEnable;

/**
 * @brief  LSI ready interrupt clear (LSIRDYC) control type.
 * @note   Write-only self-clearing bit (bit 16 of RCC_CIR, LSIRDYC) set by software to clear `LSIRDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_LowSpeedInternalReadyInterruptClear;

/**
 * @brief  LSE ready interrupt clear (LSERDYC) control type.
 * @note   Write-only self-clearing bit (bit 17 of RCC_CIR, LSERDYC) set by software to clear `LSERDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_LowSpeedExternalReadyInterruptClear;

/**
 * @brief  HSI ready interrupt clear (HSIRDYC) control type.
 * @note   Write-only self-clearing bit (bit 18 of RCC_CIR, HSIRDYC) set by software to clear `HSIRDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_HighSpeedInternalReadyInterruptClear;

/**
 * @brief  HSE ready interrupt clear (HSERDYC) control type.
 * @note   Write-only self-clearing bit (bit 19 of RCC_CIR, HSERDYC) set by software to clear `HSERDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_HighSpeedExternalReadyInterruptClear;

/**
 * @brief  Main PLL ready interrupt clear (PLLRDYC) control type.
 * @note   Write-only self-clearing bit (bit 20 of RCC_CIR, PLLRDYC) set by software to clear `PLLRDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_PhaseLockedLoopReadyInterruptClear;

/**
 * @brief  PLLI2S ready interrupt clear (PLLI2SRDYC) control type.
 * @note   Write-only self-clearing bit (bit 21 of RCC_CIR, PLLI2SRDYC) set by software to clear `PLLI2SRDYF`.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_PhaseLockedLoopI2SReadyInterruptClear;

/**
 * @brief  Clock Security System interrupt clear (CSSC) control type.
 * @note   Write-only self-clearing bit (bit 23 of RCC_CIR, CSSC) set by software to clear `CSSF`
 *         inside the NMI handler after an HSE clock failure.
 * @warning Reading this bit always returns 0.
 * @see    PLAY32_RCC_Switch
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_CIR_ClockSecuritySystemInterruptClear;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_CIR_Types */

/**
 * @defgroup PLAY32_RCC_AHB1RSTR_Types RCC AHB1 Peripheral Reset Register (RCC_AHB1RSTR)
 * @brief Bit positions, masks, and reset control types for RCC_AHB1RSTR (offset 0x10).
 * @{
 */
#pragma region RCC_AHB1RSTR_REGISTER

#pragma region RCC_AHB1RSTR_REGISTER_POSITION
#define PLAY32_RCC_AHB1RSTR_GPIOARST_POS    (0U)  /**< Bit 0: IO port A reset position. */
#define PLAY32_RCC_AHB1RSTR_GPIOBRST_POS    (1U)  /**< Bit 1: IO port B reset position. */
#define PLAY32_RCC_AHB1RSTR_GPIOCRST_POS    (2U)  /**< Bit 2: IO port C reset position. */
#define PLAY32_RCC_AHB1RSTR_GPIODRST_POS    (3U)  /**< Bit 3: IO port D reset position. */
#define PLAY32_RCC_AHB1RSTR_GPIOERST_POS    (4U)  /**< Bit 4: IO port E reset position. */
#define PLAY32_RCC_AHB1RSTR_GPIOHRST_POS    (7U)  /**< Bit 7: IO port H reset position. */
#define PLAY32_RCC_AHB1RSTR_CRCRST_POS      (12U) /**< Bit 12: CRC reset position. */
#define PLAY32_RCC_AHB1RSTR_DMA1RST_POS     (21U) /**< Bit 21: DMA1 reset position. */
#define PLAY32_RCC_AHB1RSTR_DMA2RST_POS     (22U) /**< Bit 22: DMA2 reset position. */
#pragma endregion

#pragma region RCC_AHB1RSTR_REGISTER_MASK
#define PLAY32_RCC_AHB1RSTR_GPIOARST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIOARST_POS) /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_AHB1RSTR_GPIOBRST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIOBRST_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_AHB1RSTR_GPIOCRST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIOCRST_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_AHB1RSTR_GPIODRST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIODRST_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_AHB1RSTR_GPIOERST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIOERST_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_AHB1RSTR_GPIOHRST_MSK    (1UL << PLAY32_RCC_AHB1RSTR_GPIOHRST_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_RCC_AHB1RSTR_CRCRST_MSK      (1UL << PLAY32_RCC_AHB1RSTR_CRCRST_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_AHB1RSTR_DMA1RST_MSK     (1UL << PLAY32_RCC_AHB1RSTR_DMA1RST_POS)  /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_AHB1RSTR_DMA2RST_MSK     (1UL << PLAY32_RCC_AHB1RSTR_DMA2RST_POS)  /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region RCC_AHB1RSTR_REGISTER_ENUM

/**
 * @brief  IO port A reset (GPIOARST) control type.
 * @note   Read/Write control bit (bit 0 of RCC_AHB1RSTR, GPIOARST) used to reset the GPIOA peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIOAReset;

/**
 * @brief  IO port B reset (GPIOBRST) control type.
 * @note   Read/Write control bit (bit 1 of RCC_AHB1RSTR, GPIOBRST) used to reset the GPIOB peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIOBReset;

/**
 * @brief  IO port C reset (GPIOCRST) control type.
 * @note   Read/Write control bit (bit 2 of RCC_AHB1RSTR, GPIOCRST) used to reset the GPIOC peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIOCReset;

/**
 * @brief  IO port D reset (GPIODRST) control type.
 * @note   Read/Write control bit (bit 3 of RCC_AHB1RSTR, GPIODRST) used to reset the GPIOD peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIODReset;

/**
 * @brief  IO port E reset (GPIOERST) control type.
 * @note   Read/Write control bit (bit 4 of RCC_AHB1RSTR, GPIOERST) used to reset the GPIOE peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIOEReset;

/**
 * @brief  IO port H reset (GPIOHRST) control type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB1RSTR, GPIOHRST) used to reset the GPIOH peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_GPIOHReset;

/**
 * @brief  CRC calculation unit reset (CRCRST) control type.
 * @note   Read/Write control bit (bit 12 of RCC_AHB1RSTR, CRCRST) used to reset the CRC peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_CRCReset;

/**
 * @brief  DMA1 controller reset (DMA1RST) control type.
 * @note   Read/Write control bit (bit 21 of RCC_AHB1RSTR, DMA1RST) used to reset the DMA1 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_DMA1Reset;

/**
 * @brief  DMA2 controller reset (DMA2RST) control type.
 * @note   Read/Write control bit (bit 22 of RCC_AHB1RSTR, DMA2RST) used to reset the DMA2 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB1RSTR_DMA2Reset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_AHB1RSTR_Types */


/**
 * @defgroup PLAY32_RCC_AHB2RSTR_Types RCC AHB2 Peripheral Reset Register (RCC_AHB2RSTR)
 * @brief Bit position, mask, and reset control type for RCC_AHB2RSTR (offset 0x14).
 * @{
 */
#pragma region RCC_AHB2RSTR_REGISTER

#pragma region RCC_AHB2RSTR_REGISTER_POSITION
#define PLAY32_RCC_AHB2RSTR_OTGFSRST_POS    (7U) /**< Bit 7: USB OTG FS module reset position. */
#pragma endregion

#pragma region RCC_AHB2RSTR_REGISTER_MASK
#define PLAY32_RCC_AHB2RSTR_OTGFSRST_MSK    (1UL << PLAY32_RCC_AHB2RSTR_OTGFSRST_POS) /**< Bit 7 mask (0x00000080). */
#pragma endregion

#pragma region RCC_AHB2RSTR_REGISTER_ENUM

/**
 * @brief  USB OTG FS module reset (OTGFSRST) control type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB2RSTR, OTGFSRST) used to reset the
 *         USB On-The-Go Full-Speed peripheral. All other bits in `RCC_AHB2RSTR` are reserved on STM32F401.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_AHB2RSTR_OTGFSReset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_AHB2RSTR_Types */

/**
 * @defgroup PLAY32_RCC_APB1RSTR_Types RCC APB1 Peripheral Reset Register (RCC_APB1RSTR)
 * @brief Bit positions, masks, and reset control types for RCC_APB1RSTR (offset 0x20).
 * @{
 */
#pragma region RCC_APB1RSTR_REGISTER

#pragma region RCC_APB1RSTR_REGISTER_POSITION
#define PLAY32_RCC_APB1RSTR_TIM2RST_POS      (0U)  /**< Bit 0: TIM2 reset position. */
#define PLAY32_RCC_APB1RSTR_TIM3RST_POS      (1U)  /**< Bit 1: TIM3 reset position. */
#define PLAY32_RCC_APB1RSTR_TIM4RST_POS      (2U)  /**< Bit 2: TIM4 reset position. */
#define PLAY32_RCC_APB1RSTR_TIM5RST_POS      (3U)  /**< Bit 3: TIM5 reset position. */
#define PLAY32_RCC_APB1RSTR_WWDGRST_POS      (11U) /**< Bit 11: Window watchdog reset position. */
#define PLAY32_RCC_APB1RSTR_SPI2RST_POS      (14U) /**< Bit 14: SPI2 reset position. */
#define PLAY32_RCC_APB1RSTR_SPI3RST_POS      (15U) /**< Bit 15: SPI3 reset position. */
#define PLAY32_RCC_APB1RSTR_USART2RST_POS    (17U) /**< Bit 17: USART2 reset position. */
#define PLAY32_RCC_APB1RSTR_I2C1RST_POS      (21U) /**< Bit 21: I2C1 reset position. */
#define PLAY32_RCC_APB1RSTR_I2C2RST_POS      (22U) /**< Bit 22: I2C2 reset position. */
#define PLAY32_RCC_APB1RSTR_I2C3RST_POS      (23U) /**< Bit 23: I2C3 reset position. */
#define PLAY32_RCC_APB1RSTR_PWRRST_POS       (28U) /**< Bit 28: Power interface reset position. */
#pragma endregion

#pragma region RCC_APB1RSTR_REGISTER_MASK
#define PLAY32_RCC_APB1RSTR_TIM2RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_TIM2RST_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB1RSTR_TIM3RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_TIM3RST_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_APB1RSTR_TIM4RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_TIM4RST_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_APB1RSTR_TIM5RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_TIM5RST_POS)   /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_APB1RSTR_WWDGRST_MSK      (1UL << PLAY32_RCC_APB1RSTR_WWDGRST_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB1RSTR_SPI2RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_SPI2RST_POS)   /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB1RSTR_SPI3RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_SPI3RST_POS)   /**< Bit 15 mask (0x00008000). */
#define PLAY32_RCC_APB1RSTR_USART2RST_MSK    (1UL << PLAY32_RCC_APB1RSTR_USART2RST_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB1RSTR_I2C1RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_I2C1RST_POS)   /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_APB1RSTR_I2C2RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_I2C2RST_POS)   /**< Bit 22 mask (0x00400000). */
#define PLAY32_RCC_APB1RSTR_I2C3RST_MSK      (1UL << PLAY32_RCC_APB1RSTR_I2C3RST_POS)   /**< Bit 23 mask (0x00800000). */
#define PLAY32_RCC_APB1RSTR_PWRRST_MSK       (1UL << PLAY32_RCC_APB1RSTR_PWRRST_POS)    /**< Bit 28 mask (0x10000000). */
#pragma endregion

#pragma region RCC_APB1RSTR_REGISTER_ENUM

/**
 * @brief  TIM2 peripheral reset (TIM2RST) control type.
 * @note   Read/Write control bit (bit 0 of RCC_APB1RSTR, TIM2RST) used to reset the TIM2 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_TIM2Reset;

/**
 * @brief  TIM3 peripheral reset (TIM3RST) control type.
 * @note   Read/Write control bit (bit 1 of RCC_APB1RSTR, TIM3RST) used to reset the TIM3 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_TIM3Reset;

/**
 * @brief  TIM4 peripheral reset (TIM4RST) control type.
 * @note   Read/Write control bit (bit 2 of RCC_APB1RSTR, TIM4RST) used to reset the TIM4 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_TIM4Reset;

/**
 * @brief  TIM5 peripheral reset (TIM5RST) control type.
 * @note   Read/Write control bit (bit 3 of RCC_APB1RSTR, TIM5RST) used to reset the TIM5 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_TIM5Reset;

/**
 * @brief  Window watchdog reset (WWDGRST) control type.
 * @note   Read/Write control bit (bit 11 of RCC_APB1RSTR, WWDGRST) used to reset the WWDG peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_WWDGReset;

/**
 * @brief  SPI2 peripheral reset (SPI2RST) control type.
 * @note   Read/Write control bit (bit 14 of RCC_APB1RSTR, SPI2RST) used to reset the SPI2/I2S2 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_SPI2Reset;

/**
 * @brief  SPI3 peripheral reset (SPI3RST) control type.
 * @note   Read/Write control bit (bit 15 of RCC_APB1RSTR, SPI3RST) used to reset the SPI3/I2S3 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_SPI3Reset;

/**
 * @brief  USART2 peripheral reset (USART2RST) control type.
 * @note   Read/Write control bit (bit 17 of RCC_APB1RSTR, USART2RST) used to reset the USART2 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_USART2Reset;

/**
 * @brief  I2C1 peripheral reset (I2C1RST) control type.
 * @note   Read/Write control bit (bit 21 of RCC_APB1RSTR, I2C1RST) used to reset the I2C1 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_I2C1Reset;

/**
 * @brief  I2C2 peripheral reset (I2C2RST) control type.
 * @note   Read/Write control bit (bit 22 of RCC_APB1RSTR, I2C2RST) used to reset the I2C2 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_I2C2Reset;

/**
 * @brief  I2C3 peripheral reset (I2C3RST) control type.
 * @note   Read/Write control bit (bit 23 of RCC_APB1RSTR, I2C3RST) used to reset the I2C3 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_I2C3Reset;

/**
 * @brief  Power interface reset (PWRRST) control type.
 * @note   Read/Write control bit (bit 28 of RCC_APB1RSTR, PWRRST) used to reset the PWR peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB1RSTR_PWRReset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_APB1RSTR_Types */

/**
 * @defgroup PLAY32_RCC_APB2RSTR_Types RCC APB2 Peripheral Reset Register (RCC_APB2RSTR)
 * @brief Bit positions, masks, and reset control types for RCC_APB2RSTR (offset 0x24).
 * @{
 */
#pragma region RCC_APB2RSTR_REGISTER

#pragma region RCC_APB2RSTR_REGISTER_POSITION
#define PLAY32_RCC_APB2RSTR_TIM1RST_POS      (0U)  /**< Bit 0: TIM1 reset position. */
#define PLAY32_RCC_APB2RSTR_USART1RST_POS    (4U)  /**< Bit 4: USART1 reset position. */
#define PLAY32_RCC_APB2RSTR_USART6RST_POS    (5U)  /**< Bit 5: USART6 reset position. */
#define PLAY32_RCC_APB2RSTR_ADC1RST_POS      (8U)  /**< Bit 8: ADC1 interface reset position. */
#define PLAY32_RCC_APB2RSTR_SDIORST_POS      (11U) /**< Bit 11: SDIO reset position. */
#define PLAY32_RCC_APB2RSTR_SPI1RST_POS      (12U) /**< Bit 12: SPI1 reset position. */
#define PLAY32_RCC_APB2RSTR_SPI4RST_POS      (13U) /**< Bit 13: SPI4 reset position. */
#define PLAY32_RCC_APB2RSTR_SYSCFGRST_POS    (14U) /**< Bit 14: System configuration controller reset position. */
#define PLAY32_RCC_APB2RSTR_TIM9RST_POS      (16U) /**< Bit 16: TIM9 reset position. */
#define PLAY32_RCC_APB2RSTR_TIM10RST_POS     (17U) /**< Bit 17: TIM10 reset position. */
#define PLAY32_RCC_APB2RSTR_TIM11RST_POS     (18U) /**< Bit 18: TIM11 reset position. */
#pragma endregion

#pragma region RCC_APB2RSTR_REGISTER_MASK
#define PLAY32_RCC_APB2RSTR_TIM1RST_MSK      (1UL << PLAY32_RCC_APB2RSTR_TIM1RST_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB2RSTR_USART1RST_MSK    (1UL << PLAY32_RCC_APB2RSTR_USART1RST_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_APB2RSTR_USART6RST_MSK    (1UL << PLAY32_RCC_APB2RSTR_USART6RST_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_RCC_APB2RSTR_ADC1RST_MSK      (1UL << PLAY32_RCC_APB2RSTR_ADC1RST_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_RCC_APB2RSTR_SDIORST_MSK      (1UL << PLAY32_RCC_APB2RSTR_SDIORST_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB2RSTR_SPI1RST_MSK      (1UL << PLAY32_RCC_APB2RSTR_SPI1RST_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_APB2RSTR_SPI4RST_MSK      (1UL << PLAY32_RCC_APB2RSTR_SPI4RST_POS)   /**< Bit 13 mask (0x00002000). */
#define PLAY32_RCC_APB2RSTR_SYSCFGRST_MSK    (1UL << PLAY32_RCC_APB2RSTR_SYSCFGRST_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB2RSTR_TIM9RST_MSK      (1UL << PLAY32_RCC_APB2RSTR_TIM9RST_POS)   /**< Bit 16 mask (0x00010000). */
#define PLAY32_RCC_APB2RSTR_TIM10RST_MSK     (1UL << PLAY32_RCC_APB2RSTR_TIM10RST_POS)  /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB2RSTR_TIM11RST_MSK     (1UL << PLAY32_RCC_APB2RSTR_TIM11RST_POS)  /**< Bit 18 mask (0x00040000). */
#pragma endregion

#pragma region RCC_APB2RSTR_REGISTER_ENUM

/**
 * @brief  TIM1 peripheral reset (TIM1RST) control type.
 * @note   Read/Write control bit (bit 0 of RCC_APB2RSTR, TIM1RST) used to reset the TIM1 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_TIM1Reset;

/**
 * @brief  USART1 peripheral reset (USART1RST) control type.
 * @note   Read/Write control bit (bit 4 of RCC_APB2RSTR, USART1RST) used to reset the USART1 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_USART1Reset;

/**
 * @brief  USART6 peripheral reset (USART6RST) control type.
 * @note   Read/Write control bit (bit 5 of RCC_APB2RSTR, USART6RST) used to reset the USART6 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_USART6Reset;

/**
 * @brief  ADC1 interface reset (ADC1RST) control type.
 * @note   Read/Write control bit (bit 8 of RCC_APB2RSTR, ADC1RST) used to reset the ADC1 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_ADC1Reset;

/**
 * @brief  SDIO peripheral reset (SDIORST) control type.
 * @note   Read/Write control bit (bit 11 of RCC_APB2RSTR, SDIORST) used to reset the SDIO module.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_SDIOReset;

/**
 * @brief  SPI1 peripheral reset (SPI1RST) control type.
 * @note   Read/Write control bit (bit 12 of RCC_APB2RSTR, SPI1RST) used to reset the SPI1/I2S1 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_SPI1Reset;

/**
 * @brief  SPI4 peripheral reset (SPI4RST) control type.
 * @note   Read/Write control bit (bit 13 of RCC_APB2RSTR, SPI4RST) used to reset the SPI4/I2S4 peripheral.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_SPI4Reset;

/**
 * @brief  System configuration controller reset (SYSCFGRST) control type.
 * @note   Read/Write control bit (bit 14 of RCC_APB2RSTR, SYSCFGRST) used to reset the SYSCFG controller.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_SYSCFGReset;

/**
 * @brief  TIM9 peripheral reset (TIM9RST) control type.
 * @note   Read/Write control bit (bit 16 of RCC_APB2RSTR, TIM9RST) used to reset the TIM9 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_TIM9Reset;

/**
 * @brief  TIM10 peripheral reset (TIM10RST) control type.
 * @note   Read/Write control bit (bit 17 of RCC_APB2RSTR, TIM10RST) used to reset the TIM10 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_TIM10Reset;

/**
 * @brief  TIM11 peripheral reset (TIM11RST) control type.
 * @note   Read/Write control bit (bit 18 of RCC_APB2RSTR, TIM11RST) used to reset the TIM11 timer.
 * @warning Not self-clearing; write @ref PLAY32_RCC_KEEP (0) after asserting @ref PLAY32_RCC_RESET (1).
 * @see    PLAY32_RCC_Reset
 */
typedef PLAY32_RCC_Reset PLAY32_RCC_APB2RSTR_TIM11Reset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_APB2RSTR_Types */

/**
 * @defgroup PLAY32_RCC_AHB1ENR_Types RCC AHB1 Peripheral Clock Enable Register (RCC_AHB1ENR)
 * @brief Bit positions, masks, and clock enable types for RCC_AHB1ENR (offset 0x30).
 * @{
 */
#pragma region RCC_AHB1ENR_REGISTER

#pragma region RCC_AHB1ENR_REGISTER_POSITION
#define PLAY32_RCC_AHB1ENR_GPIOAEN_POS     (0U)  /**< Bit 0: IO port A clock enable position. */
#define PLAY32_RCC_AHB1ENR_GPIOBEN_POS     (1U)  /**< Bit 1: IO port B clock enable position. */
#define PLAY32_RCC_AHB1ENR_GPIOCEN_POS     (2U)  /**< Bit 2: IO port C clock enable position. */
#define PLAY32_RCC_AHB1ENR_GPIODEN_POS     (3U)  /**< Bit 3: IO port D clock enable position. */
#define PLAY32_RCC_AHB1ENR_GPIOEEN_POS     (4U)  /**< Bit 4: IO port E clock enable position. */
#define PLAY32_RCC_AHB1ENR_GPIOHEN_POS     (7U)  /**< Bit 7: IO port H clock enable position. */
#define PLAY32_RCC_AHB1ENR_CRCEN_POS       (12U) /**< Bit 12: CRC clock enable position. */
#define PLAY32_RCC_AHB1ENR_DMA1EN_POS      (21U) /**< Bit 21: DMA1 clock enable position. */
#define PLAY32_RCC_AHB1ENR_DMA2EN_POS      (22U) /**< Bit 22: DMA2 clock enable position. */
#pragma endregion

#pragma region RCC_AHB1ENR_REGISTER_MASK
#define PLAY32_RCC_AHB1ENR_GPIOAEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOAEN_POS) /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_AHB1ENR_GPIOBEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOBEN_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_AHB1ENR_GPIOCEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOCEN_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_AHB1ENR_GPIODEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIODEN_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_AHB1ENR_GPIOEEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOEEN_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_AHB1ENR_GPIOHEN_MSK     (1UL << PLAY32_RCC_AHB1ENR_GPIOHEN_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_RCC_AHB1ENR_CRCEN_MSK       (1UL << PLAY32_RCC_AHB1ENR_CRCEN_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_AHB1ENR_DMA1EN_MSK      (1UL << PLAY32_RCC_AHB1ENR_DMA1EN_POS)  /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_AHB1ENR_DMA2EN_MSK      (1UL << PLAY32_RCC_AHB1ENR_DMA2EN_POS)  /**< Bit 22 mask (0x00400000). */
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
/** @} */ /* End of PLAY32_RCC_AHB1ENR_Types */

/**
 * @defgroup PLAY32_RCC_AHB2ENR_Types RCC AHB2 Peripheral Clock Enable Register (RCC_AHB2ENR)
 * @brief Bit position, mask, and clock enable type for RCC_AHB2ENR (offset 0x34).
 * @{
 */
#pragma region RCC_AHB2ENR_REGISTER

#pragma region RCC_AHB2ENR_REGISTER_POSITION
#define PLAY32_RCC_AHB2ENR_OTGFSEN_POS     (7U) /**< Bit 7: USB OTG FS clock enable position. */
#pragma endregion

#pragma region RCC_AHB2ENR_REGISTER_MASK
#define PLAY32_RCC_AHB2ENR_OTGFSEN_MSK     (1UL << PLAY32_RCC_AHB2ENR_OTGFSEN_POS) /**< Bit 7 mask (0x00000080). */
#pragma endregion

#pragma region RCC_AHB2ENR_REGISTER_ENUM

/**
 * @brief  USB OTG Full-Speed (OTG_FS) clock enable state type.
 * @note   Read/Write control bit (bit 7 of RCC_AHB2ENR, OTGFSEN) used to enable or disable
 *         the AHB2 bus clock for the USB On-The-Go Full-Speed peripheral.
 * @warning Requires a dedicated 48 MHz clock generated by the main PLL (via PLLQ)
 *          to operate properly. A 2-cycle bus delay is required after enabling.
 * @see    PLAY32_RCC_Switch
 * @see    PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainQDivider
 */
typedef PLAY32_RCC_Switch PLAY32_RCC_AHB2ENR_USBOneTheGoFullSpeedEnable;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_AHB2ENR_Types */

/**
 * @defgroup PLAY32_RCC_APB1ENR_Types RCC APB1 Peripheral Clock Enable Register (RCC_APB1ENR)
 * @brief Bit positions, masks, and clock enable types for RCC_APB1ENR (offset 0x40).
 * @{
 */
#pragma region RCC_APB1ENR_REGISTER

#pragma region RCC_APB1ENR_REGISTER_POSITION
#define PLAY32_RCC_APB1ENR_TIM2EN_POS      (0U)  /**< Bit 0: TIM2 clock enable position. */
#define PLAY32_RCC_APB1ENR_TIM3EN_POS      (1U)  /**< Bit 1: TIM3 clock enable position. */
#define PLAY32_RCC_APB1ENR_TIM4EN_POS      (2U)  /**< Bit 2: TIM4 clock enable position. */
#define PLAY32_RCC_APB1ENR_TIM5EN_POS      (3U)  /**< Bit 3: TIM5 clock enable position. */
#define PLAY32_RCC_APB1ENR_WWDGEN_POS      (11U) /**< Bit 11: Window watchdog clock enable position. */
#define PLAY32_RCC_APB1ENR_SPI2EN_POS      (14U) /**< Bit 14: SPI2 clock enable position. */
#define PLAY32_RCC_APB1ENR_SPI3EN_POS      (15U) /**< Bit 15: SPI3 clock enable position. */
#define PLAY32_RCC_APB1ENR_USART2EN_POS    (17U) /**< Bit 17: USART2 clock enable position. */
#define PLAY32_RCC_APB1ENR_I2C1EN_POS      (21U) /**< Bit 21: I2C1 clock enable position. */
#define PLAY32_RCC_APB1ENR_I2C2EN_POS      (22U) /**< Bit 22: I2C2 clock enable position. */
#define PLAY32_RCC_APB1ENR_I2C3EN_POS      (23U) /**< Bit 23: I2C3 clock enable position. */
#define PLAY32_RCC_APB1ENR_PWREN_POS       (28U) /**< Bit 28: Power interface clock enable position. */
#pragma endregion

#pragma region RCC_APB1ENR_REGISTER_MASK
#define PLAY32_RCC_APB1ENR_TIM2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM2EN_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB1ENR_TIM3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM3EN_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_APB1ENR_TIM4EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM4EN_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_APB1ENR_TIM5EN_MSK      (1UL << PLAY32_RCC_APB1ENR_TIM5EN_POS)   /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_APB1ENR_WWDGEN_MSK      (1UL << PLAY32_RCC_APB1ENR_WWDGEN_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB1ENR_SPI2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_SPI2EN_POS)   /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB1ENR_SPI3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_SPI3EN_POS)   /**< Bit 15 mask (0x00008000). */
#define PLAY32_RCC_APB1ENR_USART2EN_MSK    (1UL << PLAY32_RCC_APB1ENR_USART2EN_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB1ENR_I2C1EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C1EN_POS)   /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_APB1ENR_I2C2EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C2EN_POS)   /**< Bit 22 mask (0x00400000). */
#define PLAY32_RCC_APB1ENR_I2C3EN_MSK      (1UL << PLAY32_RCC_APB1ENR_I2C3EN_POS)   /**< Bit 23 mask (0x00800000). */
#define PLAY32_RCC_APB1ENR_PWREN_MSK       (1UL << PLAY32_RCC_APB1ENR_PWREN_POS)    /**< Bit 28 mask (0x10000000). */
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
/** @} */ /* End of PLAY32_RCC_APB1ENR_Types */

/**
 * @defgroup PLAY32_RCC_APB2ENR_Types RCC APB2 Peripheral Clock Enable Register (RCC_APB2ENR)
 * @brief Bit positions, masks, and clock enable types for RCC_APB2ENR (offset 0x44).
 * @{
 */
#pragma region RCC_APB2ENR_REGISTER

#pragma region RCC_APB2ENR_REGISTER_POSITION
#define PLAY32_RCC_APB2ENR_TIM1EN_POS      (0U)  /**< Bit 0: TIM1 clock enable position. */
#define PLAY32_RCC_APB2ENR_USART1EN_POS    (4U)  /**< Bit 4: USART1 clock enable position. */
#define PLAY32_RCC_APB2ENR_USART6EN_POS    (5U)  /**< Bit 5: USART6 clock enable position. */
#define PLAY32_RCC_APB2ENR_ADC1EN_POS      (8U)  /**< Bit 8: ADC1 clock enable position. */
#define PLAY32_RCC_APB2ENR_SDIOEN_POS      (11U) /**< Bit 11: SDIO clock enable position. */
#define PLAY32_RCC_APB2ENR_SPI1EN_POS      (12U) /**< Bit 12: SPI1 clock enable position. */
#define PLAY32_RCC_APB2ENR_SPI4EN_POS      (13U) /**< Bit 13: SPI4 clock enable position. */
#define PLAY32_RCC_APB2ENR_SYSCFGEN_POS    (14U) /**< Bit 14: System configuration controller clock enable position. */
#define PLAY32_RCC_APB2ENR_TIM9EN_POS      (16U) /**< Bit 16: TIM9 clock enable position. */
#define PLAY32_RCC_APB2ENR_TIM10EN_POS     (17U) /**< Bit 17: TIM10 clock enable position. */
#define PLAY32_RCC_APB2ENR_TIM11EN_POS     (18U) /**< Bit 18: TIM11 clock enable position. */
#pragma endregion

#pragma region RCC_APB2ENR_REGISTER_MASK
#define PLAY32_RCC_APB2ENR_TIM1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_TIM1EN_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB2ENR_USART1EN_MSK    (1UL << PLAY32_RCC_APB2ENR_USART1EN_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_APB2ENR_USART6EN_MSK    (1UL << PLAY32_RCC_APB2ENR_USART6EN_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_RCC_APB2ENR_ADC1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_ADC1EN_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_RCC_APB2ENR_SDIOEN_MSK      (1UL << PLAY32_RCC_APB2ENR_SDIOEN_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB2ENR_SPI1EN_MSK      (1UL << PLAY32_RCC_APB2ENR_SPI1EN_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_APB2ENR_SPI4EN_MSK      (1UL << PLAY32_RCC_APB2ENR_SPI4EN_POS)   /**< Bit 13 mask (0x00002000). */
#define PLAY32_RCC_APB2ENR_SYSCFGEN_MSK    (1UL << PLAY32_RCC_APB2ENR_SYSCFGEN_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB2ENR_TIM9EN_MSK      (1UL << PLAY32_RCC_APB2ENR_TIM9EN_POS)   /**< Bit 16 mask (0x00010000). */
#define PLAY32_RCC_APB2ENR_TIM10EN_MSK     (1UL << PLAY32_RCC_APB2ENR_TIM10EN_POS)  /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB2ENR_TIM11EN_MSK     (1UL << PLAY32_RCC_APB2ENR_TIM11EN_POS)  /**< Bit 18 mask (0x00040000). */
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
 * @see    PLAY32_RCC_PLLCFGR_PhaseLockedLoopMainQDivider
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
/** @} */ /* End of PLAY32_RCC_APB2ENR_Types */

/**
 * @defgroup PLAY32_RCC_AHB1LPENR_Types RCC AHB1 Peripheral Clock Enable in Low-Power Mode Register (RCC_AHB1LPENR)
 * @brief Bit positions, masks, and Sleep-mode clock enable types for RCC_AHB1LPENR (offset 0x50).
 * @{
 */
#pragma region RCC_AHB1LPENR_REGISTER

#pragma region RCC_AHB1LPENR_REGISTER_POSITION
#define PLAY32_RCC_AHB1LPENR_GPIOALPEN_POS     (0U)  /**< Bit 0: IO port A clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_GPIOBLPEN_POS     (1U)  /**< Bit 1: IO port B clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_GPIOCLPEN_POS     (2U)  /**< Bit 2: IO port C clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_GPIODLPEN_POS     (3U)  /**< Bit 3: IO port D clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_GPIOELPEN_POS     (4U)  /**< Bit 4: IO port E clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_GPIOHLPEN_POS     (7U)  /**< Bit 7: IO port H clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_CRCLPEN_POS       (12U) /**< Bit 12: CRC clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_DMA1LPEN_POS      (21U) /**< Bit 21: DMA1 clock enable during Sleep mode position. */
#define PLAY32_RCC_AHB1LPENR_DMA2LPEN_POS      (22U) /**< Bit 22: DMA2 clock enable during Sleep mode position. */
#pragma endregion

#pragma region RCC_AHB1LPENR_REGISTER_MASK
#define PLAY32_RCC_AHB1LPENR_GPIOALPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOALPEN_POS) /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_AHB1LPENR_GPIOBLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOBLPEN_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_AHB1LPENR_GPIOCLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOCLPEN_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_AHB1LPENR_GPIODLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIODLPEN_POS) /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_AHB1LPENR_GPIOELPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOELPEN_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_AHB1LPENR_GPIOHLPEN_MSK     (1UL << PLAY32_RCC_AHB1LPENR_GPIOHLPEN_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_RCC_AHB1LPENR_CRCLPEN_MSK       (1UL << PLAY32_RCC_AHB1LPENR_CRCLPEN_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_AHB1LPENR_DMA1LPEN_MSK      (1UL << PLAY32_RCC_AHB1LPENR_DMA1LPEN_POS)  /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_AHB1LPENR_DMA2LPEN_MSK      (1UL << PLAY32_RCC_AHB1LPENR_DMA2LPEN_POS)  /**< Bit 22 mask (0x00400000). */
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
/** @} */ /* End of PLAY32_RCC_AHB1LPENR_Types */

/**
 * @defgroup PLAY32_RCC_AHB2LPENR_Types RCC AHB2 Peripheral Clock Enable in Low-Power Mode Register (RCC_AHB2LPENR)
 * @brief Bit position, mask, and Sleep-mode clock enable type for RCC_AHB2LPENR (offset 0x54).
 * @{
 */
#pragma region RCC_AHB2LPENR_REGISTER

#pragma region RCC_AHB2LPENR_REGISTER_POSITION
#define PLAY32_RCC_AHB2LPENR_OTGFSLPEN_POS     (7U) /**< Bit 7: USB OTG FS clock enable during Sleep mode position. */
#pragma endregion

#pragma region RCC_AHB2LPENR_REGISTER_MASK
#define PLAY32_RCC_AHB2LPENR_OTGFSLPEN_MSK     (1UL << PLAY32_RCC_AHB2LPENR_OTGFSLPEN_POS) /**< Bit 7 mask (0x00000080). */
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
/** @} */ /* End of PLAY32_RCC_AHB2LPENR_Types */

/**
 * @defgroup PLAY32_RCC_APB1LPENR_Types RCC APB1 Peripheral Clock Enable in Low-Power Mode Register (RCC_APB1LPENR)
 * @brief Bit positions, masks, and Sleep-mode clock enable types for RCC_APB1LPENR (offset 0x60).
 * @{
 */
#pragma region RCC_APB1LPENR_REGISTER

#pragma region RCC_APB1LPENR_REGISTER_POSITION
#define PLAY32_RCC_APB1LPENR_TIM2LPEN_POS      (0U)  /**< Bit 0: TIM2 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_TIM3LPEN_POS      (1U)  /**< Bit 1: TIM3 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_TIM4LPEN_POS      (2U)  /**< Bit 2: TIM4 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_TIM5LPEN_POS      (3U)  /**< Bit 3: TIM5 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_WWDGLPEN_POS      (11U) /**< Bit 11: Window watchdog clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_SPI2LPEN_POS      (14U) /**< Bit 14: SPI2 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_SPI3LPEN_POS      (15U) /**< Bit 15: SPI3 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_USART2LPEN_POS    (17U) /**< Bit 17: USART2 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_I2C1LPEN_POS      (21U) /**< Bit 21: I2C1 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_I2C2LPEN_POS      (22U) /**< Bit 22: I2C2 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_I2C3LPEN_POS      (23U) /**< Bit 23: I2C3 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB1LPENR_PWRLPEN_POS       (28U) /**< Bit 28: Power interface clock enable during Sleep mode position. */
#pragma endregion

#pragma region RCC_APB1LPENR_REGISTER_MASK
#define PLAY32_RCC_APB1LPENR_TIM2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM2LPEN_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB1LPENR_TIM3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM3LPEN_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_APB1LPENR_TIM4LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM4LPEN_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_APB1LPENR_TIM5LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_TIM5LPEN_POS)   /**< Bit 3 mask (0x00000008). */
#define PLAY32_RCC_APB1LPENR_WWDGLPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_WWDGLPEN_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB1LPENR_SPI2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_SPI2LPEN_POS)   /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB1LPENR_SPI3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_SPI3LPEN_POS)   /**< Bit 15 mask (0x00008000). */
#define PLAY32_RCC_APB1LPENR_USART2LPEN_MSK    (1UL << PLAY32_RCC_APB1LPENR_USART2LPEN_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB1LPENR_I2C1LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C1LPEN_POS)   /**< Bit 21 mask (0x00200000). */
#define PLAY32_RCC_APB1LPENR_I2C2LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C2LPEN_POS)   /**< Bit 22 mask (0x00400000). */
#define PLAY32_RCC_APB1LPENR_I2C3LPEN_MSK      (1UL << PLAY32_RCC_APB1LPENR_I2C3LPEN_POS)   /**< Bit 23 mask (0x00800000). */
#define PLAY32_RCC_APB1LPENR_PWRLPEN_MSK       (1UL << PLAY32_RCC_APB1LPENR_PWRLPEN_POS)    /**< Bit 28 mask (0x10000000). */
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
/** @} */ /* End of PLAY32_RCC_APB1LPENR_Types */


/**
 * @defgroup PLAY32_RCC_APB2LPENR_Types RCC APB2 Peripheral Clock Enable in Low-Power Mode Register (RCC_APB2LPENR)
 * @brief Bit positions, masks, and Sleep-mode clock enable types for RCC_APB2LPENR (offset 0x64).
 * @{
 */
#pragma region RCC_APB2LPENR_REGISTER

#pragma region RCC_APB2LPENR_REGISTER_POSITION
#define PLAY32_RCC_APB2LPENR_TIM1LPEN_POS      (0U)  /**< Bit 0: TIM1 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_USART1LPEN_POS    (4U)  /**< Bit 4: USART1 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_USART6LPEN_POS    (5U)  /**< Bit 5: USART6 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_ADC1LPEN_POS      (8U)  /**< Bit 8: ADC1 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_SDIOLPEN_POS      (11U) /**< Bit 11: SDIO clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_SPI1LPEN_POS      (12U) /**< Bit 12: SPI1 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_SPI4LPEN_POS      (13U) /**< Bit 13: SPI4 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_SYSCFGLPEN_POS    (14U) /**< Bit 14: System configuration controller clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_TIM9LPEN_POS      (16U) /**< Bit 16: TIM9 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_TIM10LPEN_POS     (17U) /**< Bit 17: TIM10 clock enable during Sleep mode position. */
#define PLAY32_RCC_APB2LPENR_TIM11LPEN_POS     (18U) /**< Bit 18: TIM11 clock enable during Sleep mode position. */
#pragma endregion

#pragma region RCC_APB2LPENR_REGISTER_MASK
#define PLAY32_RCC_APB2LPENR_TIM1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_TIM1LPEN_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_APB2LPENR_USART1LPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_USART1LPEN_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_RCC_APB2LPENR_USART6LPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_USART6LPEN_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_RCC_APB2LPENR_ADC1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_ADC1LPEN_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_RCC_APB2LPENR_SDIOLPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SDIOLPEN_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_RCC_APB2LPENR_SPI1LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SPI1LPEN_POS)   /**< Bit 12 mask (0x00001000). */
#define PLAY32_RCC_APB2LPENR_SPI4LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_SPI4LPEN_POS)   /**< Bit 13 mask (0x00002000). */
#define PLAY32_RCC_APB2LPENR_SYSCFGLPEN_MSK    (1UL << PLAY32_RCC_APB2LPENR_SYSCFGLPEN_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_RCC_APB2LPENR_TIM9LPEN_MSK      (1UL << PLAY32_RCC_APB2LPENR_TIM9LPEN_POS)   /**< Bit 16 mask (0x00010000). */
#define PLAY32_RCC_APB2LPENR_TIM10LPEN_MSK     (1UL << PLAY32_RCC_APB2LPENR_TIM10LPEN_POS)  /**< Bit 17 mask (0x00020000). */
#define PLAY32_RCC_APB2LPENR_TIM11LPEN_MSK     (1UL << PLAY32_RCC_APB2LPENR_TIM11LPEN_POS)  /**< Bit 18 mask (0x00040000). */
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
/** @} */ /* End of PLAY32_RCC_APB2LPENR_Types */


/**
 * @defgroup PLAY32_RCC_BDCR_Types RCC Backup Domain Control Register (RCC_BDCR)
 * @brief Bit positions, masks, and Backup domain / RTC clock control types for RCC_BDCR (offset 0x70).
 * @{
 */
#pragma region RCC_BDCR_REGISTER

#pragma region RCC_BDCR_REGISTER_POSITION
#define PLAY32_RCC_BDCR_LSEON_POS     (0U)  /**< Bit 0: External low-speed oscillator enable position. */
#define PLAY32_RCC_BDCR_LSERDY_POS    (1U)  /**< Bit 1: External low-speed oscillator ready flag position. */
#define PLAY32_RCC_BDCR_LSEBYP_POS    (2U)  /**< Bit 2: External low-speed oscillator bypass position. */
#define PLAY32_RCC_BDCR_RTCSEL_POS    (8U)  /**< Bits [9:8]: RTC clock source selection position. */
#define PLAY32_RCC_BDCR_RTCEN_POS     (15U) /**< Bit 15: RTC clock enable position. */
#define PLAY32_RCC_BDCR_BDRST_POS     (16U) /**< Bit 16: Backup domain software reset position. */
#pragma endregion

#pragma region RCC_BDCR_REGISTER_MASK
#define PLAY32_RCC_BDCR_LSEON_MSK     (1UL << PLAY32_RCC_BDCR_LSEON_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_BDCR_LSERDY_MSK    (1UL << PLAY32_RCC_BDCR_LSERDY_POS) /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_BDCR_LSEBYP_MSK    (1UL << PLAY32_RCC_BDCR_LSEBYP_POS) /**< Bit 2 mask (0x00000004). */
#define PLAY32_RCC_BDCR_RTCSEL_MSK    (3UL << PLAY32_RCC_BDCR_RTCSEL_POS) /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_RCC_BDCR_RTCEN_MSK     (1UL << PLAY32_RCC_BDCR_RTCEN_POS)  /**< Bit 15 mask (0x00008000). */
#define PLAY32_RCC_BDCR_BDRST_MSK     (1UL << PLAY32_RCC_BDCR_BDRST_POS)  /**< Bit 16 mask (0x00010000). */
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
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorEnable
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_BDCR_ExternalLowSpeedOscillatorReady;

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
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_NO_CLOCK = 0U, /**< No clock supplied to RTC (reset state). */
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_LSE      = 1U, /**< LSE oscillator clock (32.768 kHz) used as the RTC clock. */
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_LSI      = 2U, /**< LSI RC oscillator clock (~32 kHz) used as the RTC clock. */
    PLAY32_RCC_BDCR_REAL_TIME_CLOCK_SOURCE_SELECTION_HSE      = 3U  /**< HSE oscillator clock divided by a programmable prescaler (RTCPRE in RCC_CFGR) used as the RTC clock. */
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
/** @} */ /* End of PLAY32_RCC_BDCR_Types */


/**
 * @defgroup PLAY32_RCC_CSR_Types RCC Clock Control & Status Register (RCC_CSR)
 * @brief Bit positions, masks, and LSI oscillator / reset-cause flag types for RCC_CSR (offset 0x74).
 * @{
 */
#pragma region RCC_CSR_REGISTER

#pragma region RCC_CSR_REGISTER_POSITION
#define PLAY32_RCC_CSR_LSION_POS       (0U)  /**< Bit 0: Internal low-speed oscillator enable position. */
#define PLAY32_RCC_CSR_LSIRDY_POS      (1U)  /**< Bit 1: Internal low-speed oscillator ready flag position. */
#define PLAY32_RCC_CSR_RMVF_POS        (24U) /**< Bit 24: Remove reset flag position. */
#define PLAY32_RCC_CSR_BORRSTF_POS     (25U) /**< Bit 25: BOR reset flag position. */
#define PLAY32_RCC_CSR_PINRSTF_POS     (26U) /**< Bit 26: PIN reset flag position. */
#define PLAY32_RCC_CSR_PORRSTF_POS     (27U) /**< Bit 27: POR/PDR reset flag position. */
#define PLAY32_RCC_CSR_SFTRSTF_POS     (28U) /**< Bit 28: Software reset flag position. */
#define PLAY32_RCC_CSR_IWDGRSTF_POS    (29U) /**< Bit 29: Independent watchdog reset flag position. */
#define PLAY32_RCC_CSR_WWDGRSTF_POS    (30U) /**< Bit 30: Window watchdog reset flag position. */
#define PLAY32_RCC_CSR_LPWRRSTF_POS    (31U) /**< Bit 31: Low-power reset flag position. */
#pragma endregion

#pragma region RCC_CSR_REGISTER_MASK
#define PLAY32_RCC_CSR_LSION_MSK       (1UL << PLAY32_RCC_CSR_LSION_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_RCC_CSR_LSIRDY_MSK      (1UL << PLAY32_RCC_CSR_LSIRDY_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_RCC_CSR_RMVF_MSK        (1UL << PLAY32_RCC_CSR_RMVF_POS)     /**< Bit 24 mask (0x01000000). */
#define PLAY32_RCC_CSR_BORRSTF_MSK     (1UL << PLAY32_RCC_CSR_BORRSTF_POS)  /**< Bit 25 mask (0x02000000). */
#define PLAY32_RCC_CSR_PINRSTF_MSK     (1UL << PLAY32_RCC_CSR_PINRSTF_POS)  /**< Bit 26 mask (0x04000000). */
#define PLAY32_RCC_CSR_PORRSTF_MSK     (1UL << PLAY32_RCC_CSR_PORRSTF_POS)  /**< Bit 27 mask (0x08000000). */
#define PLAY32_RCC_CSR_SFTRSTF_MSK     (1UL << PLAY32_RCC_CSR_SFTRSTF_POS)  /**< Bit 28 mask (0x10000000). */
#define PLAY32_RCC_CSR_IWDGRSTF_MSK    (1UL << PLAY32_RCC_CSR_IWDGRSTF_POS) /**< Bit 29 mask (0x20000000). */
#define PLAY32_RCC_CSR_WWDGRSTF_MSK    (1UL << PLAY32_RCC_CSR_WWDGRSTF_POS) /**< Bit 30 mask (0x40000000). */
#define PLAY32_RCC_CSR_LPWRRSTF_MSK    (1UL << PLAY32_RCC_CSR_LPWRRSTF_POS) /**< Bit 31 mask (0x80000000). */
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
 * @see    PLAY32_RCC_Flag
 * @see    PLAY32_RCC_CSR_InternalLowSpeedOscillatorEnable
 */
typedef PLAY32_RCC_Flag PLAY32_RCC_CSR_InternalLowSpeedOscillatorReady;

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
/** @} */ /* End of PLAY32_RCC_CSR_Types */

/**
 * @defgroup PLAY32_RCC_SSCGR_Types RCC Spread Spectrum Clock Generation Register (RCC_SSCGR)
 * @brief Bit positions, masks, and spread-spectrum modulation types for RCC_SSCGR (offset 0x80).
 * @{
 */
#pragma region RCC_SSCGR_REGISTER

#pragma region RCC_SSCGR_REGISTER_POSITION
#define PLAY32_RCC_SSCGR_MODPER_POS       (0U)  /**< Bits [12:0]: Modulation period position. */
#define PLAY32_RCC_SSCGR_INCSTEP_POS      (13U) /**< Bits [27:13]: Incrementation step position. */
#define PLAY32_RCC_SSCGR_SPREADSEL_POS    (30U) /**< Bit 30: Spread select position. */
#define PLAY32_RCC_SSCGR_SSCGEN_POS       (31U) /**< Bit 31: Spread spectrum modulation enable position. */
#pragma endregion

#pragma region RCC_SSCGR_REGISTER_MASK
#define PLAY32_RCC_SSCGR_MODPER_MSK       (8191UL << PLAY32_RCC_SSCGR_MODPER_POS)    /**< Bits [12:0] mask (0x00001FFF). */
#define PLAY32_RCC_SSCGR_INCSTEP_MSK      (32767UL << PLAY32_RCC_SSCGR_INCSTEP_POS)  /**< Bits [27:13] mask (0x0FFFE000). */
#define PLAY32_RCC_SSCGR_SPREADSEL_MSK    (1UL << PLAY32_RCC_SSCGR_SPREADSEL_POS)    /**< Bit 30 mask (0x40000000). */
#define PLAY32_RCC_SSCGR_SSCGEN_MSK       (1UL << PLAY32_RCC_SSCGR_SSCGEN_POS)       /**< Bit 31 mask (0x80000000). */
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
/** @} */ /* End of PLAY32_RCC_SSCGR_Types */

/**
 * @defgroup PLAY32_RCC_PLLI2SCFGR_Types RCC PLLI2S Configuration Register (RCC_PLLI2SCFGR)
 * @brief Bit positions, masks, and multiplier/divider value types for RCC_PLLI2SCFGR (offset 0x84).
 * @{
 */
#pragma region RCC_PLLI2SCFGR_REGISTER

#pragma region RCC_PLLI2SCFGR_REGISTER_POSITION
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SN_POS    (6U)  /**< Bits [14:6]: PLLI2S multiplication factor for VCO position. */
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SR_POS    (28U) /**< Bits [30:28]: PLLI2S division factor for I2S clocks position. */
#pragma endregion

#pragma region RCC_PLLI2SCFGR_REGISTER_MASK
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SN_MSK    (511UL << PLAY32_RCC_PLLI2SCFGR_PLLI2SN_POS) /**< Bits [14:6] mask (0x00007FC0). */
#define PLAY32_RCC_PLLI2SCFGR_PLLI2SR_MSK    (7UL << PLAY32_RCC_PLLI2SCFGR_PLLI2SR_POS)   /**< Bits [30:28] mask (0x70000000). */
#pragma endregion

#pragma region RCC_PLLI2SCFGR_REGISTER_VALUE

/**
 * @brief  PLLI2S VCO multiplication factor (PLLI2SN) value type.
 * @note   Read/Write 9-bit control field (bits 14:6 of RCC_PLLI2SCFGR, PLLI2SN[8:0], valid range 50 to 432)
 *         that sets the multiplication factor for the PLLI2S VCO output frequency:
 *         \f$f_{\text{VCO\_I2S}} = f_{\text{VCO\_IN}} \times \text{PLLI2SN}\f$.
 * @warning Must only be written when PLLI2S is disabled (`PLLI2SON = 0` in `RCC_CR`).
 *          Ensure the resulting VCO output frequency remains within the specified hardware range
 *          (**192 MHz to 432 MHz** on STM32F401).
 * @see    PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SDivision
 */
typedef uint16_t PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SMultiplication;

/**
 * @brief  PLLI2S division factor for I2S clocks (PLLI2SR) value type.
 * @note   Read/Write 3-bit control field (bits 30:28 of RCC_PLLI2SCFGR, PLLI2SR[2:0], valid range 2 to 7)
 *         that divides the PLLI2S VCO output to generate the I2S peripheral clock:
 *         \f$f_{\text{I2S\_CLK}} = \frac{f_{\text{VCO\_I2S}}}{\text{PLLI2SR}}\f$.
 * @warning Must only be written when PLLI2S is disabled (`PLLI2SON = 0` in `RCC_CR`).
 *          Values 0 and 1 are forbidden by hardware; ensure the resulting I2S clock
 *          does not exceed the maximum allowed frequency (**192 MHz**).
 * @see    PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SMultiplication
 */
typedef uint8_t PLAY32_RCC_PLLI2SCFGR_PhaseLockedLoopI2SDivision;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_PLLI2SCFGR_Types */

/**
 * @defgroup PLAY32_RCC_DCKCFGR_Types RCC Dedicated Clocks Configuration Register (RCC_DCKCFGR)
 * @brief Bit position, mask, and timer clock prescaler selection for RCC_DCKCFGR (offset 0x8C).
 * @{
 */
#pragma region RCC_DCKCFGR_REGISTER

#pragma region RCC_DCKCFGR_REGISTER_POSITION
#define PLAY32_RCC_DCKCFGR_TIMPRE_POS    (24U) /**< Bit 24: Timers clocks prescalers selection position. */
#pragma endregion

#pragma region RCC_DCKCFGR_REGISTER_MASK
#define PLAY32_RCC_DCKCFGR_TIMPRE_MSK    (1UL << PLAY32_RCC_DCKCFGR_TIMPRE_POS) /**< Bit 24 mask (0x01000000). */
#pragma endregion

#pragma region RCC_DCKCFGR_REGISTER_VALUE

/**
 * @brief  Timers clocks prescalers selection (TIMPRE) enumeration.
 * @note   Read/Write control bit (bit 24 of RCC_DCKCFGR, TIMPRE) used to control the clock
 *         frequency of all timers connected to the APB1 and APB2 domains.
 *         Bits [31:25] and [23:0] of RCC_DCKCFGR are reserved and must be kept at reset value (0).
 * @warning When @ref PLAY32_RCC_DCKCFGR_TIMERS_PRESCALER_X_4 is selected,
 *          `TIMxCLK` equals `HCLK` if the APB prescaler (`PPRE1`/`PPRE2`) is 1 or 2, and `4 x PCLKx`
 *          otherwise. Ensure timer peripheral maximum clock limits are not exceeded.
 * @see    PLAY32_RCC_Switch
 */
typedef enum {
    PLAY32_RCC_DCKCFGR_TIMERS_PRESCALER_X_2 = 0U, /**< If APB prescaler is 1, TIMxCLK = HCLK; otherwise TIMxCLK = 2 x PCLKx. */
    PLAY32_RCC_DCKCFGR_TIMERS_PRESCALER_X_4 = 1U  /**< If APB prescaler is 1 or 2, TIMxCLK = HCLK; otherwise TIMxCLK = 4 x PCLKx. */
} PLAY32_RCC_DCKCFGR_TimersPrescaler;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_RCC_DCKCFGR_Types */

/** @} */ /* End of PLAY32_RCC */

#endif /* PLAY32_RCC_TYPES_H */

