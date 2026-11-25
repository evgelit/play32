/**
 * @file    syscfg.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for System Configuration Controller (SYSCFG) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-25
 *
 * @note    Uses advanced Computed Macro Calls for linear register dispatching,
 *          providing zero-cost abstractions and eliminating code duplication.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_SYSCFG_H
#define PLAY32_SYSCFG_H

#include "syscfg_types.h"

/**
 * @addtogroup PLAY32_SYSCFG
 * @{
 */

/**
 * @defgroup PLAY32_SYSCFG_Driver SYSCFG Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for the singleton SYSCFG controller (`PLAY32_SYSCFG`).
 * @details Maps each memory remap, ADC noise reduction, EXTI port multiplexer, or compensation cell
 *          field to its hardware register, bitfield mnemonic, strict typedef from @ref syscfg_types.h,
 *          and hardware access mode using the signature:
 *          `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Remember to enable the `SYSCFG` clock on `APB2` (`play32_rcc_set_syscfg_enable`)
 *          before writing to any `SYSCFG` register.
 * @see    PLAY32_SYSCFG_TypeDef
 */
#define SYSCFG_REGISTERS_TABLE(X) \
/************************************************* SYSCFG MEMRMP REGISTER *********************************************/\
X(memory_mode,                                     MEMRMP,       MEM_MODE,      MemoryMode,                        SET_RMW )\
\
/************************************************* SYSCFG PMC REGISTER ************************************************/\
X(adc1_dc2,                                        PMC,          ADC1DC2,       ADC1DC2,                           SET_RMW )\
\
/************************************************* SYSCFG EXTICR1 REGISTER ********************************************/\
X(external_interrupt_0,                            EXTICR1,      EXTI0,         ExternalInterrupt0,                SET_RMW )\
X(external_interrupt_1,                            EXTICR1,      EXTI1,         ExternalInterrupt1,                SET_RMW )\
X(external_interrupt_2,                            EXTICR1,      EXTI2,         ExternalInterrupt2,                SET_RMW )\
X(external_interrupt_3,                            EXTICR1,      EXTI3,         ExternalInterrupt3,                SET_RMW )\
\
/************************************************* SYSCFG EXTICR2 REGISTER ********************************************/\
X(external_interrupt_4,                            EXTICR2,      EXTI4,         ExternalInterrupt4,                SET_RMW )\
X(external_interrupt_5,                            EXTICR2,      EXTI5,         ExternalInterrupt5,                SET_RMW )\
X(external_interrupt_6,                            EXTICR2,      EXTI6,         ExternalInterrupt6,                SET_RMW )\
X(external_interrupt_7,                            EXTICR2,      EXTI7,         ExternalInterrupt7,                SET_RMW )\
\
/************************************************* SYSCFG EXTICR3 REGISTER ********************************************/\
X(external_interrupt_8,                            EXTICR3,      EXTI8,         ExternalInterrupt8,                SET_RMW )\
X(external_interrupt_9,                            EXTICR3,      EXTI9,         ExternalInterrupt9,                SET_RMW )\
X(external_interrupt_10,                           EXTICR3,      EXTI10,        ExternalInterrupt10,               SET_RMW )\
X(external_interrupt_11,                           EXTICR3,      EXTI11,        ExternalInterrupt11,               SET_RMW )\
\
/************************************************* SYSCFG EXTICR4 REGISTER ********************************************/\
X(external_interrupt_12,                           EXTICR4,      EXTI12,        ExternalInterrupt12,               SET_RMW )\
X(external_interrupt_13,                           EXTICR4,      EXTI13,        ExternalInterrupt13,               SET_RMW )\
X(external_interrupt_14,                           EXTICR4,      EXTI14,        ExternalInterrupt14,               SET_RMW )\
X(external_interrupt_15,                           EXTICR4,      EXTI15,        ExternalInterrupt15,               SET_RMW )\
\
/************************************************* SYSCFG CMPCR REGISTER **********************************************/\
X(compensation_cell_power_down,                    CMPCR,        CMP_PD,        CompensationCellPowerDown,         SET_RMW )\
X(ready,                                           CMPCR,        READY,         Ready,                             RO      )

/*----------------------------------------------------------------------------
 * Writer Generators (Dispatched by 5th column: SET_RMW, RO)
 *----------------------------------------------------------------------------*/

#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c SYSCFG_##_reg.                  \
     * @param[in] value  Typed value to write (@see PLAY32_SYSCFG_##_reg##_##_type).            \
     */                                                                                         \
    static inline void play32_syscfg_set_##short_name(                                          \
        const PLAY32_SYSCFG_##_reg##_##_type value                                              \
    ) {                                                                                         \
        PLAY32_SYSCFG->_reg = (PLAY32_SYSCFG->_reg & ~(PLAY32_SYSCFG_##_reg##_##_sub_reg##_MSK))\
            | (((uint32_t)value << (PLAY32_SYSCFG_##_reg##_##_sub_reg##_POS))                   \
            & (PLAY32_SYSCFG_##_reg##_##_sub_reg##_MSK));                                       \
    }

#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no setter emitted */

#define DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)                           \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)

/*----------------------------------------------------------------------------
 * Reader Generator
 *----------------------------------------------------------------------------*/

#define GEN_GET(short_name, _reg, _sub_reg, _type, mode)                                        \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c SYSCFG_##_reg.        \
     * @return Current field value cast to @ref PLAY32_SYSCFG_##_reg##_##_type.                 \
     */                                                                                         \
    static inline PLAY32_SYSCFG_##_reg##_##_type play32_syscfg_get_##short_name(void) {         \
        return (PLAY32_SYSCFG_##_reg##_##_type)                                                 \
            ((PLAY32_SYSCFG->_reg & (PLAY32_SYSCFG_##_reg##_##_sub_reg##_MSK))                  \
            >> (PLAY32_SYSCFG_##_reg##_##_sub_reg##_POS));                                      \
    }

/* Instantiate all SYSCFG setter and getter inline functions */
SYSCFG_REGISTERS_TABLE(DISPATCH_WRITER)
SYSCFG_REGISTERS_TABLE(GEN_GET)

#undef GEN_SET_RMW
#undef GEN_RO
#undef DISPATCH_WRITER_IMPL
#undef DISPATCH_WRITER
#undef GEN_GET

/** @} */ /* End of PLAY32_SYSCFG_Driver */
/** @} */ /* End of PLAY32_SYSCFG */

#endif /* PLAY32_SYSCFG_H */
