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

/**
 * @addtogroup PLAY32_GPIOx
 * @{
 */

/**
 * @defgroup PLAY32_GPIOx_Driver GPIOx Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for GPIO port registers (GPIOA-GPIOH).
 * @details Maps each pin configuration or data field to its hardware register,
 *          bitfield mnemonic, strict typedef from @ref gpiox_types.h, and hardware access mode
 *          using the signature: `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_GPIOx_TypeDef
 */
#define GPIOx_REGISTERS_TABLE(X) \
/************************ GPIOx MODER REGISTER *********************************/\
X(mode0,                 MODER,     MODER_0,      Mode,                 SET_RMW )\
X(mode1,                 MODER,     MODER_1,      Mode,                 SET_RMW )\
X(mode2,                 MODER,     MODER_2,      Mode,                 SET_RMW )\
X(mode3,                 MODER,     MODER_3,      Mode,                 SET_RMW )\
X(mode4,                 MODER,     MODER_4,      Mode,                 SET_RMW )\
X(mode5,                 MODER,     MODER_5,      Mode,                 SET_RMW )\
X(mode6,                 MODER,     MODER_6,      Mode,                 SET_RMW )\
X(mode7,                 MODER,     MODER_7,      Mode,                 SET_RMW )\
X(mode8,                 MODER,     MODER_8,      Mode,                 SET_RMW )\
X(mode9,                 MODER,     MODER_9,      Mode,                 SET_RMW )\
X(mode10,                MODER,     MODER_10,     Mode,                 SET_RMW )\
X(mode11,                MODER,     MODER_11,     Mode,                 SET_RMW )\
X(mode12,                MODER,     MODER_12,     Mode,                 SET_RMW )\
X(mode13,                MODER,     MODER_13,     Mode,                 SET_RMW )\
X(mode14,                MODER,     MODER_14,     Mode,                 SET_RMW )\
X(mode15,                MODER,     MODER_15,     Mode,                 SET_RMW )\
\
/************************ GPIOx OTYPER REGISTER ********************************/\
X(output_type0,           OTYPER,    OT_0,        OutputType,           SET_RMW )\
X(output_type1,           OTYPER,    OT_1,        OutputType,           SET_RMW )\
X(output_type2,           OTYPER,    OT_2,        OutputType,           SET_RMW )\
X(output_type3,           OTYPER,    OT_3,        OutputType,           SET_RMW )\
X(output_type4,           OTYPER,    OT_4,        OutputType,           SET_RMW )\
X(output_type5,           OTYPER,    OT_5,        OutputType,           SET_RMW )\
X(output_type6,           OTYPER,    OT_6,        OutputType,           SET_RMW )\
X(output_type7,           OTYPER,    OT_7,        OutputType,           SET_RMW )\
X(output_type8,           OTYPER,    OT_8,        OutputType,           SET_RMW )\
X(output_type9,           OTYPER,    OT_9,        OutputType,           SET_RMW )\
X(output_type10,          OTYPER,    OT_10,       OutputType,           SET_RMW )\
X(output_type11,          OTYPER,    OT_11,       OutputType,           SET_RMW )\
X(output_type12,          OTYPER,    OT_12,       OutputType,           SET_RMW )\
X(output_type13,          OTYPER,    OT_13,       OutputType,           SET_RMW )\
X(output_type14,          OTYPER,    OT_14,       OutputType,           SET_RMW )\
X(output_type15,          OTYPER,    OT_15,       OutputType,           SET_RMW )\
\
/************************ GPIOx PUPDR REGISTER *********************************/\
X(pull_up_pull_down0,     PUPDR,     PUPDR_0,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down1,     PUPDR,     PUPDR_1,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down2,     PUPDR,     PUPDR_2,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down3,     PUPDR,     PUPDR_3,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down4,     PUPDR,     PUPDR_4,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down5,     PUPDR,     PUPDR_5,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down6,     PUPDR,     PUPDR_6,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down7,     PUPDR,     PUPDR_7,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down8,     PUPDR,     PUPDR_8,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down9,     PUPDR,     PUPDR_9,     PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down10,    PUPDR,     PUPDR_10,    PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down11,    PUPDR,     PUPDR_11,    PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down12,    PUPDR,     PUPDR_12,    PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down13,    PUPDR,     PUPDR_13,    PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down14,    PUPDR,     PUPDR_14,    PullUpPullDown,       SET_RMW )\
X(pull_up_pull_down15,    PUPDR,     PUPDR_15,    PullUpPullDown,       SET_RMW )\
\
/************************ GPIOx IDR REGISTER ***********************************/\
X(input_direction0,       IDR,       IDR_0,       InputDirection,       RO      )\
X(input_direction1,       IDR,       IDR_1,       InputDirection,       RO      )\
X(input_direction2,       IDR,       IDR_2,       InputDirection,       RO      )\
X(input_direction3,       IDR,       IDR_3,       InputDirection,       RO      )\
X(input_direction4,       IDR,       IDR_4,       InputDirection,       RO      )\
X(input_direction5,       IDR,       IDR_5,       InputDirection,       RO      )\
X(input_direction6,       IDR,       IDR_6,       InputDirection,       RO      )\
X(input_direction7,       IDR,       IDR_7,       InputDirection,       RO      )\
X(input_direction8,       IDR,       IDR_8,       InputDirection,       RO      )\
X(input_direction9,       IDR,       IDR_9,       InputDirection,       RO      )\
X(input_direction10,      IDR,       IDR_10,      InputDirection,       RO      )\
X(input_direction11,      IDR,       IDR_11,      InputDirection,       RO      )\
X(input_direction12,      IDR,       IDR_12,      InputDirection,       RO      )\
X(input_direction13,      IDR,       IDR_13,      InputDirection,       RO      )\
X(input_direction14,      IDR,       IDR_14,      InputDirection,       RO      )\
X(input_direction15,      IDR,       IDR_15,      InputDirection,       RO      )\
\
/************************ GPIOx ODR REGISTER ***********************************/\
X(output_direction0,      ODR,       ODR_0,       OutputDirection,      SET_RMW )\
X(output_direction1,      ODR,       ODR_1,       OutputDirection,      SET_RMW )\
X(output_direction2,      ODR,       ODR_2,       OutputDirection,      SET_RMW )\
X(output_direction3,      ODR,       ODR_3,       OutputDirection,      SET_RMW )\
X(output_direction4,      ODR,       ODR_4,       OutputDirection,      SET_RMW )\
X(output_direction5,      ODR,       ODR_5,       OutputDirection,      SET_RMW )\
X(output_direction6,      ODR,       ODR_6,       OutputDirection,      SET_RMW )\
X(output_direction7,      ODR,       ODR_7,       OutputDirection,      SET_RMW )\
X(output_direction8,      ODR,       ODR_8,       OutputDirection,      SET_RMW )\
X(output_direction9,      ODR,       ODR_9,       OutputDirection,      SET_RMW )\
X(output_direction10,     ODR,       ODR_10,      OutputDirection,      SET_RMW )\
X(output_direction11,     ODR,       ODR_11,      OutputDirection,      SET_RMW )\
X(output_direction12,     ODR,       ODR_12,      OutputDirection,      SET_RMW )\
X(output_direction13,     ODR,       ODR_13,      OutputDirection,      SET_RMW )\
X(output_direction14,     ODR,       ODR_14,      OutputDirection,      SET_RMW )\
X(output_direction15,     ODR,       ODR_15,      OutputDirection,      SET_RMW )\
\
/************************ GPIOx BSRR REGISTER **********************************/\
X(bit_set0,               BSRR,      BS_0,        BitSet,               SET_WO  )\
X(bit_set1,               BSRR,      BS_1,        BitSet,               SET_WO  )\
X(bit_set2,               BSRR,      BS_2,        BitSet,               SET_WO  )\
X(bit_set3,               BSRR,      BS_3,        BitSet,               SET_WO  )\
X(bit_set4,               BSRR,      BS_4,        BitSet,               SET_WO  )\
X(bit_set5,               BSRR,      BS_5,        BitSet,               SET_WO  )\
X(bit_set6,               BSRR,      BS_6,        BitSet,               SET_WO  )\
X(bit_set7,               BSRR,      BS_7,        BitSet,               SET_WO  )\
X(bit_set8,               BSRR,      BS_8,        BitSet,               SET_WO  )\
X(bit_set9,               BSRR,      BS_9,        BitSet,               SET_WO  )\
X(bit_set10,              BSRR,      BS_10,       BitSet,               SET_WO  )\
X(bit_set11,              BSRR,      BS_11,       BitSet,               SET_WO  )\
X(bit_set12,              BSRR,      BS_12,       BitSet,               SET_WO  )\
X(bit_set13,              BSRR,      BS_13,       BitSet,               SET_WO  )\
X(bit_set14,              BSRR,      BS_14,       BitSet,               SET_WO  )\
X(bit_set15,              BSRR,      BS_15,       BitSet,               SET_WO  )\
X(bit_reset0,             BSRR,      BR_0,        BitReset,             SET_WO  )\
X(bit_reset1,             BSRR,      BR_1,        BitReset,             SET_WO  )\
X(bit_reset2,             BSRR,      BR_2,        BitReset,             SET_WO  )\
X(bit_reset3,             BSRR,      BR_3,        BitReset,             SET_WO  )\
X(bit_reset4,             BSRR,      BR_4,        BitReset,             SET_WO  )\
X(bit_reset5,             BSRR,      BR_5,        BitReset,             SET_WO  )\
X(bit_reset6,             BSRR,      BR_6,        BitReset,             SET_WO  )\
X(bit_reset7,             BSRR,      BR_7,        BitReset,             SET_WO  )\
X(bit_reset8,             BSRR,      BR_8,        BitReset,             SET_WO  )\
X(bit_reset9,             BSRR,      BR_9,        BitReset,             SET_WO  )\
X(bit_reset10,            BSRR,      BR_10,       BitReset,             SET_WO  )\
X(bit_reset11,            BSRR,      BR_11,       BitReset,             SET_WO  )\
X(bit_reset12,            BSRR,      BR_12,       BitReset,             SET_WO  )\
X(bit_reset13,            BSRR,      BR_13,       BitReset,             SET_WO  )\
X(bit_reset14,            BSRR,      BR_14,       BitReset,             SET_WO  )\
X(bit_reset15,            BSRR,      BR_15,       BitReset,             SET_WO  )\
\
/************************ GPIOx AFRL REGISTER **********************************/\
X(alternate_function0,    AFRL,      AFRL_0,      AlternateFunction,    SET_RMW )\
X(alternate_function1,    AFRL,      AFRL_1,      AlternateFunction,    SET_RMW )\
X(alternate_function2,    AFRL,      AFRL_2,      AlternateFunction,    SET_RMW )\
X(alternate_function3,    AFRL,      AFRL_3,      AlternateFunction,    SET_RMW )\
X(alternate_function4,    AFRL,      AFRL_4,      AlternateFunction,    SET_RMW )\
X(alternate_function5,    AFRL,      AFRL_5,      AlternateFunction,    SET_RMW )\
X(alternate_function6,    AFRL,      AFRL_6,      AlternateFunction,    SET_RMW )\
X(alternate_function7,    AFRL,      AFRL_7,      AlternateFunction,    SET_RMW )\
\
/************************ GPIOx AFRH REGISTER **********************************/\
X(alternate_function8,    AFRH,      AFRH_8,      AlternateFunction,    SET_RMW )\
X(alternate_function9,    AFRH,      AFRH_9,      AlternateFunction,    SET_RMW )\
X(alternate_function10,   AFRH,      AFRH_10,     AlternateFunction,    SET_RMW )\
X(alternate_function11,   AFRH,      AFRH_11,     AlternateFunction,    SET_RMW )\
X(alternate_function12,   AFRH,      AFRH_12,     AlternateFunction,    SET_RMW )\
X(alternate_function13,   AFRH,      AFRH_13,     AlternateFunction,    SET_RMW )\
X(alternate_function14,   AFRH,      AFRH_14,     AlternateFunction,    SET_RMW )\
X(alternate_function15,   AFRH,      AFRH_15,     AlternateFunction,    SET_RMW )

/**
 * @brief  X-Macro descriptor entry for the GPIO configuration lock register (`GPIOx_LCKR`).
 * @param  X  Generator macro invoked with `(short_name, reg)`.
 * @see    GEN_LOCK_FUNCTION
 */
#define GPIOx_LOCK_REGISTER(X) X(lock, LCKR)

/**
 * @brief  X-Macro descriptor entry for atomic multi-pin set/reset operations (`GPIOx_BSRR`).
 * @param  X  Generator macro invoked with `(short_name, reg)`.
 * @see    GEN_BULK_SET_FUNCTION
 */
#define GPIOx_BULK_SET(X) X(bulk_set, BSRR)

/**
 * @brief  X-Macro descriptor entry for atomic multi-pin toggle operations (`GPIOx_BSRR`).
 * @param  X  Generator macro invoked with `(short_name, reg)`.
 * @see    GEN_TOGGLE_FUNCTION
 */
#define GPIOx_TOGGLE(X) X(toggle, BSRR)

/*----------------------------------------------------------------------------
 * Writer Generators (Dispatched by 5th column: SET_RMW, SET_WO, RO)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a read-modify-write `static inline` setter for multi-pin GPIO registers.
 * @param  short_name  Snake-case function suffix (e.g., `mode9`).
 * @param  _reg        Target register member in @ref PLAY32_GPIOx_TypeDef (e.g., `MODER`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `MODER_9`).
 * @param  _type       Type suffix matching `PLAY32_GPIOx_<_reg>_<_type>` (e.g., `Mode`).
 */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                                     \
    /**                                                                                                    \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c GPIOx_##_reg.                              \
     * @param[in,out] gpiox  Pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     * @param[in]     value  Typed value to write (@see PLAY32_GPIOx_##_reg##_##_type).                    \
     */                                                                                                    \
    static inline void play32_gpiox_set_##short_name(                                                      \
        PLAY32_GPIOx_TypeDef *gpiox,                                                                       \
        const PLAY32_GPIOx_##_reg##_##_type value                                                          \
    ) {                                                                                                    \
        gpiox->_reg = (gpiox->_reg & ~(PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK))                            \
            | (((uint32_t)value << (PLAY32_GPIOx_##_reg##_##_sub_reg##_POS))                               \
            & (PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK));                                                   \
    }

/**
 * @brief  Generates an atomic single-write `static inline` setter for write-only `GPIOx_BSRR`.
 * @details Compiles to a single `STR` instruction with zero bus read latency and full ISR safety.
 * @param  short_name  Snake-case function suffix (e.g., `bit_set9` or `bit_reset9`).
 * @param  _reg        Target register member (`BSRR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_MSK` macro (e.g., `BS_9` or `BR_9`).
 * @param  _type       Type suffix (`BitSet` or `BitReset`).
 */
#define GEN_SET_WO(short_name, _reg, _sub_reg, _type)                                                      \
    /**                                                                                                    \
     * @brief  Atomically triggers @c short_name (@c _sub_reg) in write-only @c GPIOx_##_reg.              \
     * @param[in,out] gpiox  Pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     */                                                                                                    \
    static inline void play32_gpiox_set_##short_name(                                                      \
        PLAY32_GPIOx_TypeDef *gpiox                                                                        \
    ) {                                                                                                    \
        gpiox->_reg = PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK;                                              \
    }

/** @brief Read-only field guard: emits no setter function. */
#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no setter emitted */

/** @brief Dispatches writer generation based on the table's access-mode column. */
#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                  \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

/*----------------------------------------------------------------------------
 * Reader Generators (Skips write-only BSRR fields automatically)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a `static inline` getter for a readable GPIOx register field.
 * @param  short_name  Snake-case function suffix (e.g., `input_direction9`).
 * @param  _reg        Target register member in @ref PLAY32_GPIOx_TypeDef (e.g., `IDR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `IDR_9`).
 * @param  _type       Type suffix matching `PLAY32_GPIOx_<_reg>_<_type>` (e.g., `InputDirection`).
 */
#define GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)                                   \
    /**                                                                                     \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c GPIOx_##_reg.     \
     * @param[in] gpiox  Const pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     * @return Current field value cast to @ref PLAY32_GPIOx_##_reg##_##_type.              \
     */                                                                                     \
    static inline PLAY32_GPIOx_##_reg##_##_type play32_gpiox_get_##short_name(              \
        const PLAY32_GPIOx_TypeDef *gpiox                                                   \
    ) {                                                                                     \
        return (PLAY32_GPIOx_##_reg##_##_type)                                              \
            ((gpiox->_reg & (PLAY32_GPIOx_##_reg##_##_sub_reg##_MSK))                       \
            >> (PLAY32_GPIOx_##_reg##_##_sub_reg##_POS));                                   \
    }

#define GET_SET_RMW(short_name, _reg, _sub_reg, _type) GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_RO(short_name, _reg, _sub_reg, _type)      GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_SET_WO(short_name, _reg, _sub_reg, _type)  /* Write-only BSRR: no getter emitted */

/** @brief Dispatches reader generation based on the table's access-mode column. */
#define DISPATCH_READER(short_name, _reg, _sub_reg, _type, mode)                            \
    GET_##mode(short_name, _reg, _sub_reg, _type)

/**
 * @brief  Generates a `static inline` hardware configuration lock function for `GPIOx_LCKR`.
 * @details Executes the mandatory STM32F4 4-step `LCKK` (bit 16) write-key sequence to freeze
 *          the configuration registers (`MODER`, `OTYPER`, `OSPEEDR`, `PUPDR`, `AFRL`, `AFRH`)
 *          for all pins selected in `lock_mask`.
 * @param  short_name  Snake-case function suffix (e.g., `lock`).
 * @param  reg         Target lock register member in @ref PLAY32_GPIOx_TypeDef (`LCKR`).
 */
#define GEN_LOCK_FUNCTION(short_name, reg)                                             \
    /**                                                                                     \
     * @brief  Locks the configuration of selected GPIO pins until the next MCU reset.      \
     * @note   Executes the hardware `LCKK` (bit 16) sequence on `GPIOx_##reg`:             \
     *         1. Write `LCKK = 1` + `lock_mask`                                            \
     *         2. Write `LCKK = 0` + `lock_mask`                                            \
     *         3. Write `LCKK = 1` + `lock_mask`                                            \
     *         4. Read `LCKR` (dummy read required by hardware)                             \
     *         5. Read `LCKR` to confirm `LCKK == 1`.                                       \
     * @warning Once locked, pin direction, output type, speed, pull resistors, and         \
     *          alternate function settings cannot be modified until a system reset.        \
     *          Interrupts should be disabled around this call if an ISR accesses `LCKR`.   \
     * @param[in,out] gpiox      Pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     * @param[in]     lock_mask  Bitmask of pins to lock (bitwise OR of @ref PLAY32_GPIOx_PinList). \
     * @return `true` if the port lock key (`LCKK`) was successfully activated; `false` otherwise. \
     */                                                                                     \
    static inline bool play32_gpiox_##short_name(                                           \
        PLAY32_GPIOx_TypeDef *gpiox,                                                        \
        uint32_t lock_mask                                                                  \
    ) {                                                                                     \
        lock_mask &= 0x0000FFFFUL;                                                          \
        gpiox->reg = (1UL << 16) | lock_mask;                                               \
        gpiox->reg = lock_mask;                                                             \
        gpiox->reg = (1UL << 16) | lock_mask;                                               \
        (void)gpiox->reg;                                                                   \
        return ((gpiox->reg & (1UL << 16)) != 0UL);                                         \
    }

/**
 * @brief  Generates a `static inline` atomic bulk pin set/reset function for `GPIOx_BSRR`.
 * @details Combines set bits (`enable` in `[15:0]`) and reset bits (`disable` in `[31:16]`)
 *          into a single 32-bit write to `GPIOx_BSRR`.
 * @param  short_name  Snake-case function suffix (e.g., `bulk_set`).
 * @param  reg         Target bit set/reset register member in @ref PLAY32_GPIOx_TypeDef (`BSRR`).
 */
#define GEN_BULK_SET_FUNCTION(short_name, reg)                                         \
    /**                                                                                     \
     * @brief  Atomically sets and resets multiple GPIO pins in a single bus write.         \
     * @note   Writes `enable` to `BS[15:0]` and `disable` to `BR[31:16]` of `GPIOx_##reg`  \
     *         without performing a read-modify-write cycle.                                \
     * @warning If the same pin bit is present in both `enable` and `disable`, the set      \
     *          action (`BSy`) takes hardware priority over reset (`BRy`).                  \
     * @param[in,out] gpiox    Pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     * @param[in]     enable   Bitmask of pins to drive high (bitwise OR of @ref PLAY32_GPIOx_PinList). \
     * @param[in]     disable  Bitmask of pins to drive low (bitwise OR of @ref PLAY32_GPIOx_PinList). \
     */                                                                                     \
    static inline void play32_gpiox_##short_name(                                           \
        PLAY32_GPIOx_TypeDef *gpiox,                                                        \
        uint32_t enable,                                                                    \
        uint32_t disable                                                                    \
    ) {                                                                                     \
        gpiox->reg = ((disable & 0xFFFFUL) << 16)                                           \
            | (enable & 0xFFFFUL);                                                          \
    }

/**
 * @brief  Generates a `static inline` pin toggle function backed by `GPIOx_BSRR`.
 * @details Reads the current `ODR` state and writes complementary set/reset masks to `BSRR`
 *          so unmasked pins on the port remain completely untouched.
 * @param  short_name  Snake-case function suffix (e.g., `toggle`).
 * @param  reg         Target bit set/reset register member in @ref PLAY32_GPIOx_TypeDef (`BSRR`).
 */
#define GEN_TOGGLE_FUNCTION(short_name, reg)                                                                  \
    /**                                                                                                       \
     * @brief  Toggles the output state of selected GPIO pins via `GPIOx_##reg`.                              \
     * @note   Reads `GPIOx_ODR` once and atomically drives currently high pins low                           \
     *         (`BR[31:16]`) and currently low pins high (`BS[15:0]`) without disturbing                      \
     *         other pins on the same port.                                                                   \
     * @param[in,out] gpiox     Pointer to GPIOx peripheral instance (@ref PLAY32_GPIOA - @ref PLAY32_GPIOH). \
     * @param[in]     pin_mask  Bitmask of pins to toggle (bitwise OR of @ref PLAY32_GPIOx_PinList).          \
     */                                                                                                       \
    static inline void play32_gpiox_##short_name(                                                             \
        PLAY32_GPIOx_TypeDef *gpiox,                                                                          \
        uint32_t pin_mask                                                                                     \
    ) {                                                                                                       \
        pin_mask &= 0x0000FFFFUL;                                                                             \
        uint32_t odr = gpiox->ODR;                                                                            \
        gpiox->reg = ((odr & pin_mask) << 16) | (~odr & pin_mask);                                            \
    }

/* Instantiate all GPIOx setter and getter inline functions */
GPIOx_REGISTERS_TABLE(DISPATCH_WRITER)
GPIOx_REGISTERS_TABLE(DISPATCH_READER)
GPIOx_LOCK_REGISTER(GEN_LOCK_FUNCTION);
GPIOx_TOGGLE(GEN_TOGGLE_FUNCTION)

#undef GENERATE_LOCK_FUNCTION
#undef GENERATE_TOGGLE_FUNCTION
#undef GEN_SET_RMW
#undef GEN_SET_WO
#undef GEN_RO
#undef DISPATCH_WRITER
#undef GEN_GET_COMMON
#undef GET_SET_RMW
#undef GET_RO
#undef GET_SET_WO
#undef DISPATCH_READER
#endif //PLAY32_GPIOx_H
