/**
 * @file    usart_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for Universal Synchronous/Asynchronous Receiver-Transmitter (USART) of STM32F401 CCU.
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

#ifndef PLAY32_USART_TYPES_H
#define PLAY32_USART_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_USART Universal Synchronous/Asynchronous Receiver-Transmitter (USART)
 * @brief Hardware register map, base addresses, bit masks, and type-safe enumerations for USART.
 * @{
 */

/**
 * @defgroup PLAY32_USART_Memory_Map Peripheral Base Addresses and Register Map
 * @brief APB1/APB2 base address calculations and memory-mapped register structure for USART.
 * @{
 */

/**
 * @brief  Base address of the APB1 peripheral bus (0x40000000).
 * @note   USART2 is mapped onto the APB1 peripheral bus in STM32F401.
 */
#define PLAY32_APB1_PERIPHERAL       (1UL << 30)

/**
 * @brief  Base address of the APB2 peripheral bus (0x40010000).
 * @note   USART1 and USART6 are mapped onto the APB2 peripheral bus in STM32F401.
 */
#define PLAY32_APB2_PERIPHERAL       ((1UL << 30) | (1UL << 16))

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE            (1UL << 10)

/**
 * @brief  APB2 memory slot index for USART1 (offset 4 * 0x0400 = 0x1000).
 * @see    PLAY32_USART1_BASE
 */
#define PLAY32_USART1_BASE_POS       (4U)

/**
 * @brief  APB2 memory slot index for USART6 (offset 5 * 0x0400 = 0x1400).
 * @see    PLAY32_USART6_BASE
 */
#define PLAY32_USART6_BASE_POS       (5U)

/**
 * @brief  APB1 memory slot index for USART2 (offset 17 * 0x0400 = 0x4400).
 * @see    PLAY32_USART2_BASE
 */
#define PLAY32_USART2_BASE_POS       (17U)

/**
 * @brief  USART1 peripheral base address (0x40011000).
 * @note   Computed from @ref PLAY32_APB2_PERIPHERAL and @ref PLAY32_USART1_BASE_POS.
 */
#define PLAY32_USART1_BASE           (PLAY32_APB2_PERIPHERAL + (PLAY32_USART1_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  USART6 peripheral base address (0x40011400).
 * @note   Computed from @ref PLAY32_APB2_PERIPHERAL and @ref PLAY32_USART6_BASE_POS.
 */
#define PLAY32_USART6_BASE           (PLAY32_APB2_PERIPHERAL + (PLAY32_USART6_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  USART2 peripheral base address (0x40004400).
 * @note   Computed from @ref PLAY32_APB1_PERIPHERAL and @ref PLAY32_USART2_BASE_POS.
 */
#define PLAY32_USART2_BASE           (PLAY32_APB1_PERIPHERAL + (PLAY32_USART2_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  Universal Synchronous/Asynchronous Receiver-Transmitter (USART) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 19.6, offsets 0x00-0x18).
 *         Shared identically by `USART1`, `USART2`, and `USART6`.
 */
typedef struct {
    volatile uint32_t SR;   /**< Offset: 0x00 - Status register. */
    volatile uint32_t DR;   /**< Offset: 0x04 - Data register. */
    volatile uint32_t BRR;  /**< Offset: 0x08 - Baud rate register. */
    volatile uint32_t CR1;  /**< Offset: 0x0C - Control register 1. */
    volatile uint32_t CR2;  /**< Offset: 0x10 - Control register 2. */
    volatile uint32_t CR3;  /**< Offset: 0x14 - Control register 3. */
    volatile uint32_t GTPR; /**< Offset: 0x18 - Guard time and prescaler register. */
} PLAY32_USART_TypeDef;

/** @brief USART1 peripheral register map pointer (APB2, 0x40011000). */
#define PLAY32_USART1 ((PLAY32_USART_TypeDef *)PLAY32_USART1_BASE)

/** @brief USART6 peripheral register map pointer (APB2, 0x40011400). */
#define PLAY32_USART6 ((PLAY32_USART_TypeDef *)PLAY32_USART6_BASE)

/** @brief USART2 peripheral register map pointer (APB1, 0x40004400). */
#define PLAY32_USART2 ((PLAY32_USART_TypeDef *)PLAY32_USART2_BASE)

/** @} */ /* End of PLAY32_USART_Memory_Map */

/**
 * @defgroup PLAY32_USART_Common_Types Common USART Enumerations
 * @brief Reusable active-high control switch and hardware status flag enumerations across USART registers.
 * @{
 */
#pragma region USART_COMMON_ENUM

/**
 * @brief  Standard active-high control switch states for USART peripheral and feature bits.
 * @note   Used across USART control registers (`CR1`, `CR2`, `CR3`) where logic '1' activates
 *         a peripheral feature, interrupt, or DMA request, and logic '0' disables it.
 */
typedef enum {
    PLAY32_USART_SWITCH_DISABLED = 0U, /**< Feature, interrupt, or peripheral disabled (0). */
    PLAY32_USART_SWITCH_ENABLED  = 1U  /**< Feature, interrupt, or peripheral enabled (1). */
} PLAY32_USART_Switch;

/**
 * @brief  USART hardware status flag state enumeration.
 * @note   Generic 1-bit status type used across `USART_SR` status fields to indicate
 *         whether a specific hardware event, buffer state, or error condition has occurred.
 * @warning Some `USART_SR` flags are cleared by reading `SR` followed by `DR` (`PE`, `FE`, `NF`, `ORE`, `IDLE`),
 *          while others (`RXNE`, `TC`, `LBD`, `CTS`) are `rc_w0` bits cleared by writing `0` directly to `USART_SR`.
 */
typedef enum {
    PLAY32_USART_FLAG_NOT_SET = 0U, /**< Flag is cleared (no event or error condition occurred). */
    PLAY32_USART_FLAG_SET     = 1U  /**< Flag is set (hardware event or error condition occurred). */
} PLAY32_USART_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_USART_Common_Types */

/**
 * @defgroup PLAY32_USART_SR_Types USART Status Register (USART_SR)
 * @brief Bit positions, masks, and status flag types for USART_SR (offset 0x00).
 * @{
 */
#pragma region USART_SR_REGISTER

#pragma region USART_SR_REGISTER_POSITION
#define PLAY32_USART_SR_PE_POS      (0U) /**< Bit 0: Parity error flag position. */
#define PLAY32_USART_SR_FE_POS      (1U) /**< Bit 1: Framing error flag position. */
#define PLAY32_USART_SR_NF_POS      (2U) /**< Bit 2: Noise detected flag position. */
#define PLAY32_USART_SR_ORE_POS     (3U) /**< Bit 3: Overrun error flag position. */
#define PLAY32_USART_SR_IDLE_POS    (4U) /**< Bit 4: IDLE line detected flag position. */
#define PLAY32_USART_SR_RXNE_POS    (5U) /**< Bit 5: Read data register not empty flag position. */
#define PLAY32_USART_SR_TC_POS      (6U) /**< Bit 6: Transmission complete flag position. */
#define PLAY32_USART_SR_TXE_POS     (7U) /**< Bit 7: Transmit data register empty flag position. */
#define PLAY32_USART_SR_LBD_POS     (8U) /**< Bit 8: LIN break detection flag position. */
#define PLAY32_USART_SR_CTS_POS     (9U) /**< Bit 9: CTS toggle flag position. */
#pragma endregion

#pragma region USART_SR_REGISTER_MASK
#define PLAY32_USART_SR_PE_MSK      (1UL << PLAY32_USART_SR_PE_POS)   /**< Bit 0 mask (0x00000001). */
#define PLAY32_USART_SR_FE_MSK      (1UL << PLAY32_USART_SR_FE_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_USART_SR_NF_MSK      (1UL << PLAY32_USART_SR_NF_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_USART_SR_ORE_MSK     (1UL << PLAY32_USART_SR_ORE_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_USART_SR_IDLE_MSK    (1UL << PLAY32_USART_SR_IDLE_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_USART_SR_RXNE_MSK    (1UL << PLAY32_USART_SR_RXNE_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_USART_SR_TC_MSK      (1UL << PLAY32_USART_SR_TC_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_USART_SR_TXE_MSK     (1UL << PLAY32_USART_SR_TXE_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_USART_SR_LBD_MSK     (1UL << PLAY32_USART_SR_LBD_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_USART_SR_CTS_MSK     (1UL << PLAY32_USART_SR_CTS_POS)  /**< Bit 9 mask (0x00000200). */
#pragma endregion

#pragma region USART_SR_REGISTER_ENUM

/**
 * @brief  Parity error (PE) status flag type.
 * @note   Read-only bit (bit 0 of USART_SR, PE) set by hardware when a parity error occurs
 *         in receiver mode.
 * @warning Cleared by a software sequence: a read to `USART_SR` followed by a read to `USART_DR`.
 *          Wait for `RXNE = 1` before clearing so the error flag corresponds to the valid received byte.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_ParityError;

/**
 * @brief  Framing error (FE) status flag type.
 * @note   Read-only bit (bit 1 of USART_SR, FE) set by hardware when a de-synchronization,
 *         excessive noise, or a break character is detected.
 * @warning Cleared by a software sequence: a read to `USART_SR` followed by a read to `USART_DR`.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_FramingError;

/**
 * @brief  Noise detected (NF) status flag type.
 * @note   Read-only bit (bit 2 of USART_SR, NF) set by hardware when noise is detected on a
 *         received frame (when `ONEBIT = 0` in `USART_CR3`).
 * @warning Cleared by a software sequence: a read to `USART_SR` followed by a read to `USART_DR`.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_NoiseDetectedFlag;

/**
 * @brief  Overrun error (ORE) status flag type.
 * @note   Read-only bit (bit 3 of USART_SR, ORE) set by hardware when the word currently in the
 *         shift register is ready to be transferred into `RDR` while `RXNE = 1`.
 * @warning Cleared by a software sequence: a read to `USART_SR` followed by a read to `USART_DR`.
 *          When set, the `RDR` content is not lost, but the new shift-register word is overwritten.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_OverrunError;

/**
 * @brief  IDLE line detected (IDLE) status flag type.
 * @note   Read-only bit (bit 4 of USART_SR, IDLE) set by hardware when an Idle Line is detected
 *         on `RX` (after at least one received byte).
 * @warning Cleared by a software sequence: a read to `USART_SR` followed by a read to `USART_DR`.
 *          Will not be set again until `RXNE` has been set once more.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_IDLELineDetected;

/**
 * @brief  Read data register not empty (RXNE) status flag type.
 * @note   Read/Clear-by-0 bit (bit 5 of USART_SR, RXNE) set by hardware when the content of the
 *         `RDR` shift register has been transferred to `USART_DR` and is ready to be read.
 * @warning Cleared by reading `USART_DR` (recommended) or by writing `0` directly to `USART_SR`
 *          (only allowed in multi-buffer communication). Never use read-modify-write on `USART_SR`.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_ReadDataRegisterNotEmpty;

/**
 * @brief  Transmission complete (TC) status flag type.
 * @note   Read/Clear-by-0 bit (bit 6 of USART_SR, TC) set by hardware if the transmission of a frame
 *         containing data is complete and `TXE` is set.
 * @warning Cleared by reading `USART_SR` followed by writing `USART_DR`, or by writing `0` directly
 *          to `USART_SR` via @ref play32_usart_clear_transmission_complete.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_TransmissionComplete;

/**
 * @brief  Transmit data register empty (TXE) status flag type.
 * @note   Read-only bit (bit 7 of USART_SR, TXE) set by hardware when the content of the `TDR`
 *         register has been transferred into the shift register.
 * @warning Cleared exclusively by writing to `USART_DR`; cannot be cleared by writing to `USART_SR`.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_TransmitDataRegisterEmpty;

/**
 * @brief  LIN break detection (LBD) status flag type.
 * @note   Read/Clear-by-0 bit (bit 8 of USART_SR, LBD) set by hardware when a LIN break character
 *         (10 or 11 dominant bits per `LBDL`) is detected while `LINEN = 1`.
 * @warning Cleared by software writing `0` directly to `USART_SR` via
 *          @ref play32_usart_clear_lin_break_detection_flag.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_LINBreakDetectionFlag;

/**
 * @brief  Clear To Send (CTS) toggle status flag type.
 * @note   Read/Clear-by-0 bit (bit 9 of USART_SR, CTS) set by hardware when the `nCTS` input toggles
 *         while hardware CTS flow control is enabled (`CTSE = 1` in `USART_CR3`).
 * @warning Cleared by software writing `0` directly to `USART_SR` via
 *          @ref play32_usart_clear_clear_to_send_flag.
 * @see    PLAY32_USART_Flag
 */
typedef PLAY32_USART_Flag PLAY32_USART_SR_ClearToSendFlag;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_SR_Types */

/**
 * @defgroup PLAY32_USART_DR_Types USART Data Register (USART_DR)
 * @brief Bit position, mask, and data word type for USART_DR (offset 0x04).
 * @{
 */
#pragma region USART_DR_REGISTER

#pragma region USART_DR_REGISTER_POSITION
#define PLAY32_USART_DR_DR_POS         (0U) /**< Bits [8:0]: Transmit/Receive data value position. */
#pragma endregion

#pragma region USART_DR_REGISTER_MASK
#define PLAY32_USART_DR_DR_MSK         (0x1FFUL << PLAY32_USART_DR_DR_POS) /**< Bits [8:0] mask (0x000001FF). */
#pragma endregion

#pragma region USART_DR_REGISTER_VALUE

/**
 * @brief  USART Data Register (DR[8:0]) transmit/receive value type.
 * @note   Contains the received or transmitted data character (8-bit or 9-bit depending on the `M` bit
 *         in `USART_CR1`). Reading `USART_DR` returns the received byte from `RDR`; writing `USART_DR`
 *         loads the transmit byte into `TDR`.
 * @warning When parity is enabled (`PCE = 1`), the MSB (bit 7 in 8-bit mode, bit 8 in 9-bit mode)
 *          is overridden by the hardware-computed parity bit on transmission and contains the
 *          received parity bit on read.
 */
typedef uint16_t PLAY32_USART_DR_Data;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_DR_Types */

/**
 * @defgroup PLAY32_USART_BRR_Types USART Baud Rate Register (USART_BRR)
 * @brief Bit positions, masks, and baud-rate divider types for USART_BRR (offset 0x08).
 * @{
 */
#pragma region USART_BRR_REGISTER

#pragma region USART_BRR_REGISTER_POSITION
#define PLAY32_USART_BRR_DIV_F_POS     (0U) /**< Bits [3:0]: Fractional part of USARTDIV position. */
#define PLAY32_USART_BRR_DIV_M_POS     (4U) /**< Bits [15:4]: Mantissa part of USARTDIV position. */
#define PLAY32_USART_BRR_FULL_POS       (0U) /**< Bits [15:0]: Full 16-bit baud-rate register value position. */

#pragma endregion

#pragma region USART_BRR_REGISTER_MASK
#define PLAY32_USART_BRR_DIV_F_MSK     (0xFUL << PLAY32_USART_BRR_DIV_F_POS)   /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_USART_BRR_DIV_M_MSK     (0xFFFUL << PLAY32_USART_BRR_DIV_M_POS) /**< Bits [15:4] mask (0x0000FFF0). */
#define PLAY32_USART_BRR_FULL_MSK       (0xFFFFUL << PLAY32_USART_BRR_FULL_POS) /**< Bits [15:0] mask (0x0000FFFF). */

#pragma endregion

#pragma region USART_BRR_REGISTER_VALUE

/**
 * @brief  USART baud-rate fractional divider (`DIV_Fraction[3:0]`) value type.
 * @note   Read/Write 4-bit field (bits 3:0 of `USART_BRR`, valid range 0 to 15) encoding the
 *         fractional part of `USARTDIV` in sixteenths (when `OVER8 = 0`) or eighths (when `OVER8 = 1`,
 *         in which case bit 3 must be kept cleared at `0`).
 * @warning The baud-rate counters are updated only after writing to the mantissa bytes (`DIV_Mantissa`).
 *          Always write `DIV_Fraction` before `DIV_Mantissa` (or write the full `BRR` register).
 * @see    PLAY32_USART_BRR_Mantissa
 */
typedef uint8_t PLAY32_USART_BRR_Fraction;

/**
 * @brief  USART baud-rate integer divider (`DIV_Mantissa[11:0]`) value type.
 * @note   Read/Write 12-bit field (bits 15:4 of `USART_BRR`, valid range 1 to 4095) encoding the
 *         integer part of `USARTDIV`:
 *         \f$\text{USARTDIV} = \frac{f_{\text{PCLK}}}{8 \times (2 - \text{OVER8}) \times \text{BaudRate}}\f$.
 * @warning `DIV_Mantissa` must not be `0`. Write `DIV_Fraction` first, as writing `DIV_Mantissa`
 *          triggers the hardware reload of the baud-rate divider counters.
 * @see    PLAY32_USART_BRR_Fraction
 */
typedef uint16_t PLAY32_USART_BRR_Mantissa;

/**
 * @brief  Full 16-bit USART Baud Rate Register (`USART_BRR[15:0]`) value type.
 * @note   Combines `DIV_Mantissa[11:0]` in bits `[15:4]` and `DIV_Fraction[3:0]` in bits `[3:0]`
 *         for atomic single-instruction configuration via `SET_DIRECT`.
 *         When `OVER8 = 0`, `BRR = (uint16_t)((f_PCLK + (BaudRate / 2U)) / BaudRate)`.
 * @warning Ensure `USART` is disabled (`UE = 0`) or idle before changing the baud rate.
 * @see    PLAY32_USART_BRR_Mantissa
 * @see    PLAY32_USART_BRR_Fraction
 */
typedef uint16_t PLAY32_USART_BRR_Full;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_BRR_Types */

/**
 * @defgroup PLAY32_USART_CR1_Types USART Control Register 1 (USART_CR1)
 * @brief Bit positions, masks, and control enumerations for USART_CR1 (offset 0x0C).
 * @{
 */
#pragma region USART_CR1_REGISTER

#pragma region USART_CR1_REGISTER_POSITION
#define PLAY32_USART_CR1_SBK_POS       (0U)  /**< Bit 0: Send break position. */
#define PLAY32_USART_CR1_RWU_POS       (1U)  /**< Bit 1: Receiver wakeup mode position. */
#define PLAY32_USART_CR1_RE_POS        (2U)  /**< Bit 2: Receiver enable position. */
#define PLAY32_USART_CR1_TE_POS        (3U)  /**< Bit 3: Transmitter enable position. */
#define PLAY32_USART_CR1_IDLEIE_POS    (4U)  /**< Bit 4: IDLE interrupt enable position. */
#define PLAY32_USART_CR1_RXNEIE_POS    (5U)  /**< Bit 5: Read data register not empty interrupt enable position. */
#define PLAY32_USART_CR1_TCIE_POS      (6U)  /**< Bit 6: Transmission complete interrupt enable position. */
#define PLAY32_USART_CR1_TXEIE_POS     (7U)  /**< Bit 7: Transmit data register empty interrupt enable position. */
#define PLAY32_USART_CR1_PEIE_POS      (8U)  /**< Bit 8: Parity error interrupt enable position. */
#define PLAY32_USART_CR1_PS_POS        (9U)  /**< Bit 9: Parity selection position. */
#define PLAY32_USART_CR1_PCE_POS       (10U) /**< Bit 10: Parity control enable position. */
#define PLAY32_USART_CR1_WAKE_POS      (11U) /**< Bit 11: Receiver wakeup method position. */
#define PLAY32_USART_CR1_M_POS         (12U) /**< Bit 12: Word length position. */
#define PLAY32_USART_CR1_UE_POS        (13U) /**< Bit 13: USART enable position. */
#define PLAY32_USART_CR1_OVER8_POS     (15U) /**< Bit 15: Oversampling mode position. */
#pragma endregion

#pragma region USART_CR1_REGISTER_MASK
#define PLAY32_USART_CR1_SBK_MSK       (1UL << PLAY32_USART_CR1_SBK_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_USART_CR1_RWU_MSK       (1UL << PLAY32_USART_CR1_RWU_POS)    /**< Bit 1 mask (0x00000002). */
#define PLAY32_USART_CR1_RE_MSK        (1UL << PLAY32_USART_CR1_RE_POS)     /**< Bit 2 mask (0x00000004). */
#define PLAY32_USART_CR1_TE_MSK        (1UL << PLAY32_USART_CR1_TE_POS)     /**< Bit 3 mask (0x00000008). */
#define PLAY32_USART_CR1_IDLEIE_MSK    (1UL << PLAY32_USART_CR1_IDLEIE_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_USART_CR1_RXNEIE_MSK    (1UL << PLAY32_USART_CR1_RXNEIE_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_USART_CR1_TCIE_MSK      (1UL << PLAY32_USART_CR1_TCIE_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_USART_CR1_TXEIE_MSK     (1UL << PLAY32_USART_CR1_TXEIE_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_USART_CR1_PEIE_MSK      (1UL << PLAY32_USART_CR1_PEIE_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_USART_CR1_PS_MSK        (1UL << PLAY32_USART_CR1_PS_POS)     /**< Bit 9 mask (0x00000200). */
#define PLAY32_USART_CR1_PCE_MSK       (1UL << PLAY32_USART_CR1_PCE_POS)    /**< Bit 10 mask (0x00000400). */
#define PLAY32_USART_CR1_WAKE_MSK      (1UL << PLAY32_USART_CR1_WAKE_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_USART_CR1_M_MSK         (1UL << PLAY32_USART_CR1_M_POS)      /**< Bit 12 mask (0x00001000). */
#define PLAY32_USART_CR1_UE_MSK        (1UL << PLAY32_USART_CR1_UE_POS)     /**< Bit 13 mask (0x00002000). */
#define PLAY32_USART_CR1_OVER8_MSK     (1UL << PLAY32_USART_CR1_OVER8_POS)  /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region USART_CR1_REGISTER_ENUM

/**
 * @brief  Send break (`SBK`) control state type.
 * @note   Read/Write control bit (bit 0 of USART_CR1, SBK) set by software to transmit
 *         a break character on the `TX` line; cleared automatically by hardware during
 *         the stop bit of the break character.
 * @warning Do not write `1` again until hardware has cleared this bit (`SBK == 0`),
 *          otherwise a second break frame will not be transmitted.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_SendBreak;

/**
 * @brief  Receiver wakeup (`RWU`) mute mode enumeration.
 * @note   Read/Write control bit (bit 1 of USART_CR1, RWU) determining whether the USART
 *         receiver operates normally or stays in mute mode waiting for a wakeup condition.
 * @warning Before putting the USART into mute mode (`RWU = 1`), ensure it is not currently
 *          receiving a data frame (`RXNE == 0`), otherwise the wakeup condition will fail.
 * @see    PLAY32_USART_CR1_WakeupMethod
 */
typedef enum {
    PLAY32_USART_CR1_RECEIVER_WAKEUP_ACTIVE_MODE = 0U, /**< Receiver in active mode (normal reception). */
    PLAY32_USART_CR1_RECEIVER_WAKEUP_MUTE_MODE   = 1U  /**< Receiver in mute mode (silenced until wakeup event). */
} PLAY32_USART_CR1_ReceiverWakeup;

/**
 * @brief  Receiver enable (`RE`) state type.
 * @note   Read/Write control bit (bit 2 of USART_CR1, RE) used to enable or disable the
 *         USART receiver and start searching for a start bit on `RX`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_ReceiverEnable;

/**
 * @brief  Transmitter enable (`TE`) state type.
 * @note   Read/Write control bit (bit 3 of USART_CR1, TE) used to enable or disable the
 *         USART transmitter. Setting `TE` sends an idle preamble frame before the first data byte.
 * @warning When disabling `TE` during an ongoing transfer, wait until `TC == 1` in `USART_SR`
 *          to avoid truncating the frame currently in the shift register.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_TransmitterEnable;

/**
 * @brief  IDLE line interrupt enable (`IDLEIE`) state type.
 * @note   Read/Write control bit (bit 4 of USART_CR1, IDLEIE) used to enable or disable
 *         the USART interrupt request when `IDLE = 1` in `USART_SR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_IDLEInterruptEnable;

/**
 * @brief  Read data register not empty interrupt enable (`RXNEIE`) state type.
 * @note   Read/Write control bit (bit 5 of USART_CR1, RXNEIE) used to enable or disable
 *         the USART interrupt request when `RXNE = 1` or `ORE = 1` in `USART_SR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_ReadDataRegisterNotEmptyInterruptEnable;

/**
 * @brief  Transmission complete interrupt enable (`TCIE`) state type.
 * @note   Read/Write control bit (bit 6 of USART_CR1, TCIE) used to enable or disable
 *         the USART interrupt request when `TC = 1` in `USART_SR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_TransmissionCompleteInterruptEnable;

/**
 * @brief  Transmit data register empty interrupt enable (`TXEIE`) state type.
 * @note   Read/Write control bit (bit 7 of USART_CR1, TXEIE) used to enable or disable
 *         the USART interrupt request when `TXE = 1` in `USART_SR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_TransmitDataRegisterEmptyInterruptEnable;

/**
 * @brief  Parity error interrupt enable (`PEIE`) state type.
 * @note   Read/Write control bit (bit 8 of USART_CR1, PEIE) used to enable or disable
 *         the USART interrupt request when `PE = 1` in `USART_SR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_ParityErrorInterruptEnable;

/**
 * @brief  Parity selection (`PS`) enumeration.
 * @note   Read/Write control bit (bit 9 of USART_CR1, PS) selecting even or odd parity
 *         generation and checking when parity control is enabled (`PCE = 1`).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR1_ParityControlEnable
 */
typedef enum {
    PLAY32_USART_CR1_PARITY_SELECTION_EVEN = 0U, /**< Even parity selected. */
    PLAY32_USART_CR1_PARITY_SELECTION_ODD  = 1U  /**< Odd parity selected. */
} PLAY32_USART_CR1_ParitySelection;

/**
 * @brief  Parity control enable (`PCE`) state type.
 * @note   Read/Write control bit (bit 10 of USART_CR1, PCE) used to enable or disable
 *         hardware parity generation on transmission and parity checking on reception.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). When enabled,
 *          the parity bit is inserted into the MSB position of the data frame.
 * @see    PLAY32_USART_Switch
 * @see    PLAY32_USART_CR1_ParitySelection
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_ParityControlEnable;

/**
 * @brief  Receiver wakeup method (`WAKE`) enumeration.
 * @note   Read/Write control bit (bit 11 of USART_CR1, WAKE) determining the condition
 *         that wakes the USART receiver from mute mode (`RWU = 1`).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR1_ReceiverWakeup
 */
typedef enum {
    PLAY32_USART_CR1_WAKEUP_METHOD_IDLE_LINE    = 0U, /**< Wakeup triggered by an Idle Line on RX. */
    PLAY32_USART_CR1_WAKEUP_METHOD_ADDRESS_MARK = 1U  /**< Wakeup triggered by an Address Mark (MSB = 1). */
} PLAY32_USART_CR1_WakeupMethod;

/**
 * @brief  Data frame word length (`M`) enumeration.
 * @note   Read/Write control bit (bit 12 of USART_CR1, M) selecting 8-bit or 9-bit data word length
 *         (including the parity bit if `PCE = 1`).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 */
typedef enum {
    PLAY32_USART_CR1_WORD_LENGTH_8_BITS = 0U, /**< 1 Start bit, 8 Data bits, n Stop bits. */
    PLAY32_USART_CR1_WORD_LENGTH_9_BITS = 1U  /**< 1 Start bit, 9 Data bits, n Stop bits. */
} PLAY32_USART_CR1_WordLength;

/**
 * @brief  USART peripheral enable (`UE`) state type.
 * @note   Read/Write control bit (bit 13 of USART_CR1, UE) used to enable or disable the
 *         USART prescalers and outputs. Clearing `UE` freezes prescalers and reduces power consumption.
 * @warning Before clearing `UE` to enter Stop mode or change configuration, wait until `TC == 1`
 *          in `USART_SR` so ongoing transmissions are not corrupted.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR1_USARTEnable;

/**
* @brief  Oversampling mode (OVER8) enumeration.
* @note   Read/Write control bit (bit 15 of USART_CR1, OVER8) selecting 16x or 8x oversampling
* for baud-rate recovery and noise tolerance.
* @warning Must only be modified when the USART is disabled (UE = 0). Selecting 8x oversampling
* doubles the maximum achievable baud rate (f_PCLK / 8) at the cost of reduced clock-drift tolerance.
* @see    PLAY32_USART_BRR_Full
*/
typedef enum {
    PLAY32_USART_CR1_OVERSAMPLING_MODE_BY_16 = 0U, /**< Oversampling by 16 (higher tolerance to clock deviations). */
    PLAY32_USART_CR1_OVERSAMPLING_MODE_BY_8  = 1U  /**< Oversampling by 8 (higher maximum baud rate). */
    } PLAY32_USART_CR1_OversamplingMode;
#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_CR1_Types */

/**
 * @defgroup PLAY32_USART_CR2_Types USART Control Register 2 (USART_CR2)
 * @brief Bit positions, masks, and stop-bit / clock / LIN enumerations for USART_CR2 (offset 0x10).
 * @{
 */
#pragma region USART_CR2_REGISTER

#pragma region USART_CR2_REGISTER_POSITION
#define PLAY32_USART_CR2_ADD_POS       (0U)  /**< Bits [3:0]: Address of the USART node position. */
#define PLAY32_USART_CR2_LBDL_POS      (5U)  /**< Bit 5: LIN break detection length position. */
#define PLAY32_USART_CR2_LBDIE_POS     (6U)  /**< Bit 6: LIN break detection interrupt enable position. */
#define PLAY32_USART_CR2_LBCL_POS      (8U)  /**< Bit 8: Last bit clock pulse position. */
#define PLAY32_USART_CR2_CPHA_POS      (9U)  /**< Bit 9: Clock phase position. */
#define PLAY32_USART_CR2_CPOL_POS      (10U) /**< Bit 10: Clock polarity position. */
#define PLAY32_USART_CR2_CLKEN_POS     (11U) /**< Bit 11: Clock enable position. */
#define PLAY32_USART_CR2_STOP_POS      (12U) /**< Bits [13:12]: STOP bits selection position. */
#define PLAY32_USART_CR2_LINEN_POS     (14U) /**< Bit 14: LIN mode enable position. */
#pragma endregion

#pragma region USART_CR2_REGISTER_MASK
#define PLAY32_USART_CR2_ADD_MSK       (0xFUL << PLAY32_USART_CR2_ADD_POS)   /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_USART_CR2_LBDL_MSK      (1UL << PLAY32_USART_CR2_LBDL_POS)    /**< Bit 5 mask (0x00000020). */
#define PLAY32_USART_CR2_LBDIE_MSK     (1UL << PLAY32_USART_CR2_LBDIE_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_USART_CR2_LBCL_MSK      (1UL << PLAY32_USART_CR2_LBCL_POS)    /**< Bit 8 mask (0x00000100). */
#define PLAY32_USART_CR2_CPHA_MSK      (1UL << PLAY32_USART_CR2_CPHA_POS)    /**< Bit 9 mask (0x00000200). */
#define PLAY32_USART_CR2_CPOL_MSK      (1UL << PLAY32_USART_CR2_CPOL_POS)    /**< Bit 10 mask (0x00000400). */
#define PLAY32_USART_CR2_CLKEN_MSK     (1UL << PLAY32_USART_CR2_CLKEN_POS)   /**< Bit 11 mask (0x00000800). */
#define PLAY32_USART_CR2_STOP_MSK      (3UL << PLAY32_USART_CR2_STOP_POS)    /**< Bits [13:12] mask (0x00003000). */
#define PLAY32_USART_CR2_LINEN_MSK     (1UL << PLAY32_USART_CR2_LINEN_POS)   /**< Bit 14 mask (0x00004000). */
#pragma endregion

#pragma region USART_CR2_REGISTER_ENUM

/**
 * @brief  Address of the USART node (`ADD[3:0]`) value type.
 * @note   Read/Write 4-bit field (bits 3:0 of USART_CR2, ADD[3:0], valid range 0 to 15)
 *         defining the 4-bit node address used for multiprocessor communication
 *         wakeup when `WAKE = 1` (Address Mark detection) in `USART_CR1`.
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR1_WakeupMethod
 */
typedef uint8_t PLAY32_USART_CR2_Address;

/**
 * @brief  LIN break detection length (`LBDL`) enumeration.
 * @note   Read/Write control bit (bit 5 of USART_CR2, LBDL) selecting between
 *         10-bit and 11-bit dominant low pulse detection for LIN sync breaks.
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR2_LINModeEnable
 * @see    PLAY32_USART_SR_LINBreakDetectionFlag
 */
typedef enum {
    PLAY32_USART_CR2_LIN_BREAK_DETECTION_LENGTH_10_BIT = 0U, /**< 10-bit break detection. */
    PLAY32_USART_CR2_LIN_BREAK_DETECTION_LENGTH_11_BIT = 1U  /**< 11-bit break detection. */
} PLAY32_USART_CR2_LINBreakDetectionLength;

/**
 * @brief  LIN break detection interrupt enable (`LBDIE`) state type.
 * @note   Read/Write control bit (bit 6 of USART_CR2, LBDIE) used to enable or disable
 *         the USART interrupt request when `LBD = 1` is set in `USART_SR`.
 * @see    PLAY32_USART_Switch
 * @see    PLAY32_USART_SR_LINBreakDetectionFlag
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR2_LINBreakDetectionInterruptEnable;

/**
 * @brief  Last bit clock pulse (`LBCL`) output control enumeration.
 * @note   Read/Write control bit (bit 8 of USART_CR2, LBCL) selecting whether the clock
 *         pulse corresponding to the last transmitted data bit (MSB) is output on `CK`
 *         in synchronous mode.
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR2_ClockEnable
 */
typedef enum {
    PLAY32_USART_CR2_LAST_BIT_CLOCK_PULSE_NOT_OUTPUT = 0U, /**< Clock pulse of the last data bit is not output to the CK pin. */
    PLAY32_USART_CR2_LAST_BIT_CLOCK_PULSE_OUTPUT     = 1U  /**< Clock pulse of the last data bit is output to the CK pin. */
} PLAY32_USART_CR2_LastBitClockPulse;

/**
 * @brief  Synchronous clock phase (`CPHA`) enumeration.
 * @note   Read/Write control bit (bit 9 of USART_CR2, CPHA) selecting the clock transition
 *         edge on `CK` on which data is captured in synchronous mode.
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR2_ClockPolarity
 * @see    PLAY32_USART_CR2_ClockEnable
 */
typedef enum {
    PLAY32_USART_CR2_CLOCK_PHASE_FIRST_EDGE  = 0U, /**< The first clock transition is the first data capture edge. */
    PLAY32_USART_CR2_CLOCK_PHASE_SECOND_EDGE = 1U  /**< The second clock transition is the first data capture edge. */
} PLAY32_USART_CR2_ClockPhase;

/**
 * @brief  Synchronous clock polarity (`CPOL`) enumeration.
 * @note   Read/Write control bit (bit 10 of USART_CR2, CPOL) selecting the steady-state
 *         polarity of the `CK` pin outside data transfers in synchronous mode.
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR2_ClockPhase
 * @see    PLAY32_USART_CR2_ClockEnable
 */
typedef enum {
    PLAY32_USART_CR2_CLOCK_POLARITY_LOW  = 0U, /**< Steady low value on CK pin outside transmission window. */
    PLAY32_USART_CR2_CLOCK_POLARITY_HIGH = 1U  /**< Steady high value on CK pin outside transmission window. */
} PLAY32_USART_CR2_ClockPolarity;

/**
 * @brief  Synchronous clock enable (`CLKEN`) state type.
 * @note   Read/Write control bit (bit 11 of USART_CR2, CLKEN) used to enable or disable
 *         the `CK` synchronous clock output pin.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). Do not enable
 *          simultaneously with LIN mode (`LINEN`), IrDA (`IREN`), or Smartcard (`SCEN`).
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR2_ClockEnable;

/**
 * @brief  STOP bits (`STOP[1:0]`) duration enumeration.
 * @note   Read/Write 2-bit field (bits 13:12 of USART_CR2, STOP[1:0]) configuring the
 *         number of stop bits transmitted at the end of each frame.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). The `0.5` and `1.5`
 *          stop-bit configurations are specifically intended for Smartcard mode.
 */
typedef enum {
    PLAY32_USART_CR2_STOP_BITS_1   = 0U, /**< 1 Stop bit (default). */
    PLAY32_USART_CR2_STOP_BITS_0_5 = 1U, /**< 0.5 Stop bit (Smartcard mode). */
    PLAY32_USART_CR2_STOP_BITS_2   = 2U, /**< 2 Stop bits. */
    PLAY32_USART_CR2_STOP_BITS_1_5 = 3U  /**< 1.5 Stop bits (Smartcard mode). */
} PLAY32_USART_CR2_StopBits;

/**
 * @brief  LIN mode enable (`LINEN`) state type.
 * @note   Read/Write control bit (bit 14 of USART_CR2, LINEN) enabling Local Interconnect
 *         Network (LIN) master/slave break generation and detection capabilities.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). When enabled,
 *          `STOP[1:0]`, `CLKEN`, `SCEN`, `HDSEL`, and `IREN` must be kept cleared (`0`).
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR2_LINModeEnable;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_CR2_Types */

/**
 * @defgroup PLAY32_USART_CR3_Types USART Control Register 3 (USART_CR3)
 * @brief Bit positions, masks, and DMA / flow-control / IrDA / Smartcard types for USART_CR3 (offset 0x14).
 * @{
 */
#pragma region USART_CR3_REGISTER

#pragma region USART_CR3_REGISTER_POSITION
#define PLAY32_USART_CR3_EIE_POS       (0U)  /**< Bit 0: Error interrupt enable position. */
#define PLAY32_USART_CR3_IREN_POS      (1U)  /**< Bit 1: IrDA mode enable position. */
#define PLAY32_USART_CR3_IRLP_POS      (2U)  /**< Bit 2: IrDA low-power mode position. */
#define PLAY32_USART_CR3_HDSEL_POS     (3U)  /**< Bit 3: Half-duplex selection position. */
#define PLAY32_USART_CR3_NACK_POS      (4U)  /**< Bit 4: Smartcard NACK enable position. */
#define PLAY32_USART_CR3_SCEN_POS      (5U)  /**< Bit 5: Smartcard mode enable position. */
#define PLAY32_USART_CR3_DMAR_POS      (6U)  /**< Bit 6: DMA enable receiver position. */
#define PLAY32_USART_CR3_DMAT_POS      (7U)  /**< Bit 7: DMA enable transmitter position. */
#define PLAY32_USART_CR3_RTSE_POS      (8U)  /**< Bit 8: RTS hardware flow control enable position. */
#define PLAY32_USART_CR3_CTSE_POS      (9U)  /**< Bit 9: CTS hardware flow control enable position. */
#define PLAY32_USART_CR3_CTSIE_POS     (10U) /**< Bit 10: CTS interrupt enable position. */
#define PLAY32_USART_CR3_ONEBIT_POS    (11U) /**< Bit 11: One sample bit method enable position. */
#pragma endregion

#pragma region USART_CR3_REGISTER_MASK
#define PLAY32_USART_CR3_EIE_MSK       (1UL << PLAY32_USART_CR3_EIE_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_USART_CR3_IREN_MSK      (1UL << PLAY32_USART_CR3_IREN_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_USART_CR3_IRLP_MSK      (1UL << PLAY32_USART_CR3_IRLP_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_USART_CR3_HDSEL_MSK     (1UL << PLAY32_USART_CR3_HDSEL_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_USART_CR3_NACK_MSK      (1UL << PLAY32_USART_CR3_NACK_POS)   /**< Bit 4 mask (0x00000010). */
#define PLAY32_USART_CR3_SCEN_MSK      (1UL << PLAY32_USART_CR3_SCEN_POS)   /**< Bit 5 mask (0x00000020). */
#define PLAY32_USART_CR3_DMAR_MSK      (1UL << PLAY32_USART_CR3_DMAR_POS)   /**< Bit 6 mask (0x00000040). */
#define PLAY32_USART_CR3_DMAT_MSK      (1UL << PLAY32_USART_CR3_DMAT_POS)   /**< Bit 7 mask (0x00000080). */
#define PLAY32_USART_CR3_RTSE_MSK      (1UL << PLAY32_USART_CR3_RTSE_POS)   /**< Bit 8 mask (0x00000100). */
#define PLAY32_USART_CR3_CTSE_MSK      (1UL << PLAY32_USART_CR3_CTSE_POS)   /**< Bit 9 mask (0x00000200). */
#define PLAY32_USART_CR3_CTSIE_MSK     (1UL << PLAY32_USART_CR3_CTSIE_POS)  /**< Bit 10 mask (0x00000400). */
#define PLAY32_USART_CR3_ONEBIT_MSK    (1UL << PLAY32_USART_CR3_ONEBIT_POS) /**< Bit 11 mask (0x00000800). */
#pragma endregion

#pragma region USART_CR3_REGISTER_ENUM

/**
 * @brief  Error interrupt enable (`EIE`) state type.
 * @note   Read/Write control bit (bit 0 of USART_CR3, EIE) enabling interrupt generation
 *         when `FE = 1`, `ORE = 1`, or `NF = 1` in `USART_SR` during multi-buffer (`DMAR = 1`) reception.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_ErrorInterruptEnable;

/**
 * @brief  IrDA mode enable (`IREN`) state type.
 * @note   Read/Write control bit (bit 1 of USART_CR3, IREN) enabling Infrared Data Association
 *         (IrDA SIR ENDEC) modulation and demodulation.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). Keep `LINEN`, `CLKEN`,
 *          `SCEN`, and `HDSEL` cleared when enabling IrDA mode.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_IrDAModeEnable;

/**
 * @brief  IrDA low-power mode (`IRLP`) selection enumeration.
 * @note   Read/Write control bit (bit 2 of USART_CR3, IRLP) selecting between normal and
 *         low-power IrDA pulse widths (configured via `PSC` in `USART_GTPR`).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR3_IrDAModeEnable
 */
typedef enum {
    PLAY32_USART_CR3_IRDA_LOW_POWER_NORMAL_MODE    = 0U, /**< Normal IrDA mode. */
    PLAY32_USART_CR3_IRDA_LOW_POWER_LOW_POWER_MODE = 1U  /**< Low-power IrDA mode. */
} PLAY32_USART_CR3_IrDALowPower;

/**
 * @brief  Half-duplex single-wire selection (`HDSEL`) state type.
 * @note   Read/Write control bit (bit 3 of USART_CR3, HDSEL) selecting single-wire half-duplex
 *         communication where `TX` and `RX` are internally connected on the `TX` pin.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). Configure `TX` pin as
 *          open-drain with an external pull-up resistor.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_HalfDuplexSelection;

/**
 * @brief  Smartcard NACK transmission enable (`NACK`) state type.
 * @note   Read/Write control bit (bit 4 of USART_CR3, NACK) enabling NACK signal generation
 *         on parity errors during Smartcard reception (`SCEN = 1`).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_Switch
 * @see    PLAY32_USART_CR3_SmartcardModeEnable
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_SmartcardNACKEnable;

/**
 * @brief  Smartcard mode enable (`SCEN`) state type.
 * @note   Read/Write control bit (bit 5 of USART_CR3, SCEN) enabling ISO 7816-3 Smartcard mode.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). Requires 0.5 or 1.5
 *          stop bits (`STOP[1:0]`) and a prescaler value in `USART_GTPR`.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_SmartcardModeEnable;

/**
 * @brief  DMA enable receiver (`DMAR`) state type.
 * @note   Read/Write control bit (bit 6 of USART_CR3, DMAR) enabling DMA requests whenever
 *         `RXNE = 1` in `USART_SR` for multi-buffer reception.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_DMAReceiverEnable;

/**
 * @brief  DMA enable transmitter (`DMAT`) state type.
 * @note   Read/Write control bit (bit 7 of USART_CR3, DMAT) enabling DMA requests whenever
 *         `TXE = 1` in `USART_SR` for multi-buffer transmission.
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_DMATransmitterEnable;

/**
 * @brief  RTS hardware flow control enable (`RTSE`) state type.
 * @note   Read/Write control bit (bit 8 of USART_CR3, RTSE) enabling Request To Send (`nRTS`)
 *         output control (asserted low only when the USART receive buffer is ready for new data).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_RTSEnable;

/**
 * @brief  CTS hardware flow control enable (`CTSE`) state type.
 * @note   Read/Write control bit (bit 9 of USART_CR3, CTSE) enabling Clear To Send (`nCTS`)
 *         input gating (data is transmitted only when `nCTS` is low).
 * @warning Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_Switch
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_CTSEnable;

/**
 * @brief  CTS interrupt enable (`CTSIE`) state type.
 * @note   Read/Write control bit (bit 10 of USART_CR3, CTSIE) enabling interrupt generation
 *         whenever `CTS = 1` is set in `USART_SR` upon an `nCTS` pin toggle.
 * @see    PLAY32_USART_Switch
 * @see    PLAY32_USART_SR_ClearToSendFlag
 */
typedef PLAY32_USART_Switch PLAY32_USART_CR3_CTSInterruptEnable;

/**
 * @brief  One sample bit method (`ONEBIT`) enumeration.
 * @note   Read/Write control bit (bit 11 of USART_CR3, ONEBIT) selecting between 3-sample
 *         majority voting (with noise detection `NF`) and single-sample bit recovery.
 * @warning Must only be modified when the USART is disabled (`UE = 0`). Selecting one-sample
 *          mode increases tolerance to clock deviations in noise-free environments and disables `NF`.
 */
typedef enum {
    PLAY32_USART_CR3_ONE_SAMPLE_BIT_THREE_SAMPLES = 0U, /**< Three-sample bit method (noise detection enabled). */
    PLAY32_USART_CR3_ONE_SAMPLE_BIT_ONE_SAMPLE    = 1U  /**< One-sample bit method (higher clock-drift tolerance, noise detection disabled). */
} PLAY32_USART_CR3_OneSampleBitMethod;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_CR3_Types */

/**
 * @defgroup PLAY32_USART_GTPR_Types USART Guard Time and Prescaler Register (USART_GTPR)
 * @brief Bit positions, masks, and Smartcard/IrDA prescaler and guard-time types for USART_GTPR (offset 0x18).
 * @{
 */
#pragma region USART_GTPR_REGISTER

#pragma region USART_GTPR_REGISTER_POSITION
#define PLAY32_USART_GTPR_PSC_POS      (0U) /**< Bits [7:0]: Prescaler value position (IrDA and Smartcard modes). */
#define PLAY32_USART_GTPR_GT_POS       (8U) /**< Bits [15:8]: Guard time value position (Smartcard mode). */
#pragma endregion

#pragma region USART_GTPR_REGISTER_MASK
#define PLAY32_USART_GTPR_PSC_MSK      (0xFFUL << PLAY32_USART_GTPR_PSC_POS) /**< Bits [7:0] mask (0x000000FF). */
#define PLAY32_USART_GTPR_GT_MSK       (0xFFUL << PLAY32_USART_GTPR_GT_POS)  /**< Bits [15:8] mask (0x0000FF00). */
#pragma endregion

#pragma region USART_GTPR_REGISTER_VALUE

/**
 * @brief  IrDA and Smartcard prescaler value (`PSC[7:0]`) type.
 * @note   Read/Write 8-bit field (bits 7:0 of USART_GTPR, PSC[7:0], valid range 1 to 255):
 *         - **IrDA Normal Mode (`IRLP = 0`):** `PSC` must be set to `1` (divides source clock by 1).
 *         - **IrDA Low-Power Mode (`IRLP = 1`):** Divides the peripheral clock by `PSC` (1 to 255)
 *           to achieve the low-power baud frequency (typically ~1.8432 MHz, range 1.42–2.12 MHz).
 *         - **Smartcard Mode (`SCEN = 1`):** Divides the peripheral clock by `2 * PSC[4:0]`
 *           (valid range `1` to `31`, yielding division factors `2` to `62`; bits `[7:5]` are ignored).
 * @warning Value `0` is reserved and must not be written. Must only be modified when `UE = 0`.
 * @see    PLAY32_USART_CR3_IrDAModeEnable
 * @see    PLAY32_USART_CR3_SmartcardModeEnable
 */
typedef uint8_t PLAY32_USART_GTPR_Prescaler;

/**
 * @brief  Smartcard guard time value (`GT[7:0]`) type.
 * @note   Read/Write 8-bit field (bits 15:8 of USART_GTPR, GT[7:0], valid range 0 to 255)
 *         specifying the guard time in number of baud clocks inserted after the stop bit
 *         before `TC` (Transmission Complete) is asserted in Smartcard mode.
 * @warning Used exclusively when Smartcard mode is enabled (`SCEN = 1` in `USART_CR3`).
 *          Must only be modified when the USART is disabled (`UE = 0`).
 * @see    PLAY32_USART_CR3_SmartcardModeEnable
 */
typedef uint8_t PLAY32_USART_GTPR_GuardTime;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_USART_GTPR_Types */

/** @} */ /* End of PLAY32_USART */
#endif /* PLAY32_USART_TYPES_H */