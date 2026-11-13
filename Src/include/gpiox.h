/**
 * @file    gpiox.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for General-Purpose Input-Output (GPIOA-GPIOH) of STM32F401 CCU.
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

#ifndef PLAY32_GPIOx_H
#define PLAY32_GPIOx_H

#include "gpiox_types.h"

#define GPIOx_REGISTERS_TABLE(X) \
/************************ GPIOx MODER REGISTER ************************/\
X(moder0,                 MODER,     MODER_0,     Mode                 )\
X(moder1,                 MODER,     MODER_1,     Mode                 )\
X(moder2,                 MODER,     MODER_2,     Mode                 )\
X(moder3,                 MODER,     MODER_3,     Mode                 )\
X(moder4,                 MODER,     MODER_4,     Mode                 )\
X(moder5,                 MODER,     MODER_5,     Mode                 )\
X(moder6,                 MODER,     MODER_6,     Mode                 )\
X(moder7,                 MODER,     MODER_7,     Mode                 )\
X(moder8,                 MODER,     MODER_8,     Mode                 )\
X(moder9,                 MODER,     MODER_9,     Mode                 )\
X(moder10,                MODER,     MODER_10,    Mode                 )\
X(moder11,                MODER,     MODER_11,    Mode                 )\
X(moder12,                MODER,     MODER_12,    Mode                 )\
X(moder13,                MODER,     MODER_13,    Mode                 )\
X(moder14,                MODER,     MODER_14,    Mode                 )\
X(moder15,                MODER,     MODER_15,    Mode                 )\
\
/************************ GPIOx OTYPER REGISTER ***********************/\
X(output_type0,           OTYPER,    OT_0,        OutputType           )\
X(output_type1,           OTYPER,    OT_1,        OutputType           )\
X(output_type2,           OTYPER,    OT_2,        OutputType           )\
X(output_type3,           OTYPER,    OT_3,        OutputType           )\
X(output_type4,           OTYPER,    OT_4,        OutputType           )\
X(output_type5,           OTYPER,    OT_5,        OutputType           )\
X(output_type6,           OTYPER,    OT_6,        OutputType           )\
X(output_type7,           OTYPER,    OT_7,        OutputType           )\
X(output_type8,           OTYPER,    OT_8,        OutputType           )\
X(output_type9,           OTYPER,    OT_9,        OutputType           )\
X(output_type10,          OTYPER,    OT_10,       OutputType           )\
X(output_type11,          OTYPER,    OT_11,       OutputType           )\
X(output_type12,          OTYPER,    OT_12,       OutputType           )\
X(output_type13,          OTYPER,    OT_13,       OutputType           )\
X(output_type14,          OTYPER,    OT_14,       OutputType           )\
X(output_type15,          OTYPER,    OT_15,       OutputType           )\
\
/************************ GPIOx PUPDR REGISTER ************************/\
X(pull_up_pull_down0,     PUPDR,     PUPDR_0,     PullUpPullDown       )\
X(pull_up_pull_down1,     PUPDR,     PUPDR_1,     PullUpPullDown       )\
X(pull_up_pull_down2,     PUPDR,     PUPDR_2,     PullUpPullDown       )\
X(pull_up_pull_down3,     PUPDR,     PUPDR_3,     PullUpPullDown       )\
X(pull_up_pull_down4,     PUPDR,     PUPDR_4,     PullUpPullDown       )\
X(pull_up_pull_down5,     PUPDR,     PUPDR_5,     PullUpPullDown       )\
X(pull_up_pull_down6,     PUPDR,     PUPDR_6,     PullUpPullDown       )\
X(pull_up_pull_down7,     PUPDR,     PUPDR_7,     PullUpPullDown       )\
X(pull_up_pull_down8,     PUPDR,     PUPDR_8,     PullUpPullDown       )\
X(pull_up_pull_down9,     PUPDR,     PUPDR_9,     PullUpPullDown       )\
X(pull_up_pull_down10,    PUPDR,     PUPDR_10,    PullUpPullDown       )\
X(pull_up_pull_down11,    PUPDR,     PUPDR_11,    PullUpPullDown       )\
X(pull_up_pull_down12,    PUPDR,     PUPDR_12,    PullUpPullDown       )\
X(pull_up_pull_down13,    PUPDR,     PUPDR_13,    PullUpPullDown       )\
X(pull_up_pull_down14,    PUPDR,     PUPDR_14,    PullUpPullDown       )\
X(pull_up_pull_down15,    PUPDR,     PUPDR_15,    PullUpPullDown       )\
\
/************************ GPIOx IDR REGISTER **************************/\
X(input_direction0,       IDR,       IDR_0,       InputDirection       )\
X(input_direction1,       IDR,       IDR_1,       InputDirection       )\
X(input_direction2,       IDR,       IDR_2,       InputDirection       )\
X(input_direction3,       IDR,       IDR_3,       InputDirection       )\
X(input_direction4,       IDR,       IDR_4,       InputDirection       )\
X(input_direction5,       IDR,       IDR_5,       InputDirection       )\
X(input_direction6,       IDR,       IDR_6,       InputDirection       )\
X(input_direction7,       IDR,       IDR_7,       InputDirection       )\
X(input_direction8,       IDR,       IDR_8,       InputDirection       )\
X(input_direction9,       IDR,       IDR_9,       InputDirection       )\
X(input_direction10,      IDR,       IDR_10,      InputDirection       )\
X(input_direction11,      IDR,       IDR_11,      InputDirection       )\
X(input_direction12,      IDR,       IDR_12,      InputDirection       )\
X(input_direction13,      IDR,       IDR_13,      InputDirection       )\
X(input_direction14,      IDR,       IDR_14,      InputDirection       )\
X(input_direction15,      IDR,       IDR_15,      InputDirection       )\
\
/************************ GPIOx ODR REGISTER **************************/\
X(output_direction0,      ODR,       ODR_0,       OutputDirection      )\
X(output_direction1,      ODR,       ODR_1,       OutputDirection      )\
X(output_direction2,      ODR,       ODR_2,       OutputDirection      )\
X(output_direction3,      ODR,       ODR_3,       OutputDirection      )\
X(output_direction4,      ODR,       ODR_4,       OutputDirection      )\
X(output_direction5,      ODR,       ODR_5,       OutputDirection      )\
X(output_direction6,      ODR,       ODR_6,       OutputDirection      )\
X(output_direction7,      ODR,       ODR_7,       OutputDirection      )\
X(output_direction8,      ODR,       ODR_8,       OutputDirection      )\
X(output_direction9,      ODR,       ODR_9,       OutputDirection      )\
X(output_direction10,     ODR,       ODR_10,      OutputDirection      )\
X(output_direction11,     ODR,       ODR_11,      OutputDirection      )\
X(output_direction12,     ODR,       ODR_12,      OutputDirection      )\
X(output_direction13,     ODR,       ODR_13,      OutputDirection      )\
X(output_direction14,     ODR,       ODR_14,      OutputDirection      )\
X(output_direction15,     ODR,       ODR_15,      OutputDirection      )\
\
/************************ GPIOx BSRR REGISTER *************************/\
X(bit_set0,               BSRR,      BS_0,        BitSet               )\
X(bit_set1,               BSRR,      BS_1,        BitSet               )\
X(bit_set2,               BSRR,      BS_2,        BitSet               )\
X(bit_set3,               BSRR,      BS_3,        BitSet               )\
X(bit_set4,               BSRR,      BS_4,        BitSet               )\
X(bit_set5,               BSRR,      BS_5,        BitSet               )\
X(bit_set6,               BSRR,      BS_6,        BitSet               )\
X(bit_set7,               BSRR,      BS_7,        BitSet               )\
X(bit_set8,               BSRR,      BS_8,        BitSet               )\
X(bit_set9,               BSRR,      BS_9,        BitSet               )\
X(bit_set10,              BSRR,      BS_10,       BitSet               )\
X(bit_set11,              BSRR,      BS_11,       BitSet               )\
X(bit_set12,              BSRR,      BS_12,       BitSet               )\
X(bit_set13,              BSRR,      BS_13,       BitSet               )\
X(bit_set14,              BSRR,      BS_14,       BitSet               )\
X(bit_set15,              BSRR,      BS_15,       BitSet               )\
X(bit_reset0,             BSRR,      BR_0,        BitSet               )\
X(bit_reset1,             BSRR,      BR_1,        BitSet               )\
X(bit_reset2,             BSRR,      BR_2,        BitSet               )\
X(bit_reset3,             BSRR,      BR_3,        BitSet               )\
X(bit_reset4,             BSRR,      BR_4,        BitSet               )\
X(bit_reset5,             BSRR,      BR_5,        BitSet               )\
X(bit_reset6,             BSRR,      BR_6,        BitSet               )\
X(bit_reset7,             BSRR,      BR_7,        BitSet               )\
X(bit_reset8,             BSRR,      BR_8,        BitSet               )\
X(bit_reset9,             BSRR,      BR_9,        BitSet               )\
X(bit_reset10,            BSRR,      BR_10,       BitSet               )\
X(bit_reset11,            BSRR,      BR_11,       BitSet               )\
X(bit_reset12,            BSRR,      BR_12,       BitSet               )\
X(bit_reset13,            BSRR,      BR_13,       BitSet               )\
X(bit_reset14,            BSRR,      BR_14,       BitSet               )\
X(bit_reset15,            BSRR,      BR_15,       BitSet               )\
\
/************************ GPIOx AFRL REGISTER *************************/\
X(alternate_function0,    AFRL,      AFRL_0,      AlternateFunction    )\
X(alternate_function1,    AFRL,      AFRL_1,      AlternateFunction    )\
X(alternate_function2,    AFRL,      AFRL_2,      AlternateFunction    )\
X(alternate_function3,    AFRL,      AFRL_3,      AlternateFunction    )\
X(alternate_function4,    AFRL,      AFRL_4,      AlternateFunction    )\
X(alternate_function5,    AFRL,      AFRL_5,      AlternateFunction    )\
X(alternate_function6,    AFRL,      AFRL_6,      AlternateFunction    )\
X(alternate_function7,    AFRL,      AFRL_7,      AlternateFunction    )\
\
/************************ GPIOx AFRH REGISTER *************************/\
X(alternate_function8,    AFRH,      AFRH_8,      AlternateFunction    )\
X(alternate_function9,    AFRH,      AFRH_9,      AlternateFunction    )\
X(alternate_function10,   AFRH,      AFRH_10,     AlternateFunction    )\
X(alternate_function11,   AFRH,      AFRH_11,     AlternateFunction    )\
X(alternate_function12,   AFRH,      AFRH_12,     AlternateFunction    )\
X(alternate_function13,   AFRH,      AFRH_13,     AlternateFunction    )\
X(alternate_function14,   AFRH,      AFRH_14,     AlternateFunction    )\
X(alternate_function15,   AFRH,      AFRH_15,     AlternateFunction    )

#define GPIOx_LOCK_REGISTER(X) X(lock, LCKR)
    
#define GENERATE_SET_FUNCTION(short_name, _reg, _sub_reg, _type)                   \
    /** @brief Sets the field short_name in GPIOx register. */                     \
    static inline void play32_gpiox_set_##short_name(                              \
        PLAY32_GPIOx_TypeDef *gpiox, const PLAY32_GPIOx_##_reg##_##_type value     \
    ) {                                                                            \
        gpiox->_reg = (gpiox->_reg & ~(PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK))    \
            | (((uint32_t)value << (PLAY32_GPIOx_##_reg##_##_sub_reg##_POS))       \
            & (PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK));                           \
    }

#define GENERATE_GET_FUNCTION(short_name, _reg, _sub_reg, _type)                  \
    /** @brief Sets the field short_name in GPIOx register. */                    \
    static inline PLAY32_GPIOx_##_reg##_##_type play32_gpiox_get_##short_name(    \
        const PLAY32_GPIOx_TypeDef *gpiox                                         \
    ) {                                                                           \
        return (PLAY32_GPIOx_##_reg##_##_type)                                    \
            ((gpiox->_reg & (PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK))             \
            >> (PLAY32_GPIOx_##_reg##_##_sub_reg##_POS));                         \
    }

#define GENERATE_LOCK_FUNCTION(short_name, reg)        \
    /** @brief Generate single lock function. */       \
    static inline bool play32_gpiox_##short_name(      \
        PLAY32_GPIOx_TypeDef *gpiox,                   \
        uint32_t lock_mask                             \
    ) {                                                \
        lock_mask &= 0x0000FFFFUL;                     \
        gpiox->reg = (1UL << 16) | lock_mask;          \
        gpiox->reg = lock_mask;                        \
        gpiox->reg = (1UL << 16) | lock_mask;          \
        (void)gpiox->reg;                              \
        return ((gpiox->reg & (1UL << 16)) != 0UL);    \
    }

GPIOx_REGISTERS_TABLE(GENERATE_SET_FUNCTION);
GPIOx_REGISTERS_TABLE(GENERATE_GET_FUNCTION);
GPIOx_LOCK_REGISTER(GENERATE_LOCK_FUNCTION);

#undef GENERATE_SET_FUNCTION
#undef GENERATE_GET_FUNCTION
#undef GENERATE_LOCK_FUNCTION
#endif //PLAY32_GPIOx_H
