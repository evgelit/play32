/**
 * @file    usart.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for Universal Synchronous/Asynchronous Receiver-Transmitter (USART) of STM32F401 CCU.
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

#ifndef PLAY32_USART_H
#define PLAY32_USART_H

#include "usart_types.h"

/**
 * @addtogroup PLAY32_USART
 * @{
 */

/**
 * @defgroup PLAY32_USART_Driver USART Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for USART registers (`USART1`, `USART2`, `USART6`).
 * @details Maps each status, data, baud-rate, control, or guard-time field to its hardware register,
 *          bitfield mnemonic, strict typedef from @ref usart_types.h, and hardware access mode
 *          using the signature: `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_USART_TypeDef
 */
#define USART_REGISTERS_TABLE(X) \
/************************************************* USART SR REGISTER ***********************************************************/\
X(parity_error,                                    SR,      PE,        ParityError,                                 RO          )\
X(framing_error,                                   SR,      FE,        FramingError,                                RO          )\
X(noise_detected_flag,                             SR,      NF,        NoiseDetectedFlag,                           RO          )\
X(overrun_error,                                   SR,      ORE,       OverrunError,                                RO          )\
X(idle_line_detected,                              SR,      IDLE,      IDLELineDetected,                            RO          )\
X(read_data_register_not_empty,                    SR,      RXNE,      ReadDataRegisterNotEmpty,                    CLEAR_RC_W0 )\
X(transmission_complete,                           SR,      TC,        TransmissionComplete,                        CLEAR_RC_W0 )\
X(transmit_data_register_empty,                    SR,      TXE,       TransmitDataRegisterEmpty,                   RO          )\
X(lin_break_detection_flag,                        SR,      LBD,       LINBreakDetectionFlag,                       CLEAR_RC_W0 )\
X(clear_to_send_flag,                              SR,      CTS,       ClearToSendFlag,                             CLEAR_RC_W0 )\
\
/************************************************* USART DR REGISTER ***********************************************************/\
X(data,                                            DR,      DR,        Data,                                        SET_DIRECT  )\
\
/************************************************* USART BRR REGISTER **********************************************************/\
X(fraction,                                        BRR,     DIV_F,     Fraction,                                    SET_RMW     )\
X(mantissa,                                        BRR,     DIV_M,     Mantissa,                                    SET_RMW     )\
X(baud_rate_register,                              BRR,     FULL,      Full,                                        SET_DIRECT  )\
\
/************************************************* USART CR1 REGISTER ***********************************************************/\
X(send_break,                                      CR1,     SBK,       SendBreak,                                   SET_RMW      )\
X(receiver_wakeup,                                 CR1,     RWU,       ReceiverWakeup,                              SET_RMW      )\
X(receiver_enable,                                 CR1,     RE,        ReceiverEnable,                              SET_RMW      )\
X(transmitter_enable,                              CR1,     TE,        TransmitterEnable,                           SET_RMW      )\
X(idle_interrupt_enable,                           CR1,     IDLEIE,    IDLEInterruptEnable,                         SET_RMW      )\
X(read_data_register_not_empty_interrupt_enable,   CR1,     RXNEIE,    ReadDataRegisterNotEmptyInterruptEnable,     SET_RMW      )\
X(transmission_complete_interrupt_enable,          CR1,     TCIE,      TransmissionCompleteInterruptEnable,         SET_RMW      )\
X(transmit_data_register_empty_interrupt_enable,   CR1,     TXEIE,     TransmitDataRegisterEmptyInterruptEnable,    SET_RMW      )\
X(parity_error_interrupt_enable,                   CR1,     PEIE,      ParityErrorInterruptEnable,                  SET_RMW      )\
X(parity_selection,                                CR1,     PS,        ParitySelection,                             SET_RMW      )\
X(parity_control_enable,                           CR1,     PCE,       ParityControlEnable,                         SET_RMW      )\
X(wakeup_method,                                   CR1,     WAKE,      WakeupMethod,                                SET_RMW      )\
X(word_length,                                     CR1,     M,         WordLength,                                  SET_RMW      )\
X(usart_enable,                                    CR1,     UE,        USARTEnable,                                 SET_RMW      )\
X(oversampling_mode,                               CR1,     OVER8,     OversamplingMode,                            SET_RMW      )\
\
/************************************************* USART CR2 REGISTER ***********************************************************/\
X(address,                                         CR2,     ADD,       Address,                                     SET_RMW      )\
X(lin_break_detection_length,                      CR2,     LBDL,      LINBreakDetectionLength,                     SET_RMW      )\
X(lin_break_detection_interrupt_enable,            CR2,     LBDIE,     LINBreakDetectionInterruptEnable,            SET_RMW      )\
X(last_bit_clock_pulse,                            CR2,     LBCL,      LastBitClockPulse,                           SET_RMW      )\
X(clock_phase,                                     CR2,     CPHA,      ClockPhase,                                  SET_RMW      )\
X(clock_polarity,                                  CR2,     CPOL,      ClockPolarity,                               SET_RMW      )\
X(clock_enable,                                    CR2,     CLKEN,     ClockEnable,                                 SET_RMW      )\
X(stop_bits,                                       CR2,     STOP,      StopBits,                                    SET_RMW      )\
X(lin_mode_enable,                                 CR2,     LINEN,     LINModeEnable,                               SET_RMW      )\
\
/************************************************* USART CR3 REGISTER ***********************************************************/\
X(error_interrupt_enable,                          CR3,     EIE,       ErrorInterruptEnable,                        SET_RMW      )\
X(irda_mode_enable,                                CR3,     IREN,      IrDAModeEnable,                              SET_RMW      )\
X(irda_low_power,                                  CR3,     IRLP,      IrDALowPower,                                SET_RMW      )\
X(half_duplex_selection,                           CR3,     HDSEL,     HalfDuplexSelection,                         SET_RMW      )\
X(smartcard_nack_enable,                           CR3,     NACK,      SmartcardNACKEnable,                         SET_RMW      )\
X(smartcard_mode_enable,                           CR3,     SCEN,      SmartcardModeEnable,                         SET_RMW      )\
X(dma_receiver_enable,                             CR3,     DMAR,      DMAReceiverEnable,                           SET_RMW      )\
X(dma_transmitter_enable,                          CR3,     DMAT,      DMATransmitterEnable,                        SET_RMW      )\
X(rts_enable,                                      CR3,     RTSE,      RTSEnable,                                   SET_RMW      )\
X(cts_enable,                                      CR3,     CTSE,      CTSEnable,                                   SET_RMW      )\
X(cts_interrupt_enable,                            CR3,     CTSIE,     CTSInterruptEnable,                          SET_RMW      )\
X(one_sample_bit_method,                           CR3,     ONEBIT,    OneSampleBitMethod,                          SET_RMW      )\
\
/************************************************* USART GTPR REGISTER **********************************************************/\
X(prescaler,                                       GTPR,    PSC,       Prescaler,                                   SET_RMW      )\
X(guard_time,                                      GTPR,    GT,        GuardTime,                                   SET_RMW      )

/*----------------------------------------------------------------------------
 * Writer & Flag-Clearer Generators (Dispatched by 5th column)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a read-modify-write `static inline` setter for multi-field USART registers.
 * @param  short_name  Snake-case function suffix (e.g., `word_length`).
 * @param  _reg        Target register member in @ref PLAY32_USART_TypeDef (e.g., `CR1`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `M`).
 * @param  _type       Type suffix matching `PLAY32_USART_<_reg>_<_type>` (e.g., `WordLength`).
 */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c USART_##_reg.                   \
     * @param[in] usart  Pointer to the USART peripheral instance (@ref PLAY32_USART1, etc.).   \
     * @param[in] value  Typed value to write (@see PLAY32_USART_##_reg##_##_type).             \
     */                                                                                         \
    static inline void play32_usart_set_##short_name(                                           \
        PLAY32_USART_TypeDef *const usart,                                                      \
        const PLAY32_USART_##_reg##_##_type value                                               \
    ) {                                                                                         \
        usart->_reg = (usart->_reg & ~(PLAY32_USART_##_reg##_##_sub_reg##_MSK))                 \
            | (((uint32_t)value << (PLAY32_USART_##_reg##_##_sub_reg##_POS))                    \
            & (PLAY32_USART_##_reg##_##_sub_reg##_MSK));                                        \
    }

/**
 * @brief  Generates a single-write `static inline` setter for full-width USART registers (`DR`, `BRR`).
 * @details Compiles to a single `STR` instruction without reading the register first
 *          (essential for `USART_DR`, where a read would drain `RDR` and clear `RXNE`).
 * @param  short_name  Snake-case function suffix (e.g., `data`, `baud_rate_register`).
 * @param  _reg        Target register member in @ref PLAY32_USART_TypeDef (`DR` or `BRR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_MSK` macro.
 * @param  _type       Type suffix matching `PLAY32_USART_<_reg>_<_type>`.
 */
#define GEN_SET_DIRECT(short_name, _reg, _sub_reg, _type)                                       \
    /**                                                                                         \
     * @brief  Writes @c short_name directly to @c USART_##_reg without read-modify-write.      \
     * @param[in] usart  Pointer to the USART peripheral instance (@ref PLAY32_USART1, etc.).   \
     * @param[in] value  Typed value to write (@see PLAY32_USART_##_reg##_##_type).             \
     */                                                                                         \
    static inline void play32_usart_set_##short_name(                                           \
        PLAY32_USART_TypeDef *const usart,                                                      \
        const PLAY32_USART_##_reg##_##_type value                                               \
    ) {                                                                                         \
        usart->_reg = ((uint32_t)value & (PLAY32_USART_##_reg##_##_sub_reg##_MSK));             \
    }

/**
 * @brief  Generates an atomic `rc_w0` flag clearer (`usart->SR = ~MSK`) for `USART_SR` clearable flags.
 * @details Avoids read-modify-write hazards so clearing `TC`, `LBD`, or `CTS` never accidentally
 *          clears other active `rc_w0` bits in `USART_SR`.
 * @param  short_name  Snake-case function suffix (e.g., `transmission_complete`).
 * @param  _reg        Target register member in @ref PLAY32_USART_TypeDef (`SR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_MSK` macro (e.g., `TC`).
 * @param  _type       Type suffix matching `PLAY32_USART_<_reg>_<_type>`.
 */
#define GEN_CLEAR_RC_W0(short_name, _reg, _sub_reg, _type)                                      \
    /**                                                                                         \
     * @brief  Atomically clears the @c _sub_reg flag (@c short_name) in @c USART_##_reg.        \
     * @param[in] usart  Pointer to the USART peripheral instance (@ref PLAY32_USART1, etc.).   \
     */                                                                                         \
    static inline void play32_usart_clear_##short_name(                                         \
        PLAY32_USART_TypeDef *const usart                                                       \
    ) {                                                                                         \
        usart->_reg = ~(PLAY32_USART_##_reg##_##_sub_reg##_MSK);                                \
    }

/** @brief Read-only field guard: emits no setter or clearer function. */
#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no writer emitted */

/** @brief Dispatches writer/clearer generation based on the table's access-mode column. */
#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

/*----------------------------------------------------------------------------
 * Reader Generator
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a `static inline` getter for any readable USART register field.
 * @param  short_name  Snake-case function suffix (e.g., `transmit_data_register_empty`).
 * @param  _reg        Target register member in @ref PLAY32_USART_TypeDef (e.g., `SR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `TXE`).
 * @param  _type       Type suffix matching `PLAY32_USART_<_reg>_<_type>`.
 */
#define GEN_GET(short_name, _reg, _sub_reg, _type, mode)                                        \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c USART_##_reg.         \
     * @param[in] usart  Pointer to the USART peripheral instance (@ref PLAY32_USART1, etc.).   \
     * @return Current field value cast to @ref PLAY32_USART_##_reg##_##_type.                  \
     */                                                                                         \
    static inline PLAY32_USART_##_reg##_##_type play32_usart_get_##short_name(                  \
        const PLAY32_USART_TypeDef *const usart                                                 \
    ) {                                                                                         \
        return (PLAY32_USART_##_reg##_##_type)                                                  \
            ((usart->_reg & (PLAY32_USART_##_reg##_##_sub_reg##_MSK))                           \
            >> (PLAY32_USART_##_reg##_##_sub_reg##_POS));                                       \
    }

/* Instantiate all USART setter, clearer, and getter inline functions */
USART_REGISTERS_TABLE(DISPATCH_WRITER);
USART_REGISTERS_TABLE(GEN_GET);

#undef GEN_SET_RMW
#undef GEN_SET_DIRECT
#undef GEN_SET_DIRECT
#undef GEN_CLEAR_RC_W0
#undef GEN_RO
#undef DISPATCH_WRITER
#undef GEN_GET

/** @} */ /* End of PLAY32_USART_Driver */
/** @} */ /* End of PLAY32_USART */

#endif /* PLAY32_USART_H */
