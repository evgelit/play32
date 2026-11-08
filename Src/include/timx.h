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

#define TIMx_REGISTERS_TABLE(X) \
/*************************************** TIMx CR1 REGISTER ***************************************/\
X(clock_division,                        CR1,     CKD,         ClockDivision                      )\
X(auto_reload_preload_enable,            CR1,     ARPE,        AutoReloadPreloadEnable            )\
X(center_aligned_mode,                   CR1,     CMS,         CenterAlignedModeSelection         )\
X(direction,                             CR1,     DIR,         Direction                          )\
X(one_pulse_mode,                        CR1,     OPM,         OnePulseMode                       )\
X(update_request_source,                 CR1,     URS,         UpdateRequestSource                )\
X(update_disable,                        CR1,     UDIS,        UpdateDisable                      )\
X(counter_enable,                        CR1,     CEN,         CounterEnable                      )\
\
/*************************************** TIMx CR2 REGISTER ***************************************/\
X(t1_selection,                          CR2,     TI1S,        T1Selection                        )\
X(master_mode_selection,                 CR2,     MMS,         MasterModeSelection                )\
X(capture_compare_dma_selection,         CR2,     CCDS,        CaptureCompareDMASelection         )\
\
/*************************************** TIMx SMCR REGISTER **************************************/\
X(slave_mode_selection,                  SMCR,    SMS,         SlaveModeSelection                 )\
X(trigger_selection,                     SMCR,    TS,          TriggerSelection                   )\
X(master_slave_mode,                     SMCR,    MSM,         MasterSlaveMode                    )\
X(ext_trigger_filter,                    SMCR,    ETF,         ExtTriggerFilter                   )\
X(ext_trigger_prescaler_selection,       SMCR,    ETPS,        ExtTriggerPrescalerSelection       )\
X(ext_clock_enable,                      SMCR,    ECE,         ExtClockEnable                     )\
X(ext_trigger_polarity,                  SMCR,    ETP,         ExtTriggerPolarity                 )\
\
/*************************************** TIMx DIER REGISTER **************************************/\
X(update_interrupt_enable,               DIER,    UIE,         UpdateInterruptEnable              )\
X(capture_compare_1_interrupt_enable,    DIER,    CC1IE,       CaptureCompare1InterruptEnable     )\
X(capture_compare_2_interrupt_enable,    DIER,    CC2IE,       CaptureCompare2InterruptEnable     )\
X(capture_compare_3_interrupt_enable,    DIER,    CC3IE,       CaptureCompare3InterruptEnable     )\
X(capture_compare_4_interrupt_enable,    DIER,    CC4IE,       CaptureCompare4InterruptEnable     )\
X(trigger_interrupt_enable,              DIER,    TIE,         TriggerInterruptEnable             )\
X(update_dma_enable,                     DIER,    UDE,         UpdateDMAEnable                    )\
X(capture_compare_1_dma_enable,          DIER,    CC1DE,       CaptureCompare1DMAEnable           )\
X(capture_compare_2_dma_enable,          DIER,    CC2DE,       CaptureCompare2DMAEnable           )\
X(capture_compare_3_dma_enable,          DIER,    CC3DE,       CaptureCompare3DMAEnable           )\
X(capture_compare_4_dma_enable,          DIER,    CC4DE,       CaptureCompare4DMAEnable           )\
X(trigger_dma_enable,                    DIER,    TDE,         TriggerDMAEnable                   )\
\
/*************************************** TIMx EGR REGISTER ***************************************/\
X(update_generation,                     EGR,     UG,          UpdateGeneration                   )\
X(capture_compare_1_generation,          EGR,     CC1G,        CaptureCompare1Generation          )\
X(capture_compare_2_generation,          EGR,     CC2G,        CaptureCompare2Generation          )\
X(capture_compare_3_generation,          EGR,     CC3G,        CaptureCompare3Generation          )\
X(capture_compare_4_generation,          EGR,     CC4G,        CaptureCompare4Generation          )\
X(trigger_generation,                    EGR,     TG,          TriggerGeneration                  )\
\
/*************************************** TIMx CCMR1 REGISTER *************************************/\
X(capture_compare_1_selection,           CCMR1,   CC1S,        CaptureCompare1Selection           )\
X(output_compare_1_fast_enable,          CCMR1,   OC1FE,       OutputCompare1FastEnable           )\
X(output_compare_1_preload_enable,       CCMR1,   OC1PE,       OutputCompare1PreloadEnable        )\
X(output_compare_1_mode,                 CCMR1,   OC1M,        OutputCompare1Mode                 )\
X(output_compare_1_clear_enable,         CCMR1,   OC1CE,       OutputCompare1ClearEnable          )\
X(capture_compare_2_selection,           CCMR1,   CC2S,        CaptureCompare2Selection           )\
X(output_compare_2_fast_enable,          CCMR1,   OC2FE,       OutputCompare2FastEnable           )\
X(output_compare_2_preload_enable,       CCMR1,   OC2PE,       OutputCompare2PreloadEnable        )\
X(output_compare_2_mode,                 CCMR1,   OC2M,        OutputCompare2Mode                 )\
X(output_compare_2_clear_enable,         CCMR1,   OC2CE,       OutputCompare2ClearEnable          )\
X(input_capture_1_prescaler,             CCMR1,   IC1PSC,      InputCapture1Prescaler             )\
X(input_capture_1_filter,                CCMR1,   IC1F,        InputCapture1Filter                )\
X(input_capture_2_prescaler,             CCMR1,   IC2PSC,      InputCapture2Prescaler             )\
X(input_capture_2_filter,                CCMR1,   IC2F,        InputCapture2Filter                )\
\
/*************************************** TIMx CCMR2 REGISTER *************************************/\
X(capture_compare_3_selection,           CCMR2,   CC3S,        CaptureCompare3Selection           )\
X(output_compare_3_fast_enable,          CCMR2,   OC3FE,       OutputCompare3FastEnable           )\
X(output_compare_3_preload_enable,       CCMR2,   OC3PE,       OutputCompare3PreloadEnable        )\
X(output_compare_3_mode,                 CCMR2,   OC3M,        OutputCompare3Mode                 )\
X(output_compare_3_clear_enable,         CCMR2,   OC3CE,       OutputCompare3ClearEnable          )\
X(capture_compare_4_selection,           CCMR2,   CC4S,        CaptureCompare4Selection           )\
X(output_compare_4_fast_enable,          CCMR2,   OC4FE,       OutputCompare4FastEnable           )\
X(output_compare_4_preload_enable,       CCMR2,   OC4PE,       OutputCompare4PreloadEnable        )\
X(output_compare_4_mode,                 CCMR2,   OC4M,        OutputCompare4Mode                 )\
X(output_compare_4_clear_enable,         CCMR2,   OC4CE,       OutputCompare4ClearEnable          )\
X(input_capture_3_prescaler,             CCMR2,   IC3PSC,      InputCapture3Prescaler             )\
X(input_capture_3_filter,                CCMR2,   IC3F,        InputCapture3Filter                )\
X(input_capture_4_prescaler,             CCMR2,   IC4PSC,      InputCapture4Prescaler             )\
X(input_capture_4_filter,                CCMR2,   IC4F,        InputCapture4Filter                )\
\
/*************************************** TIMx CCER REGISTER **************************************/\
X(capture_compare_1_enable,              CCER,    CC1E,        CaptureCompare1Enable              )\
X(capture_compare_1_polarity,            CCER,    CC1P,        CaptureCompare1Polarity            )\
X(capture_compare_1_negative_polarity,   CCER,    CC1NP,       CaptureCompare1NegativePolarity    )\
X(capture_compare_2_enable,              CCER,    CC2E,        CaptureCompare2Enable              )\
X(capture_compare_2_polarity,            CCER,    CC2P,        CaptureCompare2Polarity            )\
X(capture_compare_2_negative_polarity,   CCER,    CC2NP,       CaptureCompare2NegativePolarity    )\
X(capture_compare_3_enable,              CCER,    CC3E,        CaptureCompare3Enable              )\
X(capture_compare_3_polarity,            CCER,    CC3P,        CaptureCompare3Polarity            )\
X(capture_compare_3_negative_polarity,   CCER,    CC3NP,       CaptureCompare3NegativePolarity    )\
X(capture_compare_4_enable,              CCER,    CC4E,        CaptureCompare4Enable              )\
X(capture_compare_4_polarity,            CCER,    CC4P,        CaptureCompare4Polarity            )\
X(capture_compare_4_negative_polarity,   CCER,    CC4NP,       CaptureCompare4NegativePolarity    )\
\
/*************************************** TIMx CNT REGISTER ***************************************/\
X(counter,                               CNT,     CNT,         Counter                            )\
\
/*************************************** TIMx PSC REGISTER ***************************************/\
X(prescaler,                             PSC,     PSC,         Prescaler                          )\
\
/*************************************** TIMx ARR REGISTER ***************************************/\
X(auto_reload_reister,                   ARR,     ARR,         AutoReloadRegister                 )\
\
/*************************************** TIMx CCR1 REGISTER **************************************/\
X(capture_compare_1_reister,             CCR1,    CCR1,        CaptureCompare1Register            )\
\
/*************************************** TIMx CCR1 REGISTER **************************************/\
X(capture_compare_2_reister,             CCR2,    CCR2,        CaptureCompare2Register            )\
\
/*************************************** TIMx CCR1 REGISTER **************************************/\
X(capture_compare_3_reister,             CCR3,    CCR3,        CaptureCompare3Register            )\
\
/*************************************** TIMx CCR1 REGISTER **************************************/\
X(capture_compare_4_reister,             CCR4,    CCR4,        CaptureCompare4Register            )\
\
/*************************************** TIMx DCR REGISTER ***************************************/\
X(dma_base_address,                      DCR,     DBA,         DMABaseAddress                     )\
X(dma_burst_length,                      DCR,     DBL,         DMABurstLength                     )\
\
/*************************************** TIMx DMAR REGISTER **************************************/\
X(dma_burst,                             DMAR,    DMAB,        DMABurst                           )\
\
/*************************************** TIMx OR REGISTER ****************************************/\
X(timer_input_4_remap,                   OR,      TI4_RMP,     TimerInput4Remap                   )\
X(internal_trigger_1_remap,              OR,      ITR1_RMP,    InternalTrigger1Remap              )\

#define TIMx_STATUS_FLAG_TABLE(X) \
/*************************************** TIMx SR REGISTER ****************************************/\
X(update_interrupt_flag,                 SR,      UIF                                             )\
X(capture_compare_1_interrupt_flag,      SR,      CC1IF                                           )\
X(capture_compare_2_interrupt_flag,      SR,      CC2IF                                           )\
X(capture_compare_3_interrupt_flag,      SR,      CC3IF                                           )\
X(capture_compare_4_interrupt_flag,      SR,      CC4IF                                           )\
X(com_interrupt_flag,                    SR,      COMIF                                           )\
X(trigger_interrupt_flag,                SR,      TIF                                             )\
X(break_interrupt_flag,                  SR,      BIF                                             )\
X(capture_compare_1_overcapture_flag,    SR,      CC1OF                                           )\
X(capture_compare_2_overcapture_flag,    SR,      CC2OF                                           )\
X(capture_compare_3_overcapture_flag,    SR,      CC3OF                                           )\
X(capture_compare_4_overcapture_flag,    SR,      CC4OF                                           )\

#define GENERATE_SET_FUNCTION(short_name, _reg, _sub_reg, _type) \
    /** @brief Sets the field short_name in TIMx register. */ \
    static inline void play32_timx_set_##short_name(\
        PLAY32_TIMx_TypeDef *timx, const PLAY32_TIMx_##_reg##_##_type value\
    ) {\
        timx->_reg = (timx->_reg & ~(PLAY32_TIMx_##_reg##_##_sub_reg##_MSK)) \
            | (((uint32_t)value << (PLAY32_TIMx_##_reg##_##_sub_reg##_POS)) & (PLAY32_TIMx_##_reg##_##_sub_reg##_MSK));\
    }

#define GENERATE_GET_FUNCTION(short_name, _reg, _sub_reg, _type) \
    /** @brief Sets the field short_name in TIMx register. */ \
    static inline PLAY32_TIMx_##_reg##_##_type play32_timx_get_##short_name(\
        const PLAY32_TIMx_TypeDef *timx\
    ) { \
        return (PLAY32_TIMx_##_reg##_##_type)\
            ((timx->_reg & (PLAY32_TIMx_##_reg##_##_sub_reg##_MSK)) >> (PLAY32_TIMx_##_reg##_##_sub_reg##_POS)); \
    }

#define GENERATE_RESET_FUNCTION(short_name, _reg, _sub_reg) \
    /** @brief Sets the field short_name in TIMx register. */ \
    static inline void play32_timx_reset_##short_name(\
        PLAY32_TIMx_TypeDef *timx\
    ) { \
        timx->_reg = ~(PLAY32_TIMx_##_reg##_##_sub_reg##_MSK); \
    }\

TIMx_REGISTERS_TABLE(GENERATE_SET_FUNCTION);
TIMx_REGISTERS_TABLE(GENERATE_GET_FUNCTION);
TIMx_STATUS_FLAG_TABLE(GENERATE_RESET_FUNCTION);


#undef AS_SET_FUNCTION
#undef AS_GET_FUNCTION
#undef AS_RESET_FUNCTION
#endif //PLAY32_TIMx_H
