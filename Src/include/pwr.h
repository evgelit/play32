/**
 * @file    pwr.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for Power Controller (PWR) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-24
 *
 * @note    Uses advanced Computed Macro Calls for linear register dispatching,
 *          providing zero-cost abstractions and eliminating code duplication.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_PWR_H
#define PLAY32_PWR_H

#include "pwr_types.h"

/**
 * @addtogroup PLAY32_PWR
 * @{
 */

/**
 * @defgroup PLAY32_PWR_Driver PWR Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for the singleton Power Controller (`PLAY32_PWR`).
 * @details Maps each power control or status field to its hardware register, bitfield mnemonic,
 *          strict typedef from @ref pwr_types.h, and hardware access mode using the signature:
 *          `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_PWR_TypeDef
 */
#define PWR_REGISTERS_TABLE(X) \
/************************************************* PWR CR REGISTER ***************************************************/\
X(low_power_deepsleep,                             CR,     LPDS,      LowPowerDeepsleep,                      SET_RMW )\
X(power_down_deepsleep,                            CR,     PDDS,      PowerDownDeepsleep,                     SET_RMW )\
X(clear_wakeup_flag,                               CR,     CWUF,      ClearWakeupFlag,                        SET_RMW )\
X(clear_standby_flag,                              CR,     CSBF,      ClearStandbyFlag,                       SET_RMW )\
X(power_voltage_detector_enable,                   CR,     PVDE,      PowerVoltageDetectorEnable,             SET_RMW )\
X(pvd_level_selection,                             CR,     PLS,       PVDLevelSelection,                      SET_RMW )\
X(disable_backup_domain_write_protection,          CR,     DBP,       DisableBackupDomainWriteProtection,     SET_RMW )\
X(flash_power_down_in_stop_mode,                   CR,     FPDS,      FlashPowerDownInStopMode,               SET_RMW )\
X(low_power_regulator_low_voltage_in_deepsleep,    CR,     LPLVDS,    LowPowerRegulatorLowVoltageInDeepsleep, SET_RMW )\
X(main_regulator_low_voltage_in_deepsleep,         CR,     MRLVDS,    MainRegulatorLowVoltageInDeepsleep,     SET_RMW )\
X(adc_dc1,                                         CR,     ADCDC1,    ADCDC1,                                 SET_RMW )\
X(voltage_scaling_output_selection,                CR,     VOS,       VoltageScalingOutputSelection,          SET_RMW )\
\
/************************************************* PWR CSR REGISTER **************************************************/\
X(wakeup_flag,                                     CSR,    WUF,       WakeupFlag,                             RO      )\
X(standby_flag,                                    CSR,    SBF,       StandbyFlag,                            RO      )\
X(pvd_output,                                      CSR,    PVDO,      PVDOutput,                              RO      )\
X(backup_regulator_ready,                          CSR,    BRR,       BackupRegulatorReady,                   RO      )\
X(enable_wkup_pin,                                 CSR,    EWUP,      EnableWKUPPin,                          SET_RMW )\
X(backup_regulator_enable,                         CSR,    BRE,       BackupRegulatorEnable,                  SET_RMW )\
X(regulator_voltage_scaling_output_ready,          CSR,    VOSRDY,    RegulatorVoltageScalingOutputReady,     RO      )

/*----------------------------------------------------------------------------
 * Writer Generators (Dispatched by 5th column: SET_RMW, RO)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a read-modify-write `static inline` setter for multi-field PWR registers.
 * @param  short_name  Snake-case function suffix (e.g., `voltage_scaling_output_selection`).
 * @param  _reg        Target register member in @ref PLAY32_PWR_TypeDef (e.g., `CR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `VOS`).
 * @param  _type       Type suffix matching `PLAY32_PWR_<_reg>_<_type>` (e.g., `VoltageScalingOutputSelection`).
 */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c PWR_##_reg.                     \
     * @param[in] value  Typed value to write (@see PLAY32_PWR_##_reg##_##_type).               \
     */                                                                                         \
    static inline void play32_pwr_set_##short_name(                                             \
        const PLAY32_PWR_##_reg##_##_type value                                                 \
    ) {                                                                                         \
        PLAY32_PWR->_reg = (PLAY32_PWR->_reg & ~(PLAY32_PWR_##_reg##_##_sub_reg##_MSK))         \
            | (((uint32_t)value << (PLAY32_PWR_##_reg##_##_sub_reg##_POS))                      \
            & (PLAY32_PWR_##_reg##_##_sub_reg##_MSK));                                          \
    }

/** @brief Read-only field guard: emits no setter function. */
#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no setter emitted */

/** @brief Dispatches writer generation based on the table's access-mode column. */
#define DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)                           \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)

/*----------------------------------------------------------------------------
 * Reader Generator
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a `static inline` getter for any readable PWR register field.
 * @param  short_name  Snake-case function suffix (e.g., `standby_flag`).
 * @param  _reg        Target register member in @ref PLAY32_PWR_TypeDef (e.g., `CSR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `SBF`).
 * @param  _type       Type suffix matching `PLAY32_PWR_<_reg>_<_type>`.
 */
#define GEN_GET(short_name, _reg, _sub_reg, _type, mode)                                        \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c PWR_##_reg.           \
     * @return Current field value cast to @ref PLAY32_PWR_##_reg##_##_type.                    \
     */                                                                                         \
    static inline PLAY32_PWR_##_reg##_##_type play32_pwr_get_##short_name(void) {               \
        return (PLAY32_PWR_##_reg##_##_type)                                                    \
            ((PLAY32_PWR->_reg & (PLAY32_PWR_##_reg##_##_sub_reg##_MSK))                        \
            >> (PLAY32_PWR_##_reg##_##_sub_reg##_POS));                                         \
    }

/* Instantiate all PWR setter and getter inline functions */
PWR_REGISTERS_TABLE(DISPATCH_WRITER)
PWR_REGISTERS_TABLE(GEN_GET)

#undef GEN_SET_RMW
#undef GEN_RO
#undef DISPATCH_WRITER_IMPL
#undef DISPATCH_WRITER
#undef GEN_GET

/** @} */ /* End of PLAY32_PWR_Driver */
/** @} */ /* End of PLAY32_PWR */

#endif /* PLAY32_PWR_H */
