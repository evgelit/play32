/**
* @file    pwr_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for Power Controller (PWR) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-24
 *
 * @note    This file provides a strict compile-time type-safe interface
 *          for hardware registers manipulation without runtime overhead.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_PWR_TYPES_H
#define PLAY32_PWR_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_PWR Power Controller (PWR)
 * @brief Hardware register map, base address, bit masks, and type-safe enumerations for PWR.
 * @{
 */

/**
 * @defgroup PLAY32_PWR_Memory_Map Peripheral Base Address and Register Map
 * @brief APB1 base address calculation and memory-mapped register structure for PWR.
 * @{
 */

/**
 * @brief  Base address of the APB1 peripheral bus (0x40000000).
 * @note   PWR is mapped onto the APB1 peripheral bus in STM32F401.
 */
#define PLAY32_APB1_PERIPHERAL    (1UL << 30)

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE         (1UL << 10)

/**
 * @brief  APB1 memory slot index for PWR (offset 28 * 0x0400 = 0x7000).
 * @see    PLAY32_PWR_BASE
 */
#define PLAY32_PWR_BASE_POS       (28U)

/**
 * @brief  PWR peripheral base address (0x40007000).
 * @note   Computed from @ref PLAY32_APB1_PERIPHERAL and @ref PLAY32_PWR_BASE_POS.
 */
#define PLAY32_PWR_BASE           (PLAY32_APB1_PERIPHERAL + (PLAY32_PWR_BASE_POS * PLAY32_BLOCK_SIZE))


/**
 * @brief  Power Controller (PWR) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 5.5, offsets 0x00-0x04).
 */
typedef struct {
    volatile uint32_t CR;  /**< Offset: 0x00 - Power control register. */
    volatile uint32_t CSR; /**< Offset: 0x04 - Power control/status register. */
} PLAY32_PWR_TypeDef;

/** @brief PWR peripheral register map pointer (APB1, 0x40007000). */
#define PLAY32_PWR ((PLAY32_PWR_TypeDef *)PLAY32_PWR_BASE)

/** @} */ /* End of PLAY32_PWR_Memory_Map */

/**
 * @defgroup PLAY32_PWR_Common_Types Common PWR Enumerations
 * @brief Reusable active-high control switch and hardware status flag enumerations across PWR registers.
 * @{
 */
#pragma region PWR_COMMON_ENUM

/**
 * @brief  Standard active-high control switch states for PWR feature and wakeup enable bits.
 */
typedef enum {
    PLAY32_PWR_SWITCH_DISABLED = 0U, /**< Feature disabled (0). */
    PLAY32_PWR_SWITCH_ENABLED  = 1U  /**< Feature enabled (1). */
} PLAY32_PWR_Switch;

/**
 * @brief  PWR hardware status flag state enumeration.
 */
typedef enum {
    PLAY32_PWR_FLAG_NOT_SET = 0U, /**< Flag is cleared (0). */
    PLAY32_PWR_FLAG_SET     = 1U  /**< Flag is set (1). */
} PLAY32_PWR_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_PWR_Common_Types */

/**
 * @defgroup PLAY32_PWR_CR_Types PWR Power Control Register (PWR_CR)
 * @brief Bit positions, masks, and power/regulator/sleep enumerations for PWR_CR (offset 0x00).
 * @{
 */
#pragma region PWR_CR_REGISTER

#pragma region PWR_CR_REGISTER_POSITION
#define PLAY32_PWR_CR_LPDS_POS      (0U)  /**< Bit 0: Low-power deepsleep position. */
#define PLAY32_PWR_CR_PDDS_POS      (1U)  /**< Bit 1: Power-down deepsleep position. */
#define PLAY32_PWR_CR_CWUF_POS      (2U)  /**< Bit 2: Clear wakeup flag position. */
#define PLAY32_PWR_CR_CSBF_POS      (3U)  /**< Bit 3: Clear standby flag position. */
#define PLAY32_PWR_CR_PVDE_POS      (4U)  /**< Bit 4: Power voltage detector enable position. */
#define PLAY32_PWR_CR_PLS_POS       (5U)  /**< Bits [7:5]: PVD level selection position. */
#define PLAY32_PWR_CR_DBP_POS       (8U)  /**< Bit 8: Disable backup domain write protection position. */
#define PLAY32_PWR_CR_FPDS_POS      (9U)  /**< Bit 9: Flash power-down in Stop mode position. */
#define PLAY32_PWR_CR_LPLVDS_POS    (10U) /**< Bit 10: Low-power regulator low voltage in deepsleep position. */
#define PLAY32_PWR_CR_MRLVDS_POS    (11U) /**< Bit 11: Main regulator low voltage in deepsleep position. */
#define PLAY32_PWR_CR_ADCDC1_POS    (13U) /**< Bit 13: ADC DC1 noise reduction bit position. */
#define PLAY32_PWR_CR_VOS_POS       (14U) /**< Bits [15:14]: Regulator voltage scaling output selection position. */
#pragma endregion

#pragma region PWR_CR_REGISTER_MASK
#define PLAY32_PWR_CR_LPDS_MSK      (1UL << PLAY32_PWR_CR_LPDS_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_PWR_CR_PDDS_MSK      (1UL << PLAY32_PWR_CR_PDDS_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_PWR_CR_CWUF_MSK      (1UL << PLAY32_PWR_CR_CWUF_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_PWR_CR_CSBF_MSK      (1UL << PLAY32_PWR_CR_CSBF_POS)   /**< Bit 3 mask (0x00000008). */
#define PLAY32_PWR_CR_PVDE_MSK      (1UL << PLAY32_PWR_CR_PVDE_POS)   /**< Bit 4 mask (0x00000010). */
#define PLAY32_PWR_CR_PLS_MSK       (7UL << PLAY32_PWR_CR_PLS_POS)    /**< Bits [7:5] mask (0x000000E0). */
#define PLAY32_PWR_CR_DBP_MSK       (1UL << PLAY32_PWR_CR_DBP_POS)    /**< Bit 8 mask (0x00000100). */
#define PLAY32_PWR_CR_FPDS_MSK      (1UL << PLAY32_PWR_CR_FPDS_POS)   /**< Bit 9 mask (0x00000200). */
#define PLAY32_PWR_CR_LPLVDS_MSK    (1UL << PLAY32_PWR_CR_LPLVDS_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_PWR_CR_MRLVDS_MSK    (1UL << PLAY32_PWR_CR_MRLVDS_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_PWR_CR_ADCDC1_MSK    (1UL << PLAY32_PWR_CR_ADCDC1_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_PWR_CR_VOS_MSK       (3UL << PLAY32_PWR_CR_VOS_POS)    /**< Bits [15:14] mask (0x0000C000). */
#pragma endregion

#pragma region PWR_CR_REGISTER_ENUM

/**
 * @brief  Low-power deepsleep (`LPDS`) voltage regulator mode enumeration.
 * @note   Read/Write control bit (bit 0 of PWR_CR, LPDS) selecting whether the main voltage
 *         regulator or low-power regulator is active when the device enters Stop mode (`PDDS = 0`).
 * @see    PLAY32_PWR_CR_PowerDownDeepsleep
 * @see    PLAY32_PWR_CR_LowPowerRegulatorLowVoltageInDeepsleep
 */
typedef enum {
    PLAY32_PWR_CR_LOW_POWER_DEEPSLEEP_MAIN_REGULATOR      = 0U, /**< Main voltage regulator ON during Stop mode. */
    PLAY32_PWR_CR_LOW_POWER_DEEPSLEEP_LOW_POWER_REGULATOR = 1U  /**< Low-power voltage regulator ON during Stop mode. */
} PLAY32_PWR_CR_LowPowerDeepsleep;

/**
 * @brief  Power-down deepsleep (`PDDS`) mode selection enumeration.
 * @note   Read/Write control bit (bit 1 of PWR_CR, PDDS) working in conjunction with `LPDS`
 *         to select between Stop mode and Standby mode when the CPU enters Deepsleep (`SLEEPDEEP = 1`).
 * @warning In Standby mode (`PDDS = 1`), the 1.2V core domain is powered off and all SRAM/register
 *          contents (except Backup domain) are lost upon wakeup.
 * @see    PLAY32_PWR_CR_LowPowerDeepsleep
 */
typedef enum {
    PLAY32_PWR_CR_POWER_DOWN_DEEPSLEEP_STOP_MODE    = 0U, /**< Enter Stop mode when CPU enters deepsleep. */
    PLAY32_PWR_CR_POWER_DOWN_DEEPSLEEP_STANDBY_MODE = 1U  /**< Enter Standby mode when CPU enters deepsleep. */
} PLAY32_PWR_CR_PowerDownDeepsleep;

/**
 * @brief  Clear wakeup flag (`CWUF`) self-clearing trigger type.
 * @note   Read/Write-1 self-clearing control bit (bit 2 of PWR_CR, CWUF). Writing `1` clears
 *         the `WUF` wakeup flag in `PWR_CSR` after 2 system clock cycles; always reads as `0`.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CSR_WakeupFlag
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_ClearWakeupFlag;

/**
 * @brief  Clear standby flag (`CSBF`) self-clearing trigger type.
 * @note   Read/Write-1 self-clearing control bit (bit 3 of PWR_CR, CSBF). Writing `1` clears
 *         the `SBF` standby flag in `PWR_CSR`; always reads as `0`.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CSR_StandbyFlag
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_ClearStandbyFlag;

/**
 * @brief  Power voltage detector enable (`PVDE`) state type.
 * @note   Read/Write control bit (bit 4 of PWR_CR, PVDE) enabling the programmable comparator
 *         that monitors `VDD` against the voltage threshold selected by `PLS[2:0]`.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CR_PVDLevelSelection
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_PowerVoltageDetectorEnable;

/**
 * @brief  PVD voltage threshold level selection (`PLS[2:0]`) enumeration.
 * @note   Read/Write 3-bit field (bits 7:5 of PWR_CR, PLS[2:0]) selecting the `VDD` voltage
 *         threshold monitored by the Power Voltage Detector when `PVDE = 1`.
 * @see    PLAY32_PWR_CR_PowerVoltageDetectorEnable
 * @see    PLAY32_PWR_CSR_PVDOutput
 */
typedef enum {
    PLAY32_PWR_CR_PVD_LEVEL_2_2V = 0U, /**< Threshold level 0: 2.2 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_3V = 1U, /**< Threshold level 1: 2.3 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_4V = 2U, /**< Threshold level 2: 2.4 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_5V = 3U, /**< Threshold level 3: 2.5 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_6V = 4U, /**< Threshold level 4: 2.6 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_7V = 5U, /**< Threshold level 5: 2.7 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_8V = 6U, /**< Threshold level 6: 2.8 V. */
    PLAY32_PWR_CR_PVD_LEVEL_2_9V = 7U  /**< Threshold level 7: 2.9 V. */
} PLAY32_PWR_CR_PVDLevelSelection;

/**
 * @brief  Disable backup domain write protection (`DBP`) state type.
 * @note   Read/Write control bit (bit 8 of PWR_CR, DBP). In reset state, `RCC_BDCR` and `RTC`
 *         registers are write-protected against parasitic writes; set `DBP = 1` to unlock them.
 * @see    PLAY32_PWR_Switch
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_DisableBackupDomainWriteProtection;

/**
 * @brief  Flash power-down in Stop mode (`FPDS`) enumeration.
 * @note   Read/Write control bit (bit 9 of PWR_CR, FPDS) selecting whether the Flash memory
 *         remains idle or enters deep power-down mode during Stop mode (trading slightly longer
 *         wakeup latency for lower Stop-mode current consumption).
 */
typedef enum {
    PLAY32_PWR_CR_FLASH_POWER_DOWN_STOP_IDLE       = 0U, /**< Flash memory not in power-down when in Stop mode. */
    PLAY32_PWR_CR_FLASH_POWER_DOWN_STOP_POWER_DOWN = 1U  /**< Flash memory in power-down when in Stop mode. */
} PLAY32_PWR_CR_FlashPowerDownInStopMode;

/**
 * @brief  Low-power regulator low voltage in deepsleep (`LPLVDS`) state type.
 * @note   Read/Write control bit (bit 10 of PWR_CR, LPLVDS) reducing the low-power regulator
 *         output voltage further during Stop mode when `LPDS = 1` to minimize leakage current.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CR_LowPowerDeepsleep
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_LowPowerRegulatorLowVoltageInDeepsleep;

/**
 * @brief  Main regulator low voltage in deepsleep (`MRLVDS`) state type.
 * @note   Read/Write control bit (bit 11 of PWR_CR, MRLVDS) reducing the main regulator
 *         output voltage during Stop mode when `LPDS = 0` to reduce static current consumption.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CR_LowPowerDeepsleep
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_MainRegulatorLowVoltageInDeepsleep;

/**
 * @brief  ADC DC1 noise reduction bit (`ADCDC1`) state type.
 * @note   Read/Write control bit (bit 13 of PWR_CR, ADCDC1) used for ADC accuracy optimization
 *         per STM32F401 datasheet recommendations.
 * @warning Must only be set when the ADC is disabled (`ADON = 0`).
 * @see    PLAY32_PWR_Switch
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CR_ADCDC1;

/**
 * @brief  Regulator voltage scaling output selection (`VOS[1:0]`) enumeration.
 * @note   Read/Write 2-bit field (bits 15:14 of PWR_CR, VOS[1:0]) controlling the internal
 *         main voltage regulator output level to balance maximum `SYSCLK` frequency vs. power.
 * @warning Must only be modified when the PLL is disabled (`PLLON = 0` in `RCC_CR`).
 *          After enabling the PLL, wait until `VOSRDY == 1` in `PWR_CSR`.
 * @see    PLAY32_PWR_CSR_RegulatorVoltageScalingOutputReady
 */
typedef enum {
    PLAY32_PWR_CR_VOLTAGE_SCALING_SCALE_3 = 1U, /**< Scale 3 mode (max HCLK frequency up to 60 MHz). */
    PLAY32_PWR_CR_VOLTAGE_SCALING_SCALE_2 = 2U  /**< Scale 2 mode (default, max HCLK frequency up to 84 MHz). */
} PLAY32_PWR_CR_VoltageScalingOutputSelection;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_PWR_CR_Types */

/**
 * @defgroup PLAY32_PWR_CSR_Types PWR Power Control/Status Register (PWR_CSR)
 * @brief Bit positions, masks, and wakeup/regulator status types for PWR_CSR (offset 0x04).
 * @{
 */
#pragma region PWR_CSR_REGISTER

#pragma region PWR_CSR_REGISTER_POSITION
#define PLAY32_PWR_CSR_WUF_POS      (0U)  /**< Bit 0: Wakeup flag position. */
#define PLAY32_PWR_CSR_SBF_POS      (1U)  /**< Bit 1: Standby flag position. */
#define PLAY32_PWR_CSR_PVDO_POS     (2U)  /**< Bit 2: PVD output status position. */
#define PLAY32_PWR_CSR_BRR_POS      (3U)  /**< Bit 3: Backup regulator ready position. */
#define PLAY32_PWR_CSR_EWUP_POS     (8U)  /**< Bit 8: Enable WKUP pin (PA0) position. */
#define PLAY32_PWR_CSR_BRE_POS      (9U)  /**< Bit 9: Backup regulator enable position. */
#define PLAY32_PWR_CSR_VOSRDY_POS   (14U) /**< Bit 14: Regulator voltage scaling output selection ready position. */
#pragma endregion

#pragma region PWR_CSR_REGISTER_MASK
#define PLAY32_PWR_CSR_WUF_MSK      (1UL << PLAY32_PWR_CSR_WUF_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_PWR_CSR_SBF_MSK      (1UL << PLAY32_PWR_CSR_SBF_POS)    /**< Bit 1 mask (0x00000002). */
#define PLAY32_PWR_CSR_PVDO_MSK     (1UL << PLAY32_PWR_CSR_PVDO_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_PWR_CSR_BRR_MSK      (1UL << PLAY32_PWR_CSR_BRR_POS)    /**< Bit 3 mask (0x00000008). */
#define PLAY32_PWR_CSR_EWUP_MSK     (1UL << PLAY32_PWR_CSR_EWUP_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_PWR_CSR_BRE_MSK      (1UL << PLAY32_PWR_CSR_BRE_POS)    /**< Bit 9 mask (0x00000200). */
#define PLAY32_PWR_CSR_VOSRDY_MSK   (1UL << PLAY32_PWR_CSR_VOSRDY_POS) /**< Bit 14 mask (0x00004000). */
#pragma endregion

#pragma region PWR_CSR_REGISTER_ENUM

/**
 * @brief  Wakeup flag (`WUF`) status type.
 * @note   Read-only flag (bit 0 of PWR_CSR, WUF) set by hardware when a wakeup event
 *         is received from the `WKUP` pin (`PA0`) or from the `RTC` alarm/wakeup timer.
 * @warning Cleared by system reset or by setting `CWUF = 1` in `PWR_CR` (takes 2 system clock cycles).
 * @see    PLAY32_PWR_Flag
 * @see    PLAY32_PWR_CR_ClearWakeupFlag
 */
typedef PLAY32_PWR_Flag PLAY32_PWR_CSR_WakeupFlag;

/**
 * @brief  Standby flag (`SBF`) status type.
 * @note   Read-only flag (bit 1 of PWR_CSR, SBF) set by hardware when the device enters Standby mode,
 *         allowing software after reset to distinguish a Standby wakeup from a cold power-on reset.
 * @warning Cleared only by a Power-On/Power-Down Reset (POR/PDR) or by setting `CSBF = 1` in `PWR_CR`.
 * @see    PLAY32_PWR_Flag
 * @see    PLAY32_PWR_CR_ClearStandbyFlag
 */
typedef PLAY32_PWR_Flag PLAY32_PWR_CSR_StandbyFlag;

/**
 * @brief  PVD output (`PVDO`) threshold comparison status enumeration.
 * @note   Read-only status bit (bit 2 of PWR_CSR, PVDO) valid only when `PVDE = 1` in `PWR_CR`.
 * @see    PLAY32_PWR_CR_PowerVoltageDetectorEnable
 * @see    PLAY32_PWR_CR_PVDLevelSelection
 */
typedef enum {
    PLAY32_PWR_CSR_PVD_OUTPUT_VDD_ABOVE_THRESHOLD = 0U, /**< VDD is higher than the PVD threshold selected by PLS[2:0]. */
    PLAY32_PWR_CSR_PVD_OUTPUT_VDD_BELOW_THRESHOLD = 1U  /**< VDD is lower than the PVD threshold selected by PLS[2:0]. */
} PLAY32_PWR_CSR_PVDOutput;

/**
 * @brief  Backup regulator ready (`BRR`) status type.
 * @note   Read-only flag (bit 3 of PWR_CSR, BRR) set by hardware to indicate that the low-power
 *         Backup regulator is ready after setting `BRE = 1`.
 * @see    PLAY32_PWR_Flag
 * @see    PLAY32_PWR_CSR_BackupRegulatorEnable
 */
typedef PLAY32_PWR_Flag PLAY32_PWR_CSR_BackupRegulatorReady;

/**
 * @brief  Enable WKUP pin (`EWUP`) control state type.
 * @note   Read/Write control bit (bit 8 of PWR_CSR, EWUP). When enabled (`1`), the `WKUP` pin (`PA0`)
 *         is forced into input pull-down configuration and a rising edge wakes the MCU from Standby mode.
 * @warning Cleared by system reset.
 * @see    PLAY32_PWR_Switch
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CSR_EnableWKUPPin;

/**
 * @brief  Backup regulator enable (`BRE`) control state type.
 * @note   Read/Write control bit (bit 9 of PWR_CSR, BRE) used to keep the 4 KB Backup SRAM
 *         powered in Standby and `VBAT` modes.
 * @warning Backup domain write protection must be disabled first (`DBP = 1` in `PWR_CR`)
 *          before modifying `BRE`. Wait for `BRR == 1` before entering Standby mode.
 * @see    PLAY32_PWR_Switch
 * @see    PLAY32_PWR_CSR_BackupRegulatorReady
 */
typedef PLAY32_PWR_Switch PLAY32_PWR_CSR_BackupRegulatorEnable;

/**
 * @brief  Regulator voltage scaling output selection ready (`VOSRDY`) status type.
 * @note   Read-only flag (bit 14 of PWR_CSR, VOSRDY) set by hardware once the internal main
 *         voltage regulator output has settled to the level selected by `VOS[1:0]` in `PWR_CR`.
 * @see    PLAY32_PWR_Flag
 * @see    PLAY32_PWR_CR_VoltageScalingOutputSelection
 */
typedef PLAY32_PWR_Flag PLAY32_PWR_CSR_RegulatorVoltageScalingOutputReady;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_PWR_CSR_Types */

/** @} */ /* End of PLAY32_PWR */

#endif /* PLAY32_PWR_TYPES_H */
