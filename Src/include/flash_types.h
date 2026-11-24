/**
 * @file    flash_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for Embedded Flash Memory Interface (FLASH) of STM32F401 CCU.
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

#ifndef PLAY32_FLASH_TYPES_H
#define PLAY32_FLASH_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_FLASH Embedded Flash Memory Interface (FLASH)
 * @brief Hardware register map, base address, bit masks, and type-safe enumerations for FLASH.
 * @{
 */

/**
 * @defgroup PLAY32_FLASH_Memory_Map Peripheral Base Address and Register Map
 * @brief AHB1 base address calculation and memory-mapped register structure for FLASH.
 * @{
 */

/**
 * @brief  Base address of the AHB1 peripheral bus (0x40020000).
 * @note   FLASH interface registers are mapped onto the AHB1 peripheral bus in STM32F401.
 */
#define PLAY32_AHB1_PERIPHERAL      ((1UL << 30) | (1UL << 17))

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE           (1UL << 10)

/**
 * @brief  AHB1 memory slot index for FLASH interface (offset 15 * 0x0400 = 0x3C00).
 * @see    PLAY32_FLASH_BASE
 */
#define PLAY32_FLASH_BASE_POS       (15U)

/**
 * @brief  FLASH interface peripheral base address (0x40023C00).
 * @note   Computed from @ref PLAY32_AHB1_PERIPHERAL and @ref PLAY32_FLASH_BASE_POS.
 */
#define PLAY32_FLASH_BASE           (PLAY32_AHB1_PERIPHERAL + (PLAY32_FLASH_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  FLASH interface hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 3.9, offsets 0x00-0x14).
 */
typedef struct {
    volatile uint32_t ACR;     /**< Offset: 0x00 - Flash access control register. */
    volatile uint32_t KEYR;    /**< Offset: 0x04 - Flash key register. */
    volatile uint32_t OPTKEYR; /**< Offset: 0x08 - Flash option key register. */
    volatile uint32_t SR;      /**< Offset: 0x0C - Flash status register. */
    volatile uint32_t CR;      /**< Offset: 0x10 - Flash control register. */
    volatile uint32_t OPTCR;   /**< Offset: 0x14 - Flash option control register. */
} PLAY32_FLASH_TypeDef;

/** @brief FLASH interface peripheral register map pointer (AHB1, 0x40023C00). */
#define PLAY32_FLASH ((PLAY32_FLASH_TypeDef *)PLAY32_FLASH_BASE)

/** @} */ /* End of PLAY32_FLASH_Memory_Map */

/**
 * @defgroup PLAY32_FLASH_Common_Types Common FLASH Enumerations and Keys
 * @brief Reusable control switches, status flags, and hardware unlock keys for FLASH registers.
 * @{
 */
#pragma region FLASH_COMMON_ENUM

/** @brief First unlock key for `FLASH_KEYR` (RM0368, Section 3.5.1). */
#define PLAY32_FLASH_KEY1           (0x45670123UL)

/** @brief Second unlock key for `FLASH_KEYR` (RM0368, Section 3.5.1). */
#define PLAY32_FLASH_KEY2           (0xCDEF89ABUL)

/** @brief First option-byte unlock key for `FLASH_OPTKEYR` (RM0368, Section 3.7.2). */
#define PLAY32_FLASH_OPTKEY1        (0x08192A3BUL)

/** @brief Second option-byte unlock key for `FLASH_OPTKEYR` (RM0368, Section 3.7.2). */
#define PLAY32_FLASH_OPTKEY2        (0x4C5D6E7FUL)

/**
 * @brief  Standard active-high control switch states for FLASH features and interrupts.
 */
typedef enum {
    PLAY32_FLASH_SWITCH_DISABLED = 0U, /**< Feature or interrupt disabled (0). */
    PLAY32_FLASH_SWITCH_ENABLED  = 1U  /**< Feature or interrupt enabled (1). */
} PLAY32_FLASH_Switch;

/**
 * @brief  FLASH hardware status flag state enumeration.
 */
typedef enum {
    PLAY32_FLASH_FLAG_NOT_SET = 0U, /**< Status or error flag is cleared (0). */
    PLAY32_FLASH_FLAG_SET     = 1U  /**< Status or error flag is set (1). */
} PLAY32_FLASH_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_FLASH_Common_Types */

/**
 * @defgroup PLAY32_FLASH_ACR_Types FLASH Access Control Register (FLASH_ACR)
 * @brief Bit positions, masks, and wait-state / ART cache types for FLASH_ACR (offset 0x00).
 * @{
 */
#pragma region FLASH_ACR_REGISTER

#pragma region FLASH_ACR_REGISTER_POSITION
#define PLAY32_FLASH_ACR_LATENCY_POS    (0U)  /**< Bits [3:0]: Flash read latency (wait states) position. */
#define PLAY32_FLASH_ACR_PRFTEN_POS     (8U)  /**< Bit 8: Prefetch enable position. */
#define PLAY32_FLASH_ACR_ICEN_POS       (9U)  /**< Bit 9: Instruction cache enable position. */
#define PLAY32_FLASH_ACR_DCEN_POS       (10U) /**< Bit 10: Data cache enable position. */
#define PLAY32_FLASH_ACR_ICRST_POS      (11U) /**< Bit 11: Instruction cache reset position. */
#define PLAY32_FLASH_ACR_DCRST_POS      (12U) /**< Bit 12: Data cache reset position. */
#pragma endregion

#pragma region FLASH_ACR_REGISTER_MASK
#define PLAY32_FLASH_ACR_LATENCY_MSK    (0xFUL << PLAY32_FLASH_ACR_LATENCY_POS) /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_FLASH_ACR_PRFTEN_MSK     (1UL << PLAY32_FLASH_ACR_PRFTEN_POS)    /**< Bit 8 mask (0x00000100). */
#define PLAY32_FLASH_ACR_ICEN_MSK       (1UL << PLAY32_FLASH_ACR_ICEN_POS)      /**< Bit 9 mask (0x00000200). */
#define PLAY32_FLASH_ACR_DCEN_MSK       (1UL << PLAY32_FLASH_ACR_DCEN_POS)      /**< Bit 10 mask (0x00000400). */
#define PLAY32_FLASH_ACR_ICRST_MSK      (1UL << PLAY32_FLASH_ACR_ICRST_POS)     /**< Bit 11 mask (0x00000800). */
#define PLAY32_FLASH_ACR_DCRST_MSK      (1UL << PLAY32_FLASH_ACR_DCRST_POS)     /**< Bit 12 mask (0x00001000). */
#pragma endregion

#pragma region FLASH_ACR_REGISTER_ENUM

/**
 * @brief  Flash memory read access latency (`LATENCY[3:0]`) wait-state enumeration.
 * @note   Read/Write 4-bit field (bits 3:0 of FLASH_ACR, LATENCY[3:0]) specifying the ratio
 *         of CPU clock (`HCLK`) period to Flash memory access time (STM32F401 RM0368, Table 6).
 * @warning Must be increased **before** switching `SYSCLK` to a higher frequency (e.g., `2 WS`
 *          before switching to `84 MHz` PLL at `2.7V–3.6V`), otherwise instruction fetches will fail.
 */
typedef enum {
    PLAY32_FLASH_ACR_LATENCY_0_WS  = 0U,  /**< 0 wait states (HCLK <= 30 MHz at 2.7V–3.6V). */
    PLAY32_FLASH_ACR_LATENCY_1_WS  = 1U,  /**< 1 wait state (30 MHz < HCLK <= 60 MHz at 2.7V–3.6V). */
    PLAY32_FLASH_ACR_LATENCY_2_WS  = 2U,  /**< 2 wait states (60 MHz < HCLK <= 84 MHz at 2.7V–3.6V). */
    PLAY32_FLASH_ACR_LATENCY_3_WS  = 3U,  /**< 3 wait states (used at lower supply voltage ranges). */
    PLAY32_FLASH_ACR_LATENCY_4_WS  = 4U,  /**< 4 wait states (used at lower supply voltage ranges). */
    PLAY32_FLASH_ACR_LATENCY_5_WS  = 5U,  /**< 5 wait states (used at lower supply voltage ranges). */
    PLAY32_FLASH_ACR_LATENCY_6_WS  = 6U,  /**< 6 wait states (used at lower supply voltage ranges). */
    PLAY32_FLASH_ACR_LATENCY_7_WS  = 7U,  /**< 7 wait states (used at lower supply voltage ranges). */
    PLAY32_FLASH_ACR_LATENCY_8_WS  = 8U,  /**< 8 wait states. */
    PLAY32_FLASH_ACR_LATENCY_9_WS  = 9U,  /**< 9 wait states. */
    PLAY32_FLASH_ACR_LATENCY_10_WS = 10U, /**< 10 wait states. */
    PLAY32_FLASH_ACR_LATENCY_11_WS = 11U, /**< 11 wait states. */
    PLAY32_FLASH_ACR_LATENCY_12_WS = 12U, /**< 12 wait states. */
    PLAY32_FLASH_ACR_LATENCY_13_WS = 13U, /**< 13 wait states. */
    PLAY32_FLASH_ACR_LATENCY_14_WS = 14U, /**< 14 wait states. */
    PLAY32_FLASH_ACR_LATENCY_15_WS = 15U  /**< 15 wait states. */
} PLAY32_FLASH_ACR_Latency;

/**
 * @brief  ART Accelerator prefetch buffer enable (`PRFTEN`) state type.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_ACR_PrefetchEnable;

/**
 * @brief  ART Accelerator instruction cache enable (`ICEN`) state type.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_ACR_InstructionCacheEnable;

/**
 * @brief  ART Accelerator data cache enable (`DCEN`) state type.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_ACR_DataCacheEnable;

/**
 * @brief  Instruction cache reset (`ICRST`) control state type.
 * @warning May only be written when the instruction cache is disabled (`ICEN = 0`).
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_ACR_InstructionCacheReset;

/**
 * @brief  Data cache reset (`DCRST`) control state type.
 * @warning May only be written when the data cache is disabled (`DCEN = 0`).
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_ACR_DataCacheReset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_FLASH_ACR_Types */

/**
 * @defgroup PLAY32_FLASH_KEYR_Types FLASH Key Registers (FLASH_KEYR / FLASH_OPTKEYR)
 * @brief Bit positions, masks, and key value types for FLASH_KEYR (0x04) and FLASH_OPTKEYR (0x08).
 * @{
 */
#pragma region FLASH_KEYR_REGISTER

#pragma region FLASH_KEYR_REGISTER_POSITION
#define PLAY32_FLASH_KEYR_KEY_POS       (0U) /**< Bits [31:0]: Flash control unlock key position. */
#define PLAY32_FLASH_OPTKEYR_OPTKEY_POS (0U) /**< Bits [31:0]: Option control unlock key position. */
#pragma endregion

#pragma region FLASH_KEYR_REGISTER_MASK
#define PLAY32_FLASH_KEYR_KEY_MSK       (0xFFFFFFFFUL << PLAY32_FLASH_KEYR_KEY_POS)       /**< Bits [31:0] mask. */
#define PLAY32_FLASH_OPTKEYR_OPTKEY_MSK (0xFFFFFFFFUL << PLAY32_FLASH_OPTKEYR_OPTKEY_POS) /**< Bits [31:0] mask. */
#pragma endregion

#pragma region FLASH_KEYR_REGISTER_VALUE
/** @brief 32-bit key value type written sequentially to `FLASH_KEYR` (`KEY1`, then `KEY2`). */
typedef uint32_t PLAY32_FLASH_KEYR_Key;

/** @brief 32-bit key value type written sequentially to `FLASH_OPTKEYR` (`OPTKEY1`, then `OPTKEY2`). */
typedef uint32_t PLAY32_FLASH_OPTKEYR_OptionKey;
#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_FLASH_KEYR_Types */

/**
 * @defgroup PLAY32_FLASH_SR_Types FLASH Status Register (FLASH_SR)
 * @brief Bit positions, masks, and operation/error flag types for FLASH_SR (offset 0x0C).
 * @{
 */
#pragma region FLASH_SR_REGISTER

#pragma region FLASH_SR_REGISTER_POSITION
#define PLAY32_FLASH_SR_EOP_POS         (0U)  /**< Bit 0: End of operation flag position. */
#define PLAY32_FLASH_SR_OPERR_POS       (1U)  /**< Bit 1: Operation error flag position. */
#define PLAY32_FLASH_SR_WRPERR_POS      (4U)  /**< Bit 4: Write protection error flag position. */
#define PLAY32_FLASH_SR_PGAERR_POS      (5U)  /**< Bit 5: Programming alignment error flag position. */
#define PLAY32_FLASH_SR_PGPERR_POS      (6U)  /**< Bit 6: Programming parallelism error flag position. */
#define PLAY32_FLASH_SR_PGSERR_POS      (7U)  /**< Bit 7: Programming sequence error flag position. */
#define PLAY32_FLASH_SR_RDERR_POS       (8U)  /**< Bit 8: Read protection error (PCROP) flag position. */
#define PLAY32_FLASH_SR_BSY_POS         (16U) /**< Bit 16: Flash memory operation busy flag position. */
#pragma endregion

#pragma region FLASH_SR_REGISTER_MASK
#define PLAY32_FLASH_SR_EOP_MSK         (1UL << PLAY32_FLASH_SR_EOP_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_FLASH_SR_OPERR_MSK       (1UL << PLAY32_FLASH_SR_OPERR_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_FLASH_SR_WRPERR_MSK      (1UL << PLAY32_FLASH_SR_WRPERR_POS) /**< Bit 4 mask (0x00000010). */
#define PLAY32_FLASH_SR_PGAERR_MSK      (1UL << PLAY32_FLASH_SR_PGAERR_POS) /**< Bit 5 mask (0x00000020). */
#define PLAY32_FLASH_SR_PGPERR_MSK      (1UL << PLAY32_FLASH_SR_PGPERR_POS) /**< Bit 6 mask (0x00000040). */
#define PLAY32_FLASH_SR_PGSERR_MSK      (1UL << PLAY32_FLASH_SR_PGSERR_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_FLASH_SR_RDERR_MSK       (1UL << PLAY32_FLASH_SR_RDERR_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_FLASH_SR_BSY_MSK         (1UL << PLAY32_FLASH_SR_BSY_POS)    /**< Bit 16 mask (0x00010000). */
#pragma endregion

#pragma region FLASH_SR_REGISTER_ENUM

/**
 * @brief  End of operation (`EOP`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 0 of FLASH_SR, EOP) set by hardware when
 *         a Flash program or erase operation completes successfully and `EOPIE = 1`.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_end_of_operation.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_EndOfOperation;

/**
 * @brief  Operation error (`OPERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 1 of FLASH_SR, OPERR) set by hardware when
 *         a Flash operation error occurs and `ERRIE = 1`.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_operation_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_OperationError;

/**
 * @brief  Write protection error (`WRPERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 4 of FLASH_SR, WRPERR) set by hardware when
 *         an address to be erased or programmed belongs to a write-protected sector.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_write_protection_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_WriteProtectionError;

/**
 * @brief  Programming alignment error (`PGAERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 5 of FLASH_SR, PGAERR) set by hardware when
 *         the data to program crosses a 128-bit row boundary or is misaligned with `PSIZE`.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_programming_alignment_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_ProgrammingAlignmentError;

/**
 * @brief  Programming parallelism error (`PGPERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 6 of FLASH_SR, PGPERR) set by hardware when
 *         the bus access width does not match the parallelism size configured in `PSIZE[1:0]`.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_programming_parallelism_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_ProgrammingParallelismError;

/**
 * @brief  Programming sequence error (`PGSERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 7 of FLASH_SR, PGSERR) set by hardware when
 *         a write to Flash occurs without `PG = 1` or when control bits are modified mid-operation.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_programming_sequence_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_ProgrammingSequenceError;

/**
 * @brief  Read protection error (`RDERR`) status flag type.
 * @note   Read/Clear-by-1 (`rc_w1`) status bit (bit 8 of FLASH_SR, RDERR) set by hardware when
 *         a read access is attempted on a Proprietary Code Read-Out Protection (PCROP) sector.
 * @warning Cleared by writing `1` directly to `FLASH_SR` via @ref play32_flash_clear_read_protection_error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_ReadProtectionError;

/**
 * @brief  Flash memory operation busy (`BSY`) status flag type.
 * @note   Read-only status bit (bit 16 of FLASH_SR, BSY) set by hardware while a Flash program
 *         or erase operation is in progress and cleared automatically upon completion or error.
 * @see    PLAY32_FLASH_Flag
 */
typedef PLAY32_FLASH_Flag PLAY32_FLASH_SR_Busy;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_FLASH_SR_Types */

/**
 * @defgroup PLAY32_FLASH_CR_Types FLASH Control Register (FLASH_CR)
 * @brief Bit positions, masks, and erase/programming control types for FLASH_CR (offset 0x10).
 * @{
 */
#pragma region FLASH_CR_REGISTER

#pragma region FLASH_CR_REGISTER_POSITION
#define PLAY32_FLASH_CR_PG_POS          (0U)  /**< Bit 0: Flash programming activation position. */
#define PLAY32_FLASH_CR_SER_POS         (1U)  /**< Bit 1: Sector erase activation position. */
#define PLAY32_FLASH_CR_MER_POS         (2U)  /**< Bit 2: Mass erase activation position. */
#define PLAY32_FLASH_CR_SNB_POS         (3U)  /**< Bits [6:3]: Sector number selection position. */
#define PLAY32_FLASH_CR_PSIZE_POS       (8U)  /**< Bits [9:8]: Program parallelism size position. */
#define PLAY32_FLASH_CR_STRT_POS        (16U) /**< Bit 16: Start erase operation trigger position. */
#define PLAY32_FLASH_CR_EOPIE_POS       (24U) /**< Bit 24: End of operation interrupt enable position. */
#define PLAY32_FLASH_CR_ERRIE_POS       (25U) /**< Bit 25: Error interrupt enable position. */
#define PLAY32_FLASH_CR_LOCK_POS        (31U) /**< Bit 31: Flash control register lock position. */
#pragma endregion

#pragma region FLASH_CR_REGISTER_MASK
#define PLAY32_FLASH_CR_PG_MSK          (1UL << PLAY32_FLASH_CR_PG_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_FLASH_CR_SER_MSK         (1UL << PLAY32_FLASH_CR_SER_POS)   /**< Bit 1 mask (0x00000002). */
#define PLAY32_FLASH_CR_MER_MSK         (1UL << PLAY32_FLASH_CR_MER_POS)   /**< Bit 2 mask (0x00000004). */
#define PLAY32_FLASH_CR_SNB_MSK         (0xFUL << PLAY32_FLASH_CR_SNB_POS) /**< Bits [6:3] mask (0x00000078). */
#define PLAY32_FLASH_CR_PSIZE_MSK       (3UL << PLAY32_FLASH_CR_PSIZE_POS) /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_FLASH_CR_STRT_MSK        (1UL << PLAY32_FLASH_CR_STRT_POS)  /**< Bit 16 mask (0x00010000). */
#define PLAY32_FLASH_CR_EOPIE_MSK       (1UL << PLAY32_FLASH_CR_EOPIE_POS) /**< Bit 24 mask (0x01000000). */
#define PLAY32_FLASH_CR_ERRIE_MSK       (1UL << PLAY32_FLASH_CR_ERRIE_POS) /**< Bit 25 mask (0x02000000). */
#define PLAY32_FLASH_CR_LOCK_MSK        (1UL << PLAY32_FLASH_CR_LOCK_POS)  /**< Bit 31 mask (0x80000000). */
#pragma endregion

#pragma region FLASH_CR_REGISTER_ENUM

/**
 * @brief  Flash programming (`PG`) activation state type.
 * @note   Read/Write control bit (bit 0 of FLASH_CR, PG) enabling standard Flash memory programming.
 * @warning `FLASH_CR` must be unlocked via `FLASH_KEYR` (`KEY1`, then `KEY2`) before writing.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_Programming;

/**
 * @brief  Sector erase (`SER`) activation state type.
 * @note   Read/Write control bit (bit 1 of FLASH_CR, SER) selecting single-sector erase mode
 *         for the sector specified in `SNB[3:0]`.
 * @see    PLAY32_FLASH_Switch
 * @see    PLAY32_FLASH_CR_SectorNumber
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_SectorErase;

/**
 * @brief  Mass erase (`MER`) activation state type.
 * @note   Read/Write control bit (bit 2 of FLASH_CR, MER) triggering a full erase of all user sectors
 *         when `STRT` is asserted.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_MassErase;

/**
 * @brief  Flash sector number (`SNB[3:0]`) enumeration for STM32F401 (Sectors 0 to 7).
 * @note   Read/Write 4-bit field (bits 6:3 of FLASH_CR, SNB[3:0]) selecting the target sector
 *         when `SER = 1` (STM32F401 RM0368, Table 4).
 * @warning Verify device Flash density (128 KB, 256 KB, 384 KB, or 512 KB) before erasing high sectors.
 */
typedef enum {
    PLAY32_FLASH_CR_SECTOR_0 = 0U, /**< Sector 0 (16 KB: 0x08000000 - 0x08003FFF). */
    PLAY32_FLASH_CR_SECTOR_1 = 1U, /**< Sector 1 (16 KB: 0x08004000 - 0x08007FFF). */
    PLAY32_FLASH_CR_SECTOR_2 = 2U, /**< Sector 2 (16 KB: 0x08008000 - 0x0800BFFF). */
    PLAY32_FLASH_CR_SECTOR_3 = 3U, /**< Sector 3 (16 KB: 0x0800C000 - 0x0800FFFF). */
    PLAY32_FLASH_CR_SECTOR_4 = 4U, /**< Sector 4 (64 KB: 0x08010000 - 0x0801FFFF). */
    PLAY32_FLASH_CR_SECTOR_5 = 5U, /**< Sector 5 (128 KB: 0x08020000 - 0x0803FFFF, 256/384/512 KB variants). */
    PLAY32_FLASH_CR_SECTOR_6 = 6U, /**< Sector 6 (128 KB: 0x08040000 - 0x0805FFFF, 384/512 KB variants). */
    PLAY32_FLASH_CR_SECTOR_7 = 7U  /**< Sector 7 (128 KB: 0x08060000 - 0x0807FFFF, 512 KB variant). */
} PLAY32_FLASH_CR_SectorNumber;

/**
 * @brief  Program parallelism size (`PSIZE[1:0]`) enumeration based on `VDD` supply voltage.
 * @note   Read/Write 2-bit field (bits 9:8 of FLASH_CR, PSIZE[1:0]) configuring the number of bytes
 *         programmed/erased in parallel per operation (STM32F401 RM0368, Section 3.5.2).
 * @warning Selecting a parallelism width higher than permitted for the current `VDD` voltage
 *          will corrupt Flash contents or trigger `PGPERR`. Use `X32` at `3.3 V`.
 */
typedef enum {
    PLAY32_FLASH_CR_PROGRAM_SIZE_X8  = 0U, /**< Program x8 (byte write, 1.7V–2.1V). */
    PLAY32_FLASH_CR_PROGRAM_SIZE_X16 = 1U, /**< Program x16 (half-word write, 2.1V–2.7V). */
    PLAY32_FLASH_CR_PROGRAM_SIZE_X32 = 2U, /**< Program x32 (word write, 2.7V–3.6V). */
    PLAY32_FLASH_CR_PROGRAM_SIZE_X64 = 3U  /**< Program x64 (double-word write, 2.7V–3.6V with external Vpp). */
} PLAY32_FLASH_CR_ProgramSize;

/**
 * @brief  Start erase operation (`STRT`) trigger type.
 * @note   Read/Write control bit (bit 16 of FLASH_CR, STRT) set by software to launch a sector
 *         or mass erase; automatically cleared by hardware when `BSY` goes low.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_Start;

/**
 * @brief  End of operation interrupt enable (`EOPIE`) state type.
 * @note   Read/Write control bit (bit 24 of FLASH_CR, EOPIE) enabling interrupt generation
 *         when `EOP = 1` in `FLASH_SR`.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_EndOfOperationInterruptEnable;

/**
 * @brief  Error interrupt enable (`ERRIE`) state type.
 * @note   Read/Write control bit (bit 25 of FLASH_CR, ERRIE) enabling interrupt generation
 *         when any error flag (`OPERR`, `WRPERR`, `PGAERR`, `PGPERR`, `PGSERR`, `RDERR`) is set.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_ErrorInterruptEnable;

/**
 * @brief  Flash control register lock (`LOCK`) state type.
 * @note   Write-1-only lock bit (bit 31 of FLASH_CR, LOCK). Defaults to `1` after reset; cleared
 *         exclusively by writing `KEY1` then `KEY2` to `FLASH_KEYR`, and re-locked by writing `1`.
 * @see    PLAY32_FLASH_Switch
 */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_CR_Lock;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_FLASH_CR_Types */

/**
 * @defgroup PLAY32_FLASH_OPTCR_Types FLASH Option Control Register (FLASH_OPTCR)
 * @brief Bit positions, masks, and option-byte configuration types for FLASH_OPTCR (offset 0x14).
 * @{
 */
#pragma region FLASH_OPTCR_REGISTER

#pragma region FLASH_OPTCR_REGISTER_POSITION
#define PLAY32_FLASH_OPTCR_OPTLOCK_POS    (0U)  /**< Bit 0: Option lock position. */
#define PLAY32_FLASH_OPTCR_OPTSTRT_POS    (1U)  /**< Bit 1: Option start position. */
#define PLAY32_FLASH_OPTCR_BOR_LEV_POS    (2U)  /**< Bits [3:2]: Brown-out reset level position. */
#define PLAY32_FLASH_OPTCR_WDG_SW_POS     (5U)  /**< Bit 5: User option byte independent watchdog mode position. */
#define PLAY32_FLASH_OPTCR_NRST_STOP_POS  (6U)  /**< Bit 6: User option byte reset on Stop mode position. */
#define PLAY32_FLASH_OPTCR_NRST_STDBY_POS (7U)  /**< Bit 7: User option byte reset on Standby mode position. */
#define PLAY32_FLASH_OPTCR_RDP_POS        (8U)  /**< Bits [15:8]: Read protection level byte position. */
#define PLAY32_FLASH_OPTCR_NWRP_POS       (16U) /**< Bits [23:16]: Not write-protect sector bitmask position. */
#define PLAY32_FLASH_OPTCR_SPRMOD_POS     (31U) /**< Bit 31: Selection of protection mode for nWRP position. */
#pragma endregion

#pragma region FLASH_OPTCR_REGISTER_MASK
#define PLAY32_FLASH_OPTCR_OPTLOCK_MSK    (1UL << PLAY32_FLASH_OPTCR_OPTLOCK_POS)    /**< Bit 0 mask (0x00000001). */
#define PLAY32_FLASH_OPTCR_OPTSTRT_MSK    (1UL << PLAY32_FLASH_OPTCR_OPTSTRT_POS)    /**< Bit 1 mask (0x00000002). */
#define PLAY32_FLASH_OPTCR_BOR_LEV_MSK    (3UL << PLAY32_FLASH_OPTCR_BOR_LEV_POS)    /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_FLASH_OPTCR_WDG_SW_MSK     (1UL << PLAY32_FLASH_OPTCR_WDG_SW_POS)     /**< Bit 5 mask (0x00000020). */
#define PLAY32_FLASH_OPTCR_NRST_STOP_MSK  (1UL << PLAY32_FLASH_OPTCR_NRST_STOP_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_FLASH_OPTCR_NRST_STDBY_MSK (1UL << PLAY32_FLASH_OPTCR_NRST_STDBY_POS) /**< Bit 7 mask (0x00000080). */
#define PLAY32_FLASH_OPTCR_RDP_MSK        (0xFFUL << PLAY32_FLASH_OPTCR_RDP_POS)     /**< Bits [15:8] mask (0x0000FF00). */
#define PLAY32_FLASH_OPTCR_NWRP_MSK       (0xFFUL << PLAY32_FLASH_OPTCR_NWRP_POS)    /**< Bits [23:16] mask (0x00FF0000). */
#define PLAY32_FLASH_OPTCR_SPRMOD_MSK     (1UL << PLAY32_FLASH_OPTCR_SPRMOD_POS)     /**< Bit 31 mask (0x80000000). */
#pragma endregion

#pragma region FLASH_OPTCR_REGISTER_ENUM

/** @brief Option control register lock (`OPTLOCK`) state type. */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_OPTCR_OptionLock;

/** @brief Option byte programming start (`OPTSTRT`) trigger type. */
typedef PLAY32_FLASH_Switch PLAY32_FLASH_OPTCR_OptionStart;

/**
 * @brief  Brown-out reset threshold level (`BOR_LEV[1:0]`) enumeration.
 */
typedef enum {
    PLAY32_FLASH_OPTCR_BOR_LEVEL_3   = 0U, /**< BOR Level 3: supply voltage threshold 2.70 V to 3.60 V. */
    PLAY32_FLASH_OPTCR_BOR_LEVEL_2   = 1U, /**< BOR Level 2: supply voltage threshold 2.40 V to 2.70 V. */
    PLAY32_FLASH_OPTCR_BOR_LEVEL_1   = 2U, /**< BOR Level 1: supply voltage threshold 2.10 V to 2.40 V. */
    PLAY32_FLASH_OPTCR_BOR_LEVEL_OFF = 3U  /**< BOR Off: supply voltage threshold 1.80 V to 2.10 V (POR/PDR). */
} PLAY32_FLASH_OPTCR_BORLevel;

/**
 * @brief  Independent watchdog hardware/software selection (`WDG_SW`) enumeration.
 */
typedef enum {
    PLAY32_FLASH_OPTCR_WATCHDOG_HARDWARE = 0U, /**< Hardware independent watchdog enabled automatically at reset. */
    PLAY32_FLASH_OPTCR_WATCHDOG_SOFTWARE = 1U  /**< Software independent watchdog started by writing 0xCCCC to IWDG_KR. */
} PLAY32_FLASH_OPTCR_WatchdogSelection;

/**
 * @brief  Reset generation on Stop mode entry (`nRST_STOP`) enumeration.
 */
typedef enum {
    PLAY32_FLASH_OPTCR_RESET_STOP_GENERATED     = 0U, /**< Reset generated when entering Stop mode. */
    PLAY32_FLASH_OPTCR_RESET_STOP_NOT_GENERATED = 1U  /**< No reset generated when entering Stop mode. */
} PLAY32_FLASH_OPTCR_ResetStop;

/**
 * @brief  Reset generation on Standby mode entry (`nRST_STDBY`) enumeration.
 */
typedef enum {
    PLAY32_FLASH_OPTCR_RESET_STANDBY_GENERATED     = 0U, /**< Reset generated when entering Standby mode. */
    PLAY32_FLASH_OPTCR_RESET_STANDBY_NOT_GENERATED = 1U  /**< No reset generated when entering Standby mode. */
} PLAY32_FLASH_OPTCR_ResetStandby;

/**
 * @brief  Read protection (`RDP[7:0]`) level enumeration.
 * @warning Setting `PLAY32_FLASH_OPTCR_READ_PROTECTION_LEVEL_2` (`0xCC`) permanently disables
 *          JTAG/SWD debug and cannot be undone!
 */
typedef enum {
    PLAY32_FLASH_OPTCR_READ_PROTECTION_LEVEL_0 = 0xAAU, /**< Level 0: Read protection not active. */
    PLAY32_FLASH_OPTCR_READ_PROTECTION_LEVEL_1 = 0x55U, /**< Level 1: Read protection active (reversible via mass erase). */
    PLAY32_FLASH_OPTCR_READ_PROTECTION_LEVEL_2 = 0xCCU  /**< Level 2: Permanent chip readout & debug lock (irreversible). */
} PLAY32_FLASH_OPTCR_ReadProtection;

/** @brief 8-bit sector write/PCROP protection bitmask (`nWRP[7:0]`, 1 bit per sector 0..7). */
typedef uint8_t PLAY32_FLASH_OPTCR_SectorWriteProtection;

/**
 * @brief  Protection mode selection for `nWRP` (`SPRMOD`) enumeration.
 */
typedef enum {
    PLAY32_FLASH_OPTCR_PROTECTION_MODE_WRITE_PROTECTION = 0U, /**< nWRP bits control sector write protection (0 = protected). */
    PLAY32_FLASH_OPTCR_PROTECTION_MODE_PCROP            = 1U  /**< nWRP bits control Proprietary Code Read-Out Protection (1 = protected). */
} PLAY32_FLASH_OPTCR_ProtectionMode;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_FLASH_OPTCR_Types */

/** @} */ /* End of PLAY32_FLASH */

#endif /* PLAY32_FLASH_TYPES_H */
