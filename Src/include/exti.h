/**
 * @file    exti.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for External Interrupt/Event Controller (EXTI) of STM32F401 CCU.
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

#ifndef PLAY32_EXTI_H
#define PLAY32_EXTI_H

#include "exti_types.h"

/**
 * @addtogroup PLAY32_EXTI
 * @{
 */

/**
 * @defgroup PLAY32_EXTI_Driver EXTI Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for the singleton EXTI controller (`PLAY32_EXTI`).
 * @details Maps each interrupt/event mask, edge trigger, software trigger, or pending flag
 *          to its hardware register, bitfield mnemonic, strict typedef from @ref exti_types.h,
 *          and hardware access mode using the signature:
 *          `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_EXTI_TypeDef
 */
#define EXTI_REGISTERS_TABLE(X) \
/*************************** EXTI IMR REGISTER **********************************************************/\
X(interrupt_mask_0,          IMR,          MR0,           InterruptMask0,                    SET_RMW     )\
X(interrupt_mask_1,          IMR,          MR1,           InterruptMask1,                    SET_RMW     )\
X(interrupt_mask_2,          IMR,          MR2,           InterruptMask2,                    SET_RMW     )\
X(interrupt_mask_3,          IMR,          MR3,           InterruptMask3,                    SET_RMW     )\
X(interrupt_mask_4,          IMR,          MR4,           InterruptMask4,                    SET_RMW     )\
X(interrupt_mask_5,          IMR,          MR5,           InterruptMask5,                    SET_RMW     )\
X(interrupt_mask_6,          IMR,          MR6,           InterruptMask6,                    SET_RMW     )\
X(interrupt_mask_7,          IMR,          MR7,           InterruptMask7,                    SET_RMW     )\
X(interrupt_mask_8,          IMR,          MR8,           InterruptMask8,                    SET_RMW     )\
X(interrupt_mask_9,          IMR,          MR9,           InterruptMask9,                    SET_RMW     )\
X(interrupt_mask_10,         IMR,          MR10,          InterruptMask10,                   SET_RMW     )\
X(interrupt_mask_11,         IMR,          MR11,          InterruptMask11,                   SET_RMW     )\
X(interrupt_mask_12,         IMR,          MR12,          InterruptMask12,                   SET_RMW     )\
X(interrupt_mask_13,         IMR,          MR13,          InterruptMask13,                   SET_RMW     )\
X(interrupt_mask_14,         IMR,          MR14,          InterruptMask14,                   SET_RMW     )\
X(interrupt_mask_15,         IMR,          MR15,          InterruptMask15,                   SET_RMW     )\
X(interrupt_mask_16,         IMR,          MR16,          InterruptMask16,                   SET_RMW     )\
X(interrupt_mask_17,         IMR,          MR17,          InterruptMask17,                   SET_RMW     )\
X(interrupt_mask_18,         IMR,          MR18,          InterruptMask18,                   SET_RMW     )\
X(interrupt_mask_21,         IMR,          MR21,          InterruptMask21,                   SET_RMW     )\
X(interrupt_mask_22,         IMR,          MR22,          InterruptMask22,                   SET_RMW     )\
\
/*************************** EXTI EMR REGISTER **********************************************************/\
X(event_mask_0,              EMR,          MR0,           EventMask0,                        SET_RMW     )\
X(event_mask_1,              EMR,          MR1,           EventMask1,                        SET_RMW     )\
X(event_mask_2,              EMR,          MR2,           EventMask2,                        SET_RMW     )\
X(event_mask_3,              EMR,          MR3,           EventMask3,                        SET_RMW     )\
X(event_mask_4,              EMR,          MR4,           EventMask4,                        SET_RMW     )\
X(event_mask_5,              EMR,          MR5,           EventMask5,                        SET_RMW     )\
X(event_mask_6,              EMR,          MR6,           EventMask6,                        SET_RMW     )\
X(event_mask_7,              EMR,          MR7,           EventMask7,                        SET_RMW     )\
X(event_mask_8,              EMR,          MR8,           EventMask8,                        SET_RMW     )\
X(event_mask_9,              EMR,          MR9,           EventMask9,                        SET_RMW     )\
X(event_mask_10,             EMR,          MR10,          EventMask10,                       SET_RMW     )\
X(event_mask_11,             EMR,          MR11,          EventMask11,                       SET_RMW     )\
X(event_mask_12,             EMR,          MR12,          EventMask12,                       SET_RMW     )\
X(event_mask_13,             EMR,          MR13,          EventMask13,                       SET_RMW     )\
X(event_mask_14,             EMR,          MR14,          EventMask14,                       SET_RMW     )\
X(event_mask_15,             EMR,          MR15,          EventMask15,                       SET_RMW     )\
X(event_mask_16,             EMR,          MR16,          EventMask16,                       SET_RMW     )\
X(event_mask_17,             EMR,          MR17,          EventMask17,                       SET_RMW     )\
X(event_mask_18,             EMR,          MR18,          EventMask18,                       SET_RMW     )\
X(event_mask_21,             EMR,          MR21,          EventMask21,                       SET_RMW     )\
X(event_mask_22,             EMR,          MR22,          EventMask22,                       SET_RMW     )\
\
/*************************** EXTI RTSR REGISTER *********************************************************/\
X(rising_trigger_0,          RTSR,         TR0,           RisingTrigger0,                    SET_RMW     )\
X(rising_trigger_1,          RTSR,         TR1,           RisingTrigger1,                    SET_RMW     )\
X(rising_trigger_2,          RTSR,         TR2,           RisingTrigger2,                    SET_RMW     )\
X(rising_trigger_3,          RTSR,         TR3,           RisingTrigger3,                    SET_RMW     )\
X(rising_trigger_4,          RTSR,         TR4,           RisingTrigger4,                    SET_RMW     )\
X(rising_trigger_5,          RTSR,         TR5,           RisingTrigger5,                    SET_RMW     )\
X(rising_trigger_6,          RTSR,         TR6,           RisingTrigger6,                    SET_RMW     )\
X(rising_trigger_7,          RTSR,         TR7,           RisingTrigger7,                    SET_RMW     )\
X(rising_trigger_8,          RTSR,         TR8,           RisingTrigger8,                    SET_RMW     )\
X(rising_trigger_9,          RTSR,         TR9,           RisingTrigger9,                    SET_RMW     )\
X(rising_trigger_10,         RTSR,         TR10,          RisingTrigger10,                   SET_RMW     )\
X(rising_trigger_11,         RTSR,         TR11,          RisingTrigger11,                   SET_RMW     )\
X(rising_trigger_12,         RTSR,         TR12,          RisingTrigger12,                   SET_RMW     )\
X(rising_trigger_13,         RTSR,         TR13,          RisingTrigger13,                   SET_RMW     )\
X(rising_trigger_14,         RTSR,         TR14,          RisingTrigger14,                   SET_RMW     )\
X(rising_trigger_15,         RTSR,         TR15,          RisingTrigger15,                   SET_RMW     )\
X(rising_trigger_16,         RTSR,         TR16,          RisingTrigger16,                   SET_RMW     )\
X(rising_trigger_17,         RTSR,         TR17,          RisingTrigger17,                   SET_RMW     )\
X(rising_trigger_18,         RTSR,         TR18,          RisingTrigger18,                   SET_RMW     )\
X(rising_trigger_21,         RTSR,         TR21,          RisingTrigger21,                   SET_RMW     )\
X(rising_trigger_22,         RTSR,         TR22,          RisingTrigger22,                   SET_RMW     )\
\
/*************************** EXTI FTSR REGISTER *********************************************************/\
X(falling_trigger_0,         FTSR,         TR0,           FallingTrigger0,                   SET_RMW     )\
X(falling_trigger_1,         FTSR,         TR1,           FallingTrigger1,                   SET_RMW     )\
X(falling_trigger_2,         FTSR,         TR2,           FallingTrigger2,                   SET_RMW     )\
X(falling_trigger_3,         FTSR,         TR3,           FallingTrigger3,                   SET_RMW     )\
X(falling_trigger_4,         FTSR,         TR4,           FallingTrigger4,                   SET_RMW     )\
X(falling_trigger_5,         FTSR,         TR5,           FallingTrigger5,                   SET_RMW     )\
X(falling_trigger_6,         FTSR,         TR6,           FallingTrigger6,                   SET_RMW     )\
X(falling_trigger_7,         FTSR,         TR7,           FallingTrigger7,                   SET_RMW     )\
X(falling_trigger_8,         FTSR,         TR8,           FallingTrigger8,                   SET_RMW     )\
X(falling_trigger_9,         FTSR,         TR9,           FallingTrigger9,                   SET_RMW     )\
X(falling_trigger_10,        FTSR,         TR10,          FallingTrigger10,                  SET_RMW     )\
X(falling_trigger_11,        FTSR,         TR11,          FallingTrigger11,                  SET_RMW     )\
X(falling_trigger_12,        FTSR,         TR12,          FallingTrigger12,                  SET_RMW     )\
X(falling_trigger_13,        FTSR,         TR13,          FallingTrigger13,                  SET_RMW     )\
X(falling_trigger_14,        FTSR,         TR14,          FallingTrigger14,                  SET_RMW     )\
X(falling_trigger_15,        FTSR,         TR15,          FallingTrigger15,                  SET_RMW     )\
X(falling_trigger_16,        FTSR,         TR16,          FallingTrigger16,                  SET_RMW     )\
X(falling_trigger_17,        FTSR,         TR17,          FallingTrigger17,                  SET_RMW     )\
X(falling_trigger_18,        FTSR,         TR18,          FallingTrigger18,                  SET_RMW     )\
X(falling_trigger_21,        FTSR,         TR21,          FallingTrigger21,                  SET_RMW     )\
X(falling_trigger_22,        FTSR,         TR22,          FallingTrigger22,                  SET_RMW     )\
\
/*************************** EXTI SWIER REGISTER ********************************************************/\
X(software_interrupt_0,      SWIER,        SWIER0,        SoftwareInterrupt0,                SET_WO      )\
X(software_interrupt_1,      SWIER,        SWIER1,        SoftwareInterrupt1,                SET_WO      )\
X(software_interrupt_2,      SWIER,        SWIER2,        SoftwareInterrupt2,                SET_WO      )\
X(software_interrupt_3,      SWIER,        SWIER3,        SoftwareInterrupt3,                SET_WO      )\
X(software_interrupt_4,      SWIER,        SWIER4,        SoftwareInterrupt4,                SET_WO      )\
X(software_interrupt_5,      SWIER,        SWIER5,        SoftwareInterrupt5,                SET_WO      )\
X(software_interrupt_6,      SWIER,        SWIER6,        SoftwareInterrupt6,                SET_WO      )\
X(software_interrupt_7,      SWIER,        SWIER7,        SoftwareInterrupt7,                SET_WO      )\
X(software_interrupt_8,      SWIER,        SWIER8,        SoftwareInterrupt8,                SET_WO      )\
X(software_interrupt_9,      SWIER,        SWIER9,        SoftwareInterrupt9,                SET_WO      )\
X(software_interrupt_10,     SWIER,        SWIER10,       SoftwareInterrupt10,               SET_WO      )\
X(software_interrupt_11,     SWIER,        SWIER11,       SoftwareInterrupt11,               SET_WO      )\
X(software_interrupt_12,     SWIER,        SWIER12,       SoftwareInterrupt12,               SET_WO      )\
X(software_interrupt_13,     SWIER,        SWIER13,       SoftwareInterrupt13,               SET_WO      )\
X(software_interrupt_14,     SWIER,        SWIER14,       SoftwareInterrupt14,               SET_WO      )\
X(software_interrupt_15,     SWIER,        SWIER15,       SoftwareInterrupt15,               SET_WO      )\
X(software_interrupt_16,     SWIER,        SWIER16,       SoftwareInterrupt16,               SET_WO      )\
X(software_interrupt_17,     SWIER,        SWIER17,       SoftwareInterrupt17,               SET_WO      )\
X(software_interrupt_18,     SWIER,        SWIER18,       SoftwareInterrupt18,               SET_WO      )\
X(software_interrupt_21,     SWIER,        SWIER21,       SoftwareInterrupt21,               SET_WO      )\
X(software_interrupt_22,     SWIER,        SWIER22,       SoftwareInterrupt22,               SET_WO      )\
\
/*************************** EXTI PR REGISTER ***********************************************************/\
X(pending_0,                 PR,           PR0,           Pending0,                          CLEAR_RC_W1 )\
X(pending_1,                 PR,           PR1,           Pending1,                          CLEAR_RC_W1 )\
X(pending_2,                 PR,           PR2,           Pending2,                          CLEAR_RC_W1 )\
X(pending_3,                 PR,           PR3,           Pending3,                          CLEAR_RC_W1 )\
X(pending_4,                 PR,           PR4,           Pending4,                          CLEAR_RC_W1 )\
X(pending_5,                 PR,           PR5,           Pending5,                          CLEAR_RC_W1 )\
X(pending_6,                 PR,           PR6,           Pending6,                          CLEAR_RC_W1 )\
X(pending_7,                 PR,           PR7,           Pending7,                          CLEAR_RC_W1 )\
X(pending_8,                 PR,           PR8,           Pending8,                          CLEAR_RC_W1 )\
X(pending_9,                 PR,           PR9,           Pending9,                          CLEAR_RC_W1 )\
X(pending_10,                PR,           PR10,          Pending10,                         CLEAR_RC_W1 )\
X(pending_11,                PR,           PR11,          Pending11,                         CLEAR_RC_W1 )\
X(pending_12,                PR,           PR12,          Pending12,                         CLEAR_RC_W1 )\
X(pending_13,                PR,           PR13,          Pending13,                         CLEAR_RC_W1 )\
X(pending_14,                PR,           PR14,          Pending14,                         CLEAR_RC_W1 )\
X(pending_15,                PR,           PR15,          Pending15,                         CLEAR_RC_W1 )\
X(pending_16,                PR,           PR16,          Pending16,                         CLEAR_RC_W1 )\
X(pending_17,                PR,           PR17,          Pending17,                         CLEAR_RC_W1 )\
X(pending_18,                PR,           PR18,          Pending18,                         CLEAR_RC_W1 )\
X(pending_21,                PR,           PR21,          Pending21,                         CLEAR_RC_W1 )\
X(pending_22,                PR,           PR22,          Pending22,                         CLEAR_RC_W1 )

/*----------------------------------------------------------------------------
 * Writer & Flag-Clearer Generators (Dispatched by 5th column)
 *----------------------------------------------------------------------------*/

#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c EXTI_##_reg.                    \
     * @param[in] value  Typed value to write (@see PLAY32_EXTI_##_reg##_##_type).              \
     */                                                                                         \
    static inline void play32_exti_set_##short_name(                                            \
        const PLAY32_EXTI_##_reg##_##_type value                                                \
    ) {                                                                                         \
        PLAY32_EXTI->_reg = (PLAY32_EXTI->_reg & ~(PLAY32_EXTI_##_reg##_##_sub_reg##_MSK))      \
            | (((uint32_t)value << (PLAY32_EXTI_##_reg##_##_sub_reg##_POS))                     \
            & (PLAY32_EXTI_##_reg##_##_sub_reg##_MSK));                                         \
    }

#define GEN_SET_WO(short_name, _reg, _sub_reg, _type)                                           \
    /**                                                                                         \
     * @brief  Triggers @c _sub_reg (@c short_name) in @c EXTI_##_reg (single `STR`, `0` ignored).\
     */                                                                                         \
    static inline void play32_exti_trigger_##short_name(void) {                                 \
        PLAY32_EXTI->_reg = PLAY32_EXTI_##_reg##_##_sub_reg##_MSK;                              \
    }

#define GEN_CLEAR_RC_W1(short_name, _reg, _sub_reg, _type)                                      \
    /**                                                                                         \
     * @brief  Atomically clears the @c _sub_reg pending flag (@c short_name) in @c EXTI_##_reg.\
     */                                                                                         \
    static inline void play32_exti_clear_##short_name(void) {                                   \
        PLAY32_EXTI->_reg = PLAY32_EXTI_##_reg##_##_sub_reg##_MSK;                              \
    }

#define DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)                           \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)

/*----------------------------------------------------------------------------
 * Reader Generator
 *----------------------------------------------------------------------------*/

#define GEN_GET(short_name, _reg, _sub_reg, _type, mode)                                        \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c EXTI_##_reg.          \
     * @return Current field value cast to @ref PLAY32_EXTI_##_reg##_##_type.                   \
     */                                                                                         \
    static inline PLAY32_EXTI_##_reg##_##_type play32_exti_get_##short_name(void) {             \
        return (PLAY32_EXTI_##_reg##_##_type)                                                   \
            ((PLAY32_EXTI->_reg & (PLAY32_EXTI_##_reg##_##_sub_reg##_MSK))                      \
            >> (PLAY32_EXTI_##_reg##_##_sub_reg##_POS));                                        \
    }

/* Instantiate all EXTI setter, trigger, clearer, and getter inline functions */
EXTI_REGISTERS_TABLE(DISPATCH_WRITER)
EXTI_REGISTERS_TABLE(GEN_GET)

#undef GEN_SET_RMW
#undef GEN_SET_WO
#undef GEN_CLEAR_RC_W1
#undef DISPATCH_WRITER_IMPL
#undef DISPATCH_WRITER
#undef GEN_GET

/** @} */ /* End of PLAY32_EXTI_Driver */
/** @} */ /* End of PLAY32_EXTI */

#endif /* PLAY32_EXTI_H */
