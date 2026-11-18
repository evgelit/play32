/**
* @file    timx.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for General-Purpose Timers (TIM2-TIM5) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-08
 *
 * @note    Uses advanced Computed Macro Calls for linear register dispatching,
 *          providing zero-cost abstractions and eliminating code duplication.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_TIMx_H
#define PLAY32_TIMx_H

#include "timx_types.h"

/**
 * @addtogroup PLAY32_TIMx
 * @{
 */

/**
 * @defgroup PLAY32_TIMx_Driver TIMx Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for writable/control fields of TIM2-TIM5.
 * @details Maps each logical timer parameter to its hardware register, bitfield mnemonic,
 *          and strict typedef from @ref timx_types.h using the column signature:
 *          `X(func_suffix, reg_name, bit_name, type_suffix)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @note   Read-only status fields (such as `TIMx_SR` interrupt and overcapture flags)
 *         are intentionally excluded from write-accessor generation or handled separately.
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_TIMx_TypeDef
 */
#define TIMx_REGISTERS_TABLE(X) \
/*************************************** TIMx CR1 REGISTER ****************************************************/\
X(clock_division,                        CR1,     CKD,         ClockDivision,                          SET_RMW )\
X(auto_reload_preload_enable,            CR1,     ARPE,        AutoReloadPreloadEnable,                SET_RMW )\
X(center_aligned_mode,                   CR1,     CMS,         CenterAlignedModeSelection,             SET_RMW )\
X(direction,                             CR1,     DIR,         Direction,                              SET_RMW )\
X(one_pulse_mode,                        CR1,     OPM,         OnePulseMode,                           SET_RMW )\
X(update_request_source,                 CR1,     URS,         UpdateRequestSource,                    SET_RMW )\
X(update_disable,                        CR1,     UDIS,        UpdateDisable,                          SET_RMW )\
X(counter_enable,                        CR1,     CEN,         CounterEnable,                          SET_RMW )\
\
/*************************************** TIMx CR2 REGISTER ****************************************************/\
X(t1_selection,                          CR2,     TI1S,        T1Selection,                            SET_RMW )\
X(master_mode_selection,                 CR2,     MMS,         MasterModeSelection,                    SET_RMW )\
X(capture_compare_dma_selection,         CR2,     CCDS,        CaptureCompareDMASelection,             SET_RMW )\
\
/*************************************** TIMx SMCR REGISTER ***************************************************/\
X(slave_mode_selection,                  SMCR,    SMS,         SlaveModeSelection,                     SET_RMW )\
X(trigger_selection,                     SMCR,    TS,          TriggerSelection,                       SET_RMW )\
X(master_slave_mode,                     SMCR,    MSM,         MasterSlaveMode,                        SET_RMW )\
X(ext_trigger_filter,                    SMCR,    ETF,         ExtTriggerFilter,                       SET_RMW )\
X(ext_trigger_prescaler_selection,       SMCR,    ETPS,        ExtTriggerPrescalerSelection,           SET_RMW )\
X(ext_clock_enable,                      SMCR,    ECE,         ExtClockEnable,                         SET_RMW )\
X(ext_trigger_polarity,                  SMCR,    ETP,         ExtTriggerPolarity,                     SET_RMW )\
\
/*************************************** TIMx DIER REGISTER ***************************************************/\
X(update_interrupt_enable,               DIER,    UIE,         UpdateInterruptEnable,                  SET_RMW )\
X(capture_compare_1_interrupt_enable,    DIER,    CC1IE,       CaptureCompare1InterruptEnable,         SET_RMW )\
X(capture_compare_2_interrupt_enable,    DIER,    CC2IE,       CaptureCompare2InterruptEnable,         SET_RMW )\
X(capture_compare_3_interrupt_enable,    DIER,    CC3IE,       CaptureCompare3InterruptEnable,         SET_RMW )\
X(capture_compare_4_interrupt_enable,    DIER,    CC4IE,       CaptureCompare4InterruptEnable,         SET_RMW )\
X(trigger_interrupt_enable,              DIER,    TIE,         TriggerInterruptEnable,                 SET_RMW )\
X(update_dma_enable,                     DIER,    UDE,         UpdateDMAEnable,                        SET_RMW )\
X(capture_compare_1_dma_enable,          DIER,    CC1DE,       CaptureCompare1DMAEnable,               SET_RMW )\
X(capture_compare_2_dma_enable,          DIER,    CC2DE,       CaptureCompare2DMAEnable,               SET_RMW )\
X(capture_compare_3_dma_enable,          DIER,    CC3DE,       CaptureCompare3DMAEnable,               SET_RMW )\
X(capture_compare_4_dma_enable,          DIER,    CC4DE,       CaptureCompare4DMAEnable,               SET_RMW )\
X(trigger_dma_enable,                    DIER,    TDE,         TriggerDMAEnable,                       SET_RMW )\
\
/*************************************** TIMx EGR REGISTER ****************************************************/\
X(update_generation,                     EGR,     UG,          UpdateGeneration,                       SET_WO  )\
X(capture_compare_1_generation,          EGR,     CC1G,        CaptureCompare1Generation,              SET_WO  )\
X(capture_compare_2_generation,          EGR,     CC2G,        CaptureCompare2Generation,              SET_WO  )\
X(capture_compare_3_generation,          EGR,     CC3G,        CaptureCompare3Generation,              SET_WO  )\
X(capture_compare_4_generation,          EGR,     CC4G,        CaptureCompare4Generation,              SET_WO  )\
X(trigger_generation,                    EGR,     TG,          TriggerGeneration,                      SET_WO  )\
/*************************************** TIMx CCMR1 REGISTER **************************************************/\
X(capture_compare_1_selection,           CCMR1,   CC1S,        CaptureCompare1Selection,               SET_RMW )\
X(output_compare_1_fast_enable,          CCMR1,   OC1FE,       OutputCompare1FastEnable,               SET_RMW )\
X(output_compare_1_preload_enable,       CCMR1,   OC1PE,       OutputCompare1PreloadEnable,            SET_RMW )\
X(output_compare_1_mode,                 CCMR1,   OC1M,        OutputCompare1Mode,                     SET_RMW )\
X(output_compare_1_clear_enable,         CCMR1,   OC1CE,       OutputCompare1ClearEnable,              SET_RMW )\
X(capture_compare_2_selection,           CCMR1,   CC2S,        CaptureCompare2Selection,               SET_RMW )\
X(output_compare_2_fast_enable,          CCMR1,   OC2FE,       OutputCompare2FastEnable,               SET_RMW )\
X(output_compare_2_preload_enable,       CCMR1,   OC2PE,       OutputCompare2PreloadEnable,            SET_RMW )\
X(output_compare_2_mode,                 CCMR1,   OC2M,        OutputCompare2Mode,                     SET_RMW )\
X(output_compare_2_clear_enable,         CCMR1,   OC2CE,       OutputCompare2ClearEnable,              SET_RMW )\
X(input_capture_1_prescaler,             CCMR1,   IC1PSC,      InputCapture1Prescaler,                 SET_RMW )\
X(input_capture_1_filter,                CCMR1,   IC1F,        InputCapture1Filter,                    SET_RMW )\
X(input_capture_2_prescaler,             CCMR1,   IC2PSC,      InputCapture2Prescaler,                 SET_RMW )\
X(input_capture_2_filter,                CCMR1,   IC2F,        InputCapture2Filter,                    SET_RMW )\
\
/*************************************** TIMx CCMR2 REGISTER **************************************************/\
X(capture_compare_3_selection,           CCMR2,   CC3S,        CaptureCompare3Selection,           SET_RMW     )\
X(output_compare_3_fast_enable,          CCMR2,   OC3FE,       OutputCompare3FastEnable,           SET_RMW     )\
X(output_compare_3_preload_enable,       CCMR2,   OC3PE,       OutputCompare3PreloadEnable,        SET_RMW     )\
X(output_compare_3_mode,                 CCMR2,   OC3M,        OutputCompare3Mode,                 SET_RMW     )\
X(output_compare_3_clear_enable,         CCMR2,   OC3CE,       OutputCompare3ClearEnable,          SET_RMW     )\
X(capture_compare_4_selection,           CCMR2,   CC4S,        CaptureCompare4Selection,           SET_RMW     )\
X(output_compare_4_fast_enable,          CCMR2,   OC4FE,       OutputCompare4FastEnable,           SET_RMW     )\
X(output_compare_4_preload_enable,       CCMR2,   OC4PE,       OutputCompare4PreloadEnable,        SET_RMW     )\
X(output_compare_4_mode,                 CCMR2,   OC4M,        OutputCompare4Mode,                 SET_RMW     )\
X(output_compare_4_clear_enable,         CCMR2,   OC4CE,       OutputCompare4ClearEnable,          SET_RMW     )\
X(input_capture_3_prescaler,             CCMR2,   IC3PSC,      InputCapture3Prescaler,             SET_RMW     )\
X(input_capture_3_filter,                CCMR2,   IC3F,        InputCapture3Filter,                SET_RMW     )\
X(input_capture_4_prescaler,             CCMR2,   IC4PSC,      InputCapture4Prescaler,             SET_RMW     )\
X(input_capture_4_filter,                CCMR2,   IC4F,        InputCapture4Filter,                SET_RMW     )\
\
/*************************************** TIMx CCER REGISTER ***************************************************/\
X(capture_compare_1_enable,              CCER,    CC1E,        CaptureCompare1Enable,              SET_RMW     )\
X(capture_compare_1_polarity,            CCER,    CC1P,        CaptureCompare1Polarity,            SET_RMW     )\
X(capture_compare_1_negative_polarity,   CCER,    CC1NP,       CaptureCompare1NegativePolarity,    SET_RMW     )\
X(capture_compare_2_enable,              CCER,    CC2E,        CaptureCompare2Enable,              SET_RMW     )\
X(capture_compare_2_polarity,            CCER,    CC2P,        CaptureCompare2Polarity,            SET_RMW     )\
X(capture_compare_2_negative_polarity,   CCER,    CC2NP,       CaptureCompare2NegativePolarity,    SET_RMW     )\
X(capture_compare_3_enable,              CCER,    CC3E,        CaptureCompare3Enable,              SET_RMW     )\
X(capture_compare_3_polarity,            CCER,    CC3P,        CaptureCompare3Polarity,            SET_RMW     )\
X(capture_compare_3_negative_polarity,   CCER,    CC3NP,       CaptureCompare3NegativePolarity,    SET_RMW     )\
X(capture_compare_4_enable,              CCER,    CC4E,        CaptureCompare4Enable,              SET_RMW     )\
X(capture_compare_4_polarity,            CCER,    CC4P,        CaptureCompare4Polarity,            SET_RMW     )\
X(capture_compare_4_negative_polarity,   CCER,    CC4NP,       CaptureCompare4NegativePolarity,    SET_RMW     )\
/*************************************** TIMx CNT REGISTER ****************************************************/\
X(counter,                               CNT,     CNT,         Counter,                            SET_DIRECT  )\
\
/*************************************** TIMx PSC REGISTER ****************************************************/\
X(prescaler,                             PSC,     PSC,         Prescaler,                          SET_DIRECT  )\
\
/*************************************** TIMx ARR REGISTER ****************************************************/\
X(auto_reload_register,                  ARR,     ARR,         AutoReloadRegister,                 SET_DIRECT  )\
\
/*************************************** TIMx CCR1 REGISTER ***************************************************/\
X(capture_compare_1_reister,             CCR1,    CCR1,        CaptureCompare1Register,            SET_DIRECT  )\
\
/*************************************** TIMx CCR2 REGISTER ***************************************************/\
X(capture_compare_2_reister,             CCR2,    CCR2,        CaptureCompare2Register,            SET_DIRECT  )\
\
/*************************************** TIMx CCR3 REGISTER ***************************************************/\
X(capture_compare_3_reister,             CCR3,    CCR3,        CaptureCompare3Register,            SET_DIRECT  )\
\
/*************************************** TIMx CCR4 REGISTER ***************************************************/\
X(capture_compare_4_reister,             CCR4,    CCR4,        CaptureCompare4Register,            SET_DIRECT  )\
\
/*************************************** TIMx DCR REGISTER ****************************************************/\
X(dma_base_address,                      DCR,     DBA,         DMABaseAddress,                     SET_RMW     )\
X(dma_burst_length,                      DCR,     DBL,         DMABurstLength,                     SET_RMW     )\
\
/*************************************** TIMx DMAR REGISTER ***************************************************/\
X(dma_burst,                             DMAR,    DMAB,        DMABurst,                           SET_DIRECT  )\
\
/*************************************** TIMx OR REGISTER *****************************************************/\
X(timer_input_4_remap,                   OR,      TI4_RMP,     TimerInput4Remap,                   SET_RMW     )\
X(internal_trigger_1_remap,              OR,      ITR1_RMP,    InternalTrigger1Remap,              SET_RMW     )\
\
/*************************************** TIMx SR REGISTER *****************************************************/\
X(update_interrupt_flag,                 SR,      UIF,         UpdateInterruptFlag,               CLEAR_RC_W0  )\
X(capture_compare_1_interrupt_flag,      SR,      CC1IF,       CaptureCompare1InterruptFlag,      CLEAR_RC_W0  )\
X(capture_compare_2_interrupt_flag,      SR,      CC2IF,       CaptureCompare2InterruptFlag,      CLEAR_RC_W0  )\
X(capture_compare_3_interrupt_flag,      SR,      CC3IF,       CaptureCompare3InterruptFlag,      CLEAR_RC_W0  )\
X(capture_compare_4_interrupt_flag,      SR,      CC4IF,       CaptureCompare4InterruptFlag,      CLEAR_RC_W0  )\
X(com_interrupt_flag,                    SR,      COMIF,       COMInterruptFlag,                  CLEAR_RC_W0  )\
X(trigger_interrupt_flag,                SR,      TIF,         TriggerInterruptFlag,              CLEAR_RC_W0  )\
X(break_interrupt_flag,                  SR,      BIF,         BreakInterruptFlag,                CLEAR_RC_W0  )\
X(capture_compare_1_overcapture_flag,    SR,      CC1OF,       CaptureCompare1OvercaptureFlag,    CLEAR_RC_W0  )\
X(capture_compare_2_overcapture_flag,    SR,      CC2OF,       CaptureCompare2OvercaptureFlag,    CLEAR_RC_W0  )\
X(capture_compare_3_overcapture_flag,    SR,      CC3OF,       CaptureCompare3OvercaptureFlag,    CLEAR_RC_W0  )\
X(capture_compare_4_overcapture_flag,    SR,      CC4OF,       CaptureCompare4OvercaptureFlag,    CLEAR_RC_W0  )

/*----------------------------------------------------------------------------
 * Writer Generators (Dispatched by 5th column: SET_RMW, SET_DIRECT, SET_WO, CLEAR_RC_W0)
 *----------------------------------------------------------------------------*/

/** @brief Read-Modify-Write setter for multi-field control registers. */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                      \
    /**                                                                                     \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c TIMx_##_reg.                \
     * @param[in,out] timx   Pointer to TIMx peripheral instance.                           \
     * @param[in]     value  Typed value to write (@see PLAY32_TIMx_##_reg##_##_type).      \
     */                                                                                     \
    static inline void play32_timx_set_##short_name(                                        \
        PLAY32_TIMx_TypeDef *timx,                                                          \
        const PLAY32_TIMx_##_reg##_##_type value                                            \
    ) {                                                                                     \
        timx->_reg = (timx->_reg & ~(PLAY32_TIMx_##_reg##_##_sub_reg##_MSK))                \
            | (((uint32_t)value << (PLAY32_TIMx_##_reg##_##_sub_reg##_POS))                 \
            & (PLAY32_TIMx_##_reg##_##_sub_reg##_MSK));                                     \
    }

/** @brief Direct write setter for full-width data registers (no read cycle). */
#define GEN_SET_DIRECT(short_name, _reg, _sub_reg, _type)                                   \
    /**                                                                                     \
     * @brief  Writes @c short_name directly to @c TIMx_##_reg without read-modify-write.   \
     * @param[in,out] timx   Pointer to TIMx peripheral instance.                           \
     * @param[in]     value  Value to write (@see PLAY32_TIMx_##_reg##_##_type).            \
     */                                                                                     \
    static inline void play32_timx_set_##short_name(                                        \
        PLAY32_TIMx_TypeDef *timx,                                                          \
        const PLAY32_TIMx_##_reg##_##_type value                                            \
    ) {                                                                                     \
        timx->_reg = (uint32_t)value & (PLAY32_TIMx_##_reg##_##_sub_reg##_MSK);             \
    }

/** @brief Write-only event trigger generator for TIMx_EGR (single STR instruction). */
#define GEN_SET_WO(short_name, _reg, _sub_reg, _type)                                       \
    /**                                                                                     \
     * @brief  Triggers @c short_name (@c _sub_reg) in write-only register @c TIMx_##_reg.  \
     * @param[in,out] timx  Pointer to TIMx peripheral instance.                            \
     */                                                                                     \
    static inline void play32_timx_trigger_##short_name(                                    \
        PLAY32_TIMx_TypeDef *timx                                                           \
    ) {                                                                                     \
        timx->_reg = PLAY32_TIMx_##_reg##_##_sub_reg##_MSK;                                 \
    }

/** @brief Atomic rc_w0 flag clear generator for TIMx_SR (writes 0 to target bit, 1 to others). */
#define GEN_CLEAR_RC_W0(short_name, _reg, _sub_reg, _type)                                  \
    /**                                                                                     \
     * @brief  Atomically clears @c short_name (@c _sub_reg) in @c TIMx_##_reg.             \
     * @param[in,out] timx  Pointer to TIMx peripheral instance.                            \
     */                                                                                     \
    static inline void play32_timx_clear_##short_name(                                      \
        PLAY32_TIMx_TypeDef *timx                                                           \
    ) {                                                                                     \
        timx->_reg = ~(PLAY32_TIMx_##_reg##_##_sub_reg##_MSK);                              \
    }

#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                            \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

/*----------------------------------------------------------------------------
 * Reader Generators (Skips write-only registers automatically)
 *----------------------------------------------------------------------------*/

#define GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)                                   \
    /**                                                                                     \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c TIMx_##_reg.      \
     * @param[in] timx  Const pointer to TIMx peripheral instance.                          \
     * @return Current field value cast to @ref PLAY32_TIMx_##_reg##_##_type.               \
     */                                                                                     \
    static inline PLAY32_TIMx_##_reg##_##_type play32_timx_get_##short_name(                \
        const PLAY32_TIMx_TypeDef *timx                                                     \
    ) {                                                                                     \
        return (PLAY32_TIMx_##_reg##_##_type)                                               \
            ((timx->_reg & (PLAY32_TIMx_##_reg##_##_sub_reg##_MSK))                         \
            >> (PLAY32_TIMx_##_reg##_##_sub_reg##_POS));                                    \
    }

#define GET_SET_RMW(short_name, _reg, _sub_reg, _type)     GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_SET_DIRECT(short_name, _reg, _sub_reg, _type)  GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_CLEAR_RC_W0(short_name, _reg, _sub_reg, _type) GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_SET_WO(short_name, _reg, _sub_reg, _type)      /* Write-only: no getter emitted */

#define DISPATCH_READER(short_name, _reg, _sub_reg, _type, mode)                            \
    GET_##mode(short_name, _reg, _sub_reg, _type)

/* Instantiate all functions */
TIMx_REGISTERS_TABLE(DISPATCH_WRITER);
TIMx_REGISTERS_TABLE(DISPATCH_READER);

#undef GEN_SET_RMW
#undef GEN_SET_DIRECT
#undef GEN_SET_WO
#undef GEN_CLEAR_RC_W0
#undef DISPATCH_WRITER
#undef GEN_GET_COMMON
#undef GET_SET_RMW
#undef GET_SET_DIRECT
#undef GET_CLEAR_RC_W0
#undef GET_SET_WO
#undef DISPATCH_READER

/** @} */ /* End of PLAY32_TIMx_Driver */
/** @} */ /* End of PLAY32_TIMx */

#endif /* PLAY32_TIMx_H */
