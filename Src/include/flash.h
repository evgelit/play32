/**
 * @file    flash.h
 * @author  Eugene Litvin
 * @brief   Hardware register mapping and X-Macro code generator API
 *          for Embedded Flash Memory Interface (FLASH) of STM32F401 CCU.
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

#ifndef PLAY32_FLASH_H
#define PLAY32_FLASH_H

#include "flash_types.h"

/**
 * @addtogroup PLAY32_FLASH
 * @{
 */

/**
 * @defgroup PLAY32_FLASH_Driver FLASH Register Accessor Generator API
 * @brief X-Macro descriptor table and compile-time inline register accessor functions.
 * @{
 */

/**
 * @brief  Master X-Macro descriptor table for the singleton FLASH interface (`PLAY32_FLASH`).
 * @details Maps each Flash control, key, status, or option-byte field to its hardware register,
 *          bitfield mnemonic, strict typedef from @ref flash_types.h, and hardware access mode
 *          using the signature: `X(func_suffix, reg_name, bit_name, type_suffix, access_mode)`.
 *
 * @param  X  Generator macro invoked once per register field entry.
 *
 * @warning Ensure Doxygen is configured with `MACRO_EXPANSION = YES` if you want
 *          expanded inline functions to appear in the generated API documentation.
 * @see    PLAY32_FLASH_TypeDef
 */
#define FLASH_REGISTERS_TABLE(X) \
/************************************** FLASH ACR REGISTER *********************************************************/\
X(latency,                              ACR,          LATENCY,       Latency,                           SET_RMW     )\
X(prefetch_enable,                      ACR,          PRFTEN,        PrefetchEnable,                    SET_RMW     )\
X(instruction_cache_enable,             ACR,          ICEN,          InstructionCacheEnable,            SET_RMW     )\
X(data_cache_enable,                    ACR,          DCEN,          DataCacheEnable,                   SET_RMW     )\
X(instruction_cache_reset,              ACR,          ICRST,         InstructionCacheReset,             SET_RMW     )\
X(data_cache_reset,                     ACR,          DCRST,         DataCacheReset,                    SET_RMW     )\
\
/************************************** FLASH KEYR / OPTKEYR REGISTERS *********************************************/\
X(key,                                  KEYR,         KEY,           Key,                               SET_WO      )\
X(option_key,                           OPTKEYR,      OPTKEY,        OptionKey,                         SET_WO      )\
\
/************************************** FLASH SR REGISTER **********************************************************/\
X(end_of_operation,                     SR,           EOP,           EndOfOperation,                    CLEAR_RC_W1 )\
X(operation_error,                      SR,           OPERR,         OperationError,                    CLEAR_RC_W1 )\
X(write_protection_error,               SR,           WRPERR,        WriteProtectionError,              CLEAR_RC_W1 )\
X(programming_alignment_error,          SR,           PGAERR,        ProgrammingAlignmentError,         CLEAR_RC_W1 )\
X(programming_parallelism_error,        SR,           PGPERR,        ProgrammingParallelismError,       CLEAR_RC_W1 )\
X(programming_sequence_error,           SR,           PGSERR,        ProgrammingSequenceError,          CLEAR_RC_W1 )\
X(read_protection_error,                SR,           RDERR,         ReadProtectionError,               CLEAR_RC_W1 )\
X(busy,                                 SR,           BSY,           Busy,                              RO          )\
\
/************************************** FLASH CR REGISTER **********************************************************/\
X(programming,                          CR,           PG,            Programming,                       SET_RMW     )\
X(sector_erase,                         CR,           SER,           SectorErase,                       SET_RMW     )\
X(mass_erase,                           CR,           MER,           MassErase,                         SET_RMW     )\
X(sector_number,                        CR,           SNB,           SectorNumber,                      SET_RMW     )\
X(program_size,                         CR,           PSIZE,         ProgramSize,                       SET_RMW     )\
X(start,                                CR,           STRT,          Start,                             SET_RMW     )\
X(end_of_operation_interrupt_enable,    CR,           EOPIE,         EndOfOperationInterruptEnable,     SET_RMW     )\
X(error_interrupt_enable,               CR,           ERRIE,         ErrorInterruptEnable,              SET_RMW     )\
X(lock,                                 CR,           LOCK,          Lock,                              SET_RMW     )\
\
/************************************** FLASH OPTCR REGISTER *******************************************************/\
X(option_lock,                          OPTCR,        OPTLOCK,       OptionLock,                        SET_RMW     )\
X(option_start,                         OPTCR,        OPTSTRT,       OptionStart,                       SET_RMW     )\
X(bor_level,                            OPTCR,        BOR_LEV,       BORLevel,                          SET_RMW     )\
X(watchdog_selection,                   OPTCR,        WDG_SW,        WatchdogSelection,                 SET_RMW     )\
X(reset_stop,                           OPTCR,        NRST_STOP,     ResetStop,                         SET_RMW     )\
X(reset_standby,                        OPTCR,        NRST_STDBY,    ResetStandby,                      SET_RMW     )\
X(read_protection,                      OPTCR,        RDP,           ReadProtection,                    SET_RMW     )\
X(sector_write_protection,              OPTCR,        NWRP,          SectorWriteProtection,             SET_RMW     )\
X(protection_mode,                      OPTCR,        SPRMOD,        ProtectionMode,                    SET_RMW     )

/*----------------------------------------------------------------------------
 * Writer & Flag-Clearer Generators (Dispatched by 5th column)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a read-modify-write `static inline` setter for multi-field FLASH registers.
 * @param  short_name  Snake-case function suffix (e.g., `latency`).
 * @param  _reg        Target register member in @ref PLAY32_FLASH_TypeDef (e.g., `ACR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `LATENCY`).
 * @param  _type       Type suffix matching `PLAY32_FLASH_<_reg>_<_type>` (e.g., `Latency`).
 */
#define GEN_SET_RMW(short_name, _reg, _sub_reg, _type)                                          \
    /**                                                                                         \
     * @brief  Sets the @c _sub_reg field (@c short_name) in @c FLASH_##_reg.                   \
     * @param[in] value  Typed value to write (@see PLAY32_FLASH_##_reg##_##_type).             \
     */                                                                                         \
    static inline void play32_flash_set_##short_name(                                           \
        const PLAY32_FLASH_##_reg##_##_type value                                               \
    ) {                                                                                         \
        PLAY32_FLASH->_reg = (PLAY32_FLASH->_reg & ~(PLAY32_FLASH_##_reg##_##_sub_reg##_MSK))   \
            | (((uint32_t)value << (PLAY32_FLASH_##_reg##_##_sub_reg##_POS))                    \
            & (PLAY32_FLASH_##_reg##_##_sub_reg##_MSK));                                        \
    }

/**
 * @brief  Generates a direct 32-bit `static inline` setter for write-only key registers (`KEYR`, `OPTKEYR`).
 * @param  short_name  Snake-case function suffix (`key` or `option_key`).
 * @param  _reg        Target register member in @ref PLAY32_FLASH_TypeDef (`KEYR` or `OPTKEYR`).
 * @param  _sub_reg    Bitfield mnemonic (`KEY` or `OPTKEY`).
 * @param  _type       Type suffix (`Key` or `OptionKey`).
 */
#define GEN_SET_WO(short_name, _reg, _sub_reg, _type)                                           \
    /**                                                                                         \
     * @brief  Writes @c short_name directly to write-only @c FLASH_##_reg.                     \
     * @param[in] value  32-bit unlock key (@see PLAY32_FLASH_KEY1, @see PLAY32_FLASH_KEY2).    \
     */                                                                                         \
    static inline void play32_flash_set_##short_name(                                           \
        const PLAY32_FLASH_##_reg##_##_type value                                               \
    ) {                                                                                         \
        PLAY32_FLASH->_reg = (uint32_t)value;                                                   \
    }

/**
 * @brief  Generates an atomic `rc_w1` flag clearer (`PLAY32_FLASH->SR = MSK`) for `FLASH_SR` status bits.
 * @param  short_name  Snake-case function suffix (e.g., `end_of_operation`).
 * @param  _reg        Target register member in @ref PLAY32_FLASH_TypeDef (`SR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_MSK` macro (e.g., `EOP`).
 * @param  _type       Type suffix matching `PLAY32_FLASH_<_reg>_<_type>`.
 */
#define GEN_CLEAR_RC_W1(short_name, _reg, _sub_reg, _type)                                      \
    /**                                                                                         \
     * @brief  Atomically clears the @c _sub_reg flag (@c short_name) in @c FLASH_##_reg.       \
     */                                                                                         \
    static inline void play32_flash_clear_##short_name(void) {                                  \
        PLAY32_FLASH->_reg = PLAY32_FLASH_##_reg##_##_sub_reg##_MSK;                            \
    }

/** @brief Read-only field guard: emits no writer function. */
#define GEN_RO(short_name, _reg, _sub_reg, _type) /* Read-only: no writer emitted */

/** @brief Dispatches writer/clearer generation based on the table's access-mode column. */
#define DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)                           \
    GEN_##mode(short_name, _reg, _sub_reg, _type)

#define DISPATCH_WRITER(short_name, _reg, _sub_reg, _type, mode)                                \
    DISPATCH_WRITER_IMPL(short_name, _reg, _sub_reg, _type, mode)

/*----------------------------------------------------------------------------
 * Reader Generators (Skips write-only KEYR / OPTKEYR registers)
 *----------------------------------------------------------------------------*/

/**
 * @brief  Generates a `static inline` getter for any readable FLASH register field.
 * @param  short_name  Snake-case function suffix (e.g., `busy`).
 * @param  _reg        Target register member in @ref PLAY32_FLASH_TypeDef (e.g., `SR`).
 * @param  _sub_reg    Bitfield mnemonic used for `_POS` and `_MSK` macros (e.g., `BSY`).
 * @param  _type       Type suffix matching `PLAY32_FLASH_<_reg>_<_type>`.
 */
#define GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)                                       \
    /**                                                                                         \
     * @brief  Gets the current @c _sub_reg field (@c short_name) from @c FLASH_##_reg.         \
     * @return Current field value cast to @ref PLAY32_FLASH_##_reg##_##_type.                  \
     */                                                                                         \
    static inline PLAY32_FLASH_##_reg##_##_type play32_flash_get_##short_name(void) {           \
        return (PLAY32_FLASH_##_reg##_##_type)                                                  \
            ((PLAY32_FLASH->_reg & (PLAY32_FLASH_##_reg##_##_sub_reg##_MSK))                    \
            >> (PLAY32_FLASH_##_reg##_##_sub_reg##_POS));                                       \
    }

#define GET_SET_RMW(short_name, _reg, _sub_reg, _type)     GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_CLEAR_RC_W1(short_name, _reg, _sub_reg, _type) GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_RO(short_name, _reg, _sub_reg, _type)          GEN_GET_COMMON(short_name, _reg, _sub_reg, _type)
#define GET_SET_WO(short_name, _reg, _sub_reg, _type)      /* Write-only key register: no getter emitted */

/** @brief Dispatches reader generation based on the table's access-mode column. */
#define DISPATCH_READER_IMPL(short_name, _reg, _sub_reg, _type, mode)                           \
    GET_##mode(short_name, _reg, _sub_reg, _type)

#define DISPATCH_READER(short_name, _reg, _sub_reg, _type, mode)                                \
    DISPATCH_READER_IMPL(short_name, _reg, _sub_reg, _type, mode)

/* Instantiate all FLASH setter, clearer, and getter inline functions */
FLASH_REGISTERS_TABLE(DISPATCH_WRITER)
FLASH_REGISTERS_TABLE(DISPATCH_READER)

#undef GEN_SET_RMW
#undef GEN_SET_WO
#undef GEN_CLEAR_RC_W1
#undef GEN_RO
#undef DISPATCH_WRITER_IMPL
#undef DISPATCH_WRITER
#undef GEN_GET_COMMON
#undef GET_SET_RMW
#undef GET_CLEAR_RC_W1
#undef GET_RO
#undef GET_SET_WO
#undef DISPATCH_READER_IMPL
#undef DISPATCH_READER

/** @} */ /* End of PLAY32_FLASH_Driver */
/** @} */ /* End of PLAY32_FLASH */

#endif /* PLAY32_FLASH_H */
