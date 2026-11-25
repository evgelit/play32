/**
 * @file    exti_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for External Interrupt/Event Controller (EXTI) of STM32F401 CCU.
 * @version 1.0.0
 * @date    2026-11-25
 *
 * @note    This file provides a strict compile-time type-safe interface
 *          for hardware registers manipulation without runtime overhead.
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_EXTI_TYPES_H
#define PLAY32_EXTI_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_EXTI External Interrupt/Event Controller (EXTI)
 * @brief Hardware register map, base address, bit masks, and type-safe enumerations for EXTI.
 * @{
 */

/**
 * @defgroup PLAY32_EXTI_Memory_Map Peripheral Base Address and Register Map
 * @brief APB2 base address calculation and memory-mapped register structure for EXTI.
 * @{
 */

/**
 * @brief  Base address of the APB2 peripheral bus (0x40010000).
 * @note   EXTI is mapped onto the APB2 peripheral bus in STM32F401.
 */
#define PLAY32_APB2_PERIPHERAL    ((1UL << 30) | (1UL << 16))

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE         (1UL << 10)

/**
 * @brief  APB2 memory slot index for EXTI (offset 15 * 0x0400 = 0x3C00).
 * @see    PLAY32_EXTI_BASE
 */
#define PLAY32_EXTI_BASE_POS      (15U)

/**
 * @brief  EXTI peripheral base address (0x40013C00).
 * @note   Computed from @ref PLAY32_APB2_PERIPHERAL and @ref PLAY32_EXTI_BASE_POS.
 */
#define PLAY32_EXTI_BASE          (PLAY32_APB2_PERIPHERAL + (PLAY32_EXTI_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  External Interrupt/Event Controller (EXTI) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 10.3.7, offsets 0x00-0x14).
 */
typedef struct {
    volatile uint32_t IMR;   /**< Offset: 0x00 - Interrupt mask register. */
    volatile uint32_t EMR;   /**< Offset: 0x04 - Event mask register. */
    volatile uint32_t RTSR;  /**< Offset: 0x08 - Rising trigger selection register. */
    volatile uint32_t FTSR;  /**< Offset: 0x0C - Falling trigger selection register. */
    volatile uint32_t SWIER; /**< Offset: 0x10 - Software interrupt event register. */
    volatile uint32_t PR;    /**< Offset: 0x14 - Pending register (rc_w1). */
} PLAY32_EXTI_TypeDef;

/** @brief EXTI peripheral register map pointer (APB2, 0x40013C00). */
#define PLAY32_EXTI ((PLAY32_EXTI_TypeDef *)PLAY32_EXTI_BASE)

/** @} */ /* End of PLAY32_EXTI_Memory_Map */


/**
 * @defgroup PLAY32_EXTI_Common_Types Common EXTI Enumerations
 * @brief Reusable active-high control switch and pending status flag enumerations across EXTI registers.
 * @{
 */
#pragma region EXTI_COMMON_ENUM

/**
 * @brief  Standard active-high control switch states for EXTI mask, trigger, and software event bits.
 */
typedef enum {
    PLAY32_EXTI_SWITCH_DISABLED = 0U, /**< Interrupt/event mask or trigger disabled (0). */
    PLAY32_EXTI_SWITCH_ENABLED  = 1U  /**< Interrupt/event mask or trigger enabled (1). */
} PLAY32_EXTI_Switch;

/**
 * @brief  EXTI hardware pending status flag state enumeration.
 */
typedef enum {
    PLAY32_EXTI_FLAG_NOT_SET = 0U, /**< No trigger request occurred on the line (0). */
    PLAY32_EXTI_FLAG_SET     = 1U  /**< Selected trigger request occurred on the line (1, cleared by writing 1). */
} PLAY32_EXTI_Flag;

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_Common_Types */

/**
 * @defgroup PLAY32_EXTI_IMR_Types EXTI Interrupt Mask Register (EXTI_IMR)
 * @brief Bit positions, masks, and interrupt mask types for EXTI_IMR (offset 0x00).
 * @{
 */
#pragma region EXTI_IMR_REGISTER

#pragma region EXTI_IMR_REGISTER_POSITION
#define PLAY32_EXTI_IMR_MR0_POS     (0U)  /**< Bit 0: Interrupt mask on line 0 position. */
#define PLAY32_EXTI_IMR_MR1_POS     (1U)  /**< Bit 1: Interrupt mask on line 1 position. */
#define PLAY32_EXTI_IMR_MR2_POS     (2U)  /**< Bit 2: Interrupt mask on line 2 position. */
#define PLAY32_EXTI_IMR_MR3_POS     (3U)  /**< Bit 3: Interrupt mask on line 3 position. */
#define PLAY32_EXTI_IMR_MR4_POS     (4U)  /**< Bit 4: Interrupt mask on line 4 position. */
#define PLAY32_EXTI_IMR_MR5_POS     (5U)  /**< Bit 5: Interrupt mask on line 5 position. */
#define PLAY32_EXTI_IMR_MR6_POS     (6U)  /**< Bit 6: Interrupt mask on line 6 position. */
#define PLAY32_EXTI_IMR_MR7_POS     (7U)  /**< Bit 7: Interrupt mask on line 7 position. */
#define PLAY32_EXTI_IMR_MR8_POS     (8U)  /**< Bit 8: Interrupt mask on line 8 position. */
#define PLAY32_EXTI_IMR_MR9_POS     (9U)  /**< Bit 9: Interrupt mask on line 9 position. */
#define PLAY32_EXTI_IMR_MR10_POS    (10U) /**< Bit 10: Interrupt mask on line 10 position. */
#define PLAY32_EXTI_IMR_MR11_POS    (11U) /**< Bit 11: Interrupt mask on line 11 position. */
#define PLAY32_EXTI_IMR_MR12_POS    (12U) /**< Bit 12: Interrupt mask on line 12 position. */
#define PLAY32_EXTI_IMR_MR13_POS    (13U) /**< Bit 13: Interrupt mask on line 13 position. */
#define PLAY32_EXTI_IMR_MR14_POS    (14U) /**< Bit 14: Interrupt mask on line 14 position. */
#define PLAY32_EXTI_IMR_MR15_POS    (15U) /**< Bit 15: Interrupt mask on line 15 position. */
#define PLAY32_EXTI_IMR_MR16_POS    (16U) /**< Bit 16: Interrupt mask on line 16 (PVD output) position. */
#define PLAY32_EXTI_IMR_MR17_POS    (17U) /**< Bit 17: Interrupt mask on line 17 (RTC Alarm event) position. */
#define PLAY32_EXTI_IMR_MR18_POS    (18U) /**< Bit 18: Interrupt mask on line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_IMR_MR21_POS    (21U) /**< Bit 21: Interrupt mask on line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_IMR_MR22_POS    (22U) /**< Bit 22: Interrupt mask on line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_IMR_REGISTER_MASK
#define PLAY32_EXTI_IMR_MR0_MSK     (1UL << PLAY32_EXTI_IMR_MR0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_IMR_MR1_MSK     (1UL << PLAY32_EXTI_IMR_MR1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_IMR_MR2_MSK     (1UL << PLAY32_EXTI_IMR_MR2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_IMR_MR3_MSK     (1UL << PLAY32_EXTI_IMR_MR3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_IMR_MR4_MSK     (1UL << PLAY32_EXTI_IMR_MR4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_IMR_MR5_MSK     (1UL << PLAY32_EXTI_IMR_MR5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_IMR_MR6_MSK     (1UL << PLAY32_EXTI_IMR_MR6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_IMR_MR7_MSK     (1UL << PLAY32_EXTI_IMR_MR7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_IMR_MR8_MSK     (1UL << PLAY32_EXTI_IMR_MR8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_IMR_MR9_MSK     (1UL << PLAY32_EXTI_IMR_MR9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_IMR_MR10_MSK    (1UL << PLAY32_EXTI_IMR_MR10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_IMR_MR11_MSK    (1UL << PLAY32_EXTI_IMR_MR11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_IMR_MR12_MSK    (1UL << PLAY32_EXTI_IMR_MR12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_IMR_MR13_MSK    (1UL << PLAY32_EXTI_IMR_MR13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_IMR_MR14_MSK    (1UL << PLAY32_EXTI_IMR_MR14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_IMR_MR15_MSK    (1UL << PLAY32_EXTI_IMR_MR15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_IMR_MR16_MSK    (1UL << PLAY32_EXTI_IMR_MR16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_IMR_MR17_MSK    (1UL << PLAY32_EXTI_IMR_MR17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_IMR_MR18_MSK    (1UL << PLAY32_EXTI_IMR_MR18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_IMR_MR21_MSK    (1UL << PLAY32_EXTI_IMR_MR21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_IMR_MR22_MSK    (1UL << PLAY32_EXTI_IMR_MR22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_IMR_REGISTER_ENUM
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask0;  /**< Interrupt mask type for EXTI line 0. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask1;  /**< Interrupt mask type for EXTI line 1. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask2;  /**< Interrupt mask type for EXTI line 2. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask3;  /**< Interrupt mask type for EXTI line 3. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask4;  /**< Interrupt mask type for EXTI line 4. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask5;  /**< Interrupt mask type for EXTI line 5. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask6;  /**< Interrupt mask type for EXTI line 6. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask7;  /**< Interrupt mask type for EXTI line 7. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask8;  /**< Interrupt mask type for EXTI line 8. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask9;  /**< Interrupt mask type for EXTI line 9. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask10; /**< Interrupt mask type for EXTI line 10. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask11; /**< Interrupt mask type for EXTI line 11. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask12; /**< Interrupt mask type for EXTI line 12. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask13; /**< Interrupt mask type for EXTI line 13. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask14; /**< Interrupt mask type for EXTI line 14. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask15; /**< Interrupt mask type for EXTI line 15. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask16; /**< Interrupt mask type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask17; /**< Interrupt mask type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask18; /**< Interrupt mask type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask21; /**< Interrupt mask type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_IMR_InterruptMask22; /**< Interrupt mask type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_IMR_Types */

/**
 * @defgroup PLAY32_EXTI_EMR_Types EXTI Event Mask Register (EXTI_EMR)
 * @brief Bit positions, masks, and event mask types for EXTI_EMR (offset 0x04).
 * @{
 */
#pragma region EXTI_EMR_REGISTER

#pragma region EXTI_EMR_REGISTER_POSITION
#define PLAY32_EXTI_EMR_MR0_POS     (0U)  /**< Bit 0: Event mask on line 0 position. */
#define PLAY32_EXTI_EMR_MR1_POS     (1U)  /**< Bit 1: Event mask on line 1 position. */
#define PLAY32_EXTI_EMR_MR2_POS     (2U)  /**< Bit 2: Event mask on line 2 position. */
#define PLAY32_EXTI_EMR_MR3_POS     (3U)  /**< Bit 3: Event mask on line 3 position. */
#define PLAY32_EXTI_EMR_MR4_POS     (4U)  /**< Bit 4: Event mask on line 4 position. */
#define PLAY32_EXTI_EMR_MR5_POS     (5U)  /**< Bit 5: Event mask on line 5 position. */
#define PLAY32_EXTI_EMR_MR6_POS     (6U)  /**< Bit 6: Event mask on line 6 position. */
#define PLAY32_EXTI_EMR_MR7_POS     (7U)  /**< Bit 7: Event mask on line 7 position. */
#define PLAY32_EXTI_EMR_MR8_POS     (8U)  /**< Bit 8: Event mask on line 8 position. */
#define PLAY32_EXTI_EMR_MR9_POS     (9U)  /**< Bit 9: Event mask on line 9 position. */
#define PLAY32_EXTI_EMR_MR10_POS    (10U) /**< Bit 10: Event mask on line 10 position. */
#define PLAY32_EXTI_EMR_MR11_POS    (11U) /**< Bit 11: Event mask on line 11 position. */
#define PLAY32_EXTI_EMR_MR12_POS    (12U) /**< Bit 12: Event mask on line 12 position. */
#define PLAY32_EXTI_EMR_MR13_POS    (13U) /**< Bit 13: Event mask on line 13 position. */
#define PLAY32_EXTI_EMR_MR14_POS    (14U) /**< Bit 14: Event mask on line 14 position. */
#define PLAY32_EXTI_EMR_MR15_POS    (15U) /**< Bit 15: Event mask on line 15 position. */
#define PLAY32_EXTI_EMR_MR16_POS    (16U) /**< Bit 16: Event mask on line 16 (PVD output) position. */
#define PLAY32_EXTI_EMR_MR17_POS    (17U) /**< Bit 17: Event mask on line 17 (RTC Alarm event) position. */
#define PLAY32_EXTI_EMR_MR18_POS    (18U) /**< Bit 18: Event mask on line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_EMR_MR21_POS    (21U) /**< Bit 21: Event mask on line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_EMR_MR22_POS    (22U) /**< Bit 22: Event mask on line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_EMR_REGISTER_MASK
#define PLAY32_EXTI_EMR_MR0_MSK     (1UL << PLAY32_EXTI_EMR_MR0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_EMR_MR1_MSK     (1UL << PLAY32_EXTI_EMR_MR1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_EMR_MR2_MSK     (1UL << PLAY32_EXTI_EMR_MR2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_EMR_MR3_MSK     (1UL << PLAY32_EXTI_EMR_MR3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_EMR_MR4_MSK     (1UL << PLAY32_EXTI_EMR_MR4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_EMR_MR5_MSK     (1UL << PLAY32_EXTI_EMR_MR5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_EMR_MR6_MSK     (1UL << PLAY32_EXTI_EMR_MR6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_EMR_MR7_MSK     (1UL << PLAY32_EXTI_EMR_MR7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_EMR_MR8_MSK     (1UL << PLAY32_EXTI_EMR_MR8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_EMR_MR9_MSK     (1UL << PLAY32_EXTI_EMR_MR9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_EMR_MR10_MSK    (1UL << PLAY32_EXTI_EMR_MR10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_EMR_MR11_MSK    (1UL << PLAY32_EXTI_EMR_MR11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_EMR_MR12_MSK    (1UL << PLAY32_EXTI_EMR_MR12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_EMR_MR13_MSK    (1UL << PLAY32_EXTI_EMR_MR13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_EMR_MR14_MSK    (1UL << PLAY32_EXTI_EMR_MR14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_EMR_MR15_MSK    (1UL << PLAY32_EXTI_EMR_MR15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_EMR_MR16_MSK    (1UL << PLAY32_EXTI_EMR_MR16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_EMR_MR17_MSK    (1UL << PLAY32_EXTI_EMR_MR17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_EMR_MR18_MSK    (1UL << PLAY32_EXTI_EMR_MR18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_EMR_MR21_MSK    (1UL << PLAY32_EXTI_EMR_MR21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_EMR_MR22_MSK    (1UL << PLAY32_EXTI_EMR_MR22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_EMR_REGISTER_ENUM
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask0;  /**< Event mask type for EXTI line 0. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask1;  /**< Event mask type for EXTI line 1. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask2;  /**< Event mask type for EXTI line 2. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask3;  /**< Event mask type for EXTI line 3. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask4;  /**< Event mask type for EXTI line 4. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask5;  /**< Event mask type for EXTI line 5. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask6;  /**< Event mask type for EXTI line 6. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask7;  /**< Event mask type for EXTI line 7. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask8;  /**< Event mask type for EXTI line 8. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask9;  /**< Event mask type for EXTI line 9. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask10; /**< Event mask type for EXTI line 10. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask11; /**< Event mask type for EXTI line 11. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask12; /**< Event mask type for EXTI line 12. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask13; /**< Event mask type for EXTI line 13. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask14; /**< Event mask type for EXTI line 14. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask15; /**< Event mask type for EXTI line 15. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask16; /**< Event mask type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask17; /**< Event mask type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask18; /**< Event mask type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask21; /**< Event mask type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_EMR_EventMask22; /**< Event mask type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_EMR_Types */

/**
 * @defgroup PLAY32_EXTI_RTSR_Types EXTI Rising Trigger Selection Register (EXTI_RTSR)
 * @brief Bit positions, masks, and rising-edge trigger types for EXTI_RTSR (offset 0x08).
 * @{
 */
#pragma region EXTI_RTSR_REGISTER

#pragma region EXTI_RTSR_REGISTER_POSITION
#define PLAY32_EXTI_RTSR_TR0_POS    (0U)  /**< Bit 0: Rising trigger event configuration bit of line 0 position. */
#define PLAY32_EXTI_RTSR_TR1_POS    (1U)  /**< Bit 1: Rising trigger event configuration bit of line 1 position. */
#define PLAY32_EXTI_RTSR_TR2_POS    (2U)  /**< Bit 2: Rising trigger event configuration bit of line 2 position. */
#define PLAY32_EXTI_RTSR_TR3_POS    (3U)  /**< Bit 3: Rising trigger event configuration bit of line 3 position. */
#define PLAY32_EXTI_RTSR_TR4_POS    (4U)  /**< Bit 4: Rising trigger event configuration bit of line 4 position. */
#define PLAY32_EXTI_RTSR_TR5_POS    (5U)  /**< Bit 5: Rising trigger event configuration bit of line 5 position. */
#define PLAY32_EXTI_RTSR_TR6_POS    (6U)  /**< Bit 6: Rising trigger event configuration bit of line 6 position. */
#define PLAY32_EXTI_RTSR_TR7_POS    (7U)  /**< Bit 7: Rising trigger event configuration bit of line 7 position. */
#define PLAY32_EXTI_RTSR_TR8_POS    (8U)  /**< Bit 8: Rising trigger event configuration bit of line 8 position. */
#define PLAY32_EXTI_RTSR_TR9_POS    (9U)  /**< Bit 9: Rising trigger event configuration bit of line 9 position. */
#define PLAY32_EXTI_RTSR_TR10_POS   (10U) /**< Bit 10: Rising trigger event configuration bit of line 10 position. */
#define PLAY32_EXTI_RTSR_TR11_POS   (11U) /**< Bit 11: Rising trigger event configuration bit of line 11 position. */
#define PLAY32_EXTI_RTSR_TR12_POS   (12U) /**< Bit 12: Rising trigger event configuration bit of line 12 position. */
#define PLAY32_EXTI_RTSR_TR13_POS   (13U) /**< Bit 13: Rising trigger event configuration bit of line 13 position. */
#define PLAY32_EXTI_RTSR_TR14_POS   (14U) /**< Bit 14: Rising trigger event configuration bit of line 14 position. */
#define PLAY32_EXTI_RTSR_TR15_POS   (15U) /**< Bit 15: Rising trigger event configuration bit of line 15 position. */
#define PLAY32_EXTI_RTSR_TR16_POS   (16U) /**< Bit 16: Rising trigger event configuration bit of line 16 (PVD output) position. */
#define PLAY32_EXTI_RTSR_TR17_POS   (17U) /**< Bit 17: Rising trigger event configuration bit of line 17 (RTC Alarm) position. */
#define PLAY32_EXTI_RTSR_TR18_POS   (18U) /**< Bit 18: Rising trigger event configuration bit of line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_RTSR_TR21_POS   (21U) /**< Bit 21: Rising trigger event configuration bit of line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_RTSR_TR22_POS   (22U) /**< Bit 22: Rising trigger event configuration bit of line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_RTSR_REGISTER_MASK
#define PLAY32_EXTI_RTSR_TR0_MSK    (1UL << PLAY32_EXTI_RTSR_TR0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_RTSR_TR1_MSK    (1UL << PLAY32_EXTI_RTSR_TR1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_RTSR_TR2_MSK    (1UL << PLAY32_EXTI_RTSR_TR2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_RTSR_TR3_MSK    (1UL << PLAY32_EXTI_RTSR_TR3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_RTSR_TR4_MSK    (1UL << PLAY32_EXTI_RTSR_TR4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_RTSR_TR5_MSK    (1UL << PLAY32_EXTI_RTSR_TR5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_RTSR_TR6_MSK    (1UL << PLAY32_EXTI_RTSR_TR6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_RTSR_TR7_MSK    (1UL << PLAY32_EXTI_RTSR_TR7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_RTSR_TR8_MSK    (1UL << PLAY32_EXTI_RTSR_TR8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_RTSR_TR9_MSK    (1UL << PLAY32_EXTI_RTSR_TR9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_RTSR_TR10_MSK   (1UL << PLAY32_EXTI_RTSR_TR10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_RTSR_TR11_MSK   (1UL << PLAY32_EXTI_RTSR_TR11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_RTSR_TR12_MSK   (1UL << PLAY32_EXTI_RTSR_TR12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_RTSR_TR13_MSK   (1UL << PLAY32_EXTI_RTSR_TR13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_RTSR_TR14_MSK   (1UL << PLAY32_EXTI_RTSR_TR14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_RTSR_TR15_MSK   (1UL << PLAY32_EXTI_RTSR_TR15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_RTSR_TR16_MSK   (1UL << PLAY32_EXTI_RTSR_TR16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_RTSR_TR17_MSK   (1UL << PLAY32_EXTI_RTSR_TR17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_RTSR_TR18_MSK   (1UL << PLAY32_EXTI_RTSR_TR18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_RTSR_TR21_MSK   (1UL << PLAY32_EXTI_RTSR_TR21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_RTSR_TR22_MSK   (1UL << PLAY32_EXTI_RTSR_TR22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_RTSR_REGISTER_ENUM
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger0;  /**< Rising trigger enable type for EXTI line 0. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger1;  /**< Rising trigger enable type for EXTI line 1. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger2;  /**< Rising trigger enable type for EXTI line 2. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger3;  /**< Rising trigger enable type for EXTI line 3. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger4;  /**< Rising trigger enable type for EXTI line 4. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger5;  /**< Rising trigger enable type for EXTI line 5. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger6;  /**< Rising trigger enable type for EXTI line 6. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger7;  /**< Rising trigger enable type for EXTI line 7. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger8;  /**< Rising trigger enable type for EXTI line 8. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger9;  /**< Rising trigger enable type for EXTI line 9. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger10; /**< Rising trigger enable type for EXTI line 10. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger11; /**< Rising trigger enable type for EXTI line 11. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger12; /**< Rising trigger enable type for EXTI line 12. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger13; /**< Rising trigger enable type for EXTI line 13. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger14; /**< Rising trigger enable type for EXTI line 14. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger15; /**< Rising trigger enable type for EXTI line 15. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger16; /**< Rising trigger enable type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger17; /**< Rising trigger enable type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger18; /**< Rising trigger enable type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger21; /**< Rising trigger enable type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_RTSR_RisingTrigger22; /**< Rising trigger enable type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_RTSR_Types */

/**
 * @defgroup PLAY32_EXTI_FTSR_Types EXTI Falling Trigger Selection Register (EXTI_FTSR)
 * @brief Bit positions, masks, and falling-edge trigger types for EXTI_FTSR (offset 0x0C).
 * @{
 */
#pragma region EXTI_FTSR_REGISTER

#pragma region EXTI_FTSR_REGISTER_POSITION
#define PLAY32_EXTI_FTSR_TR0_POS    (0U)  /**< Bit 0: Falling trigger event configuration bit of line 0 position. */
#define PLAY32_EXTI_FTSR_TR1_POS    (1U)  /**< Bit 1: Falling trigger event configuration bit of line 1 position. */
#define PLAY32_EXTI_FTSR_TR2_POS    (2U)  /**< Bit 2: Falling trigger event configuration bit of line 2 position. */
#define PLAY32_EXTI_FTSR_TR3_POS    (3U)  /**< Bit 3: Falling trigger event configuration bit of line 3 position. */
#define PLAY32_EXTI_FTSR_TR4_POS    (4U)  /**< Bit 4: Falling trigger event configuration bit of line 4 position. */
#define PLAY32_EXTI_FTSR_TR5_POS    (5U)  /**< Bit 5: Falling trigger event configuration bit of line 5 position. */
#define PLAY32_EXTI_FTSR_TR6_POS    (6U)  /**< Bit 6: Falling trigger event configuration bit of line 6 position. */
#define PLAY32_EXTI_FTSR_TR7_POS    (7U)  /**< Bit 7: Falling trigger event configuration bit of line 7 position. */
#define PLAY32_EXTI_FTSR_TR8_POS    (8U)  /**< Bit 8: Falling trigger event configuration bit of line 8 position. */
#define PLAY32_EXTI_FTSR_TR9_POS    (9U)  /**< Bit 9: Falling trigger event configuration bit of line 9 position. */
#define PLAY32_EXTI_FTSR_TR10_POS   (10U) /**< Bit 10: Falling trigger event configuration bit of line 10 position. */
#define PLAY32_EXTI_FTSR_TR11_POS   (11U) /**< Bit 11: Falling trigger event configuration bit of line 11 position. */
#define PLAY32_EXTI_FTSR_TR12_POS   (12U) /**< Bit 12: Falling trigger event configuration bit of line 12 position. */
#define PLAY32_EXTI_FTSR_TR13_POS   (13U) /**< Bit 13: Falling trigger event configuration bit of line 13 position. */
#define PLAY32_EXTI_FTSR_TR14_POS   (14U) /**< Bit 14: Falling trigger event configuration bit of line 14 position. */
#define PLAY32_EXTI_FTSR_TR15_POS   (15U) /**< Bit 15: Falling trigger event configuration bit of line 15 position. */
#define PLAY32_EXTI_FTSR_TR16_POS   (16U) /**< Bit 16: Falling trigger event configuration bit of line 16 (PVD output) position. */
#define PLAY32_EXTI_FTSR_TR17_POS   (17U) /**< Bit 17: Falling trigger event configuration bit of line 17 (RTC Alarm) position. */
#define PLAY32_EXTI_FTSR_TR18_POS   (18U) /**< Bit 18: Falling trigger event configuration bit of line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_FTSR_TR21_POS   (21U) /**< Bit 21: Falling trigger event configuration bit of line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_FTSR_TR22_POS   (22U) /**< Bit 22: Falling trigger event configuration bit of line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_FTSR_REGISTER_MASK
#define PLAY32_EXTI_FTSR_TR0_MSK    (1UL << PLAY32_EXTI_FTSR_TR0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_FTSR_TR1_MSK    (1UL << PLAY32_EXTI_FTSR_TR1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_FTSR_TR2_MSK    (1UL << PLAY32_EXTI_FTSR_TR2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_FTSR_TR3_MSK    (1UL << PLAY32_EXTI_FTSR_TR3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_FTSR_TR4_MSK    (1UL << PLAY32_EXTI_FTSR_TR4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_FTSR_TR5_MSK    (1UL << PLAY32_EXTI_FTSR_TR5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_FTSR_TR6_MSK    (1UL << PLAY32_EXTI_FTSR_TR6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_FTSR_TR7_MSK    (1UL << PLAY32_EXTI_FTSR_TR7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_FTSR_TR8_MSK    (1UL << PLAY32_EXTI_FTSR_TR8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_FTSR_TR9_MSK    (1UL << PLAY32_EXTI_FTSR_TR9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_FTSR_TR10_MSK   (1UL << PLAY32_EXTI_FTSR_TR10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_FTSR_TR11_MSK   (1UL << PLAY32_EXTI_FTSR_TR11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_FTSR_TR12_MSK   (1UL << PLAY32_EXTI_FTSR_TR12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_FTSR_TR13_MSK   (1UL << PLAY32_EXTI_FTSR_TR13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_FTSR_TR14_MSK   (1UL << PLAY32_EXTI_FTSR_TR14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_FTSR_TR15_MSK   (1UL << PLAY32_EXTI_FTSR_TR15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_FTSR_TR16_MSK   (1UL << PLAY32_EXTI_FTSR_TR16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_FTSR_TR17_MSK   (1UL << PLAY32_EXTI_FTSR_TR17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_FTSR_TR18_MSK   (1UL << PLAY32_EXTI_FTSR_TR18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_FTSR_TR21_MSK   (1UL << PLAY32_EXTI_FTSR_TR21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_FTSR_TR22_MSK   (1UL << PLAY32_EXTI_FTSR_TR22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_FTSR_REGISTER_ENUM
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger0;  /**< Falling trigger enable type for EXTI line 0. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger1;  /**< Falling trigger enable type for EXTI line 1. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger2;  /**< Falling trigger enable type for EXTI line 2. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger3;  /**< Falling trigger enable type for EXTI line 3. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger4;  /**< Falling trigger enable type for EXTI line 4. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger5;  /**< Falling trigger enable type for EXTI line 5. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger6;  /**< Falling trigger enable type for EXTI line 6. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger7;  /**< Falling trigger enable type for EXTI line 7. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger8;  /**< Falling trigger enable type for EXTI line 8. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger9;  /**< Falling trigger enable type for EXTI line 9. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger10; /**< Falling trigger enable type for EXTI line 10. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger11; /**< Falling trigger enable type for EXTI line 11. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger12; /**< Falling trigger enable type for EXTI line 12. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger13; /**< Falling trigger enable type for EXTI line 13. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger14; /**< Falling trigger enable type for EXTI line 14. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger15; /**< Falling trigger enable type for EXTI line 15. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger16; /**< Falling trigger enable type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger17; /**< Falling trigger enable type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger18; /**< Falling trigger enable type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger21; /**< Falling trigger enable type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_FTSR_FallingTrigger22; /**< Falling trigger enable type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_FTSR_Types */

/**
 * @defgroup PLAY32_EXTI_SWIER_Types EXTI Software Interrupt Event Register (EXTI_SWIER)
 * @brief Bit positions, masks, and software interrupt trigger types for EXTI_SWIER (offset 0x10).
 * @{
 */
#pragma region EXTI_SWIER_REGISTER

#pragma region EXTI_SWIER_REGISTER_POSITION
#define PLAY32_EXTI_SWIER_SWIER0_POS    (0U)  /**< Bit 0: Software interrupt on line 0 position. */
#define PLAY32_EXTI_SWIER_SWIER1_POS    (1U)  /**< Bit 1: Software interrupt on line 1 position. */
#define PLAY32_EXTI_SWIER_SWIER2_POS    (2U)  /**< Bit 2: Software interrupt on line 2 position. */
#define PLAY32_EXTI_SWIER_SWIER3_POS    (3U)  /**< Bit 3: Software interrupt on line 3 position. */
#define PLAY32_EXTI_SWIER_SWIER4_POS    (4U)  /**< Bit 4: Software interrupt on line 4 position. */
#define PLAY32_EXTI_SWIER_SWIER5_POS    (5U)  /**< Bit 5: Software interrupt on line 5 position. */
#define PLAY32_EXTI_SWIER_SWIER6_POS    (6U)  /**< Bit 6: Software interrupt on line 6 position. */
#define PLAY32_EXTI_SWIER_SWIER7_POS    (7U)  /**< Bit 7: Software interrupt on line 7 position. */
#define PLAY32_EXTI_SWIER_SWIER8_POS    (8U)  /**< Bit 8: Software interrupt on line 8 position. */
#define PLAY32_EXTI_SWIER_SWIER9_POS    (9U)  /**< Bit 9: Software interrupt on line 9 position. */
#define PLAY32_EXTI_SWIER_SWIER10_POS   (10U) /**< Bit 10: Software interrupt on line 10 position. */
#define PLAY32_EXTI_SWIER_SWIER11_POS   (11U) /**< Bit 11: Software interrupt on line 11 position. */
#define PLAY32_EXTI_SWIER_SWIER12_POS   (12U) /**< Bit 12: Software interrupt on line 12 position. */
#define PLAY32_EXTI_SWIER_SWIER13_POS   (13U) /**< Bit 13: Software interrupt on line 13 position. */
#define PLAY32_EXTI_SWIER_SWIER14_POS   (14U) /**< Bit 14: Software interrupt on line 14 position. */
#define PLAY32_EXTI_SWIER_SWIER15_POS   (15U) /**< Bit 15: Software interrupt on line 15 position. */
#define PLAY32_EXTI_SWIER_SWIER16_POS   (16U) /**< Bit 16: Software interrupt on line 16 (PVD) position. */
#define PLAY32_EXTI_SWIER_SWIER17_POS   (17U) /**< Bit 17: Software interrupt on line 17 (RTC Alarm) position. */
#define PLAY32_EXTI_SWIER_SWIER18_POS   (18U) /**< Bit 18: Software interrupt on line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_SWIER_SWIER21_POS   (21U) /**< Bit 21: Software interrupt on line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_SWIER_SWIER22_POS   (22U) /**< Bit 22: Software interrupt on line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_SWIER_REGISTER_MASK
#define PLAY32_EXTI_SWIER_SWIER0_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_SWIER_SWIER1_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_SWIER_SWIER2_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_SWIER_SWIER3_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_SWIER_SWIER4_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_SWIER_SWIER5_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_SWIER_SWIER6_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_SWIER_SWIER7_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_SWIER_SWIER8_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_SWIER_SWIER9_MSK    (1UL << PLAY32_EXTI_SWIER_SWIER9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_SWIER_SWIER10_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_SWIER_SWIER11_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_SWIER_SWIER12_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_SWIER_SWIER13_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_SWIER_SWIER14_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_SWIER_SWIER15_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_SWIER_SWIER16_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_SWIER_SWIER17_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_SWIER_SWIER18_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_SWIER_SWIER21_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_SWIER_SWIER22_MSK   (1UL << PLAY32_EXTI_SWIER_SWIER22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_SWIER_REGISTER_ENUM
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt0;  /**< Software interrupt trigger type for EXTI line 0. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt1;  /**< Software interrupt trigger type for EXTI line 1. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt2;  /**< Software interrupt trigger type for EXTI line 2. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt3;  /**< Software interrupt trigger type for EXTI line 3. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt4;  /**< Software interrupt trigger type for EXTI line 4. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt5;  /**< Software interrupt trigger type for EXTI line 5. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt6;  /**< Software interrupt trigger type for EXTI line 6. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt7;  /**< Software interrupt trigger type for EXTI line 7. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt8;  /**< Software interrupt trigger type for EXTI line 8. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt9;  /**< Software interrupt trigger type for EXTI line 9. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt10; /**< Software interrupt trigger type for EXTI line 10. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt11; /**< Software interrupt trigger type for EXTI line 11. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt12; /**< Software interrupt trigger type for EXTI line 12. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt13; /**< Software interrupt trigger type for EXTI line 13. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt14; /**< Software interrupt trigger type for EXTI line 14. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt15; /**< Software interrupt trigger type for EXTI line 15. */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt16; /**< Software interrupt trigger type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt17; /**< Software interrupt trigger type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt18; /**< Software interrupt trigger type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt21; /**< Software interrupt trigger type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Switch PLAY32_EXTI_SWIER_SoftwareInterrupt22; /**< Software interrupt trigger type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_SWIER_Types */

/**
 * @defgroup PLAY32_EXTI_PR_Types EXTI Pending Register (EXTI_PR)
 * @brief Bit positions, masks, and pending status flag types for EXTI_PR (offset 0x14, rc_w1).
 * @{
 */
#pragma region EXTI_PR_REGISTER

#pragma region EXTI_PR_REGISTER_POSITION
#define PLAY32_EXTI_PR_PR0_POS      (0U)  /**< Bit 0: Pending bit on line 0 position. */
#define PLAY32_EXTI_PR_PR1_POS      (1U)  /**< Bit 1: Pending bit on line 1 position. */
#define PLAY32_EXTI_PR_PR2_POS      (2U)  /**< Bit 2: Pending bit on line 2 position. */
#define PLAY32_EXTI_PR_PR3_POS      (3U)  /**< Bit 3: Pending bit on line 3 position. */
#define PLAY32_EXTI_PR_PR4_POS      (4U)  /**< Bit 4: Pending bit on line 4 position. */
#define PLAY32_EXTI_PR_PR5_POS      (5U)  /**< Bit 5: Pending bit on line 5 position. */
#define PLAY32_EXTI_PR_PR6_POS      (6U)  /**< Bit 6: Pending bit on line 6 position. */
#define PLAY32_EXTI_PR_PR7_POS      (7U)  /**< Bit 7: Pending bit on line 7 position. */
#define PLAY32_EXTI_PR_PR8_POS      (8U)  /**< Bit 8: Pending bit on line 8 position. */
#define PLAY32_EXTI_PR_PR9_POS      (9U)  /**< Bit 9: Pending bit on line 9 position. */
#define PLAY32_EXTI_PR_PR10_POS     (10U) /**< Bit 10: Pending bit on line 10 position. */
#define PLAY32_EXTI_PR_PR11_POS     (11U) /**< Bit 11: Pending bit on line 11 position. */
#define PLAY32_EXTI_PR_PR12_POS     (12U) /**< Bit 12: Pending bit on line 12 position. */
#define PLAY32_EXTI_PR_PR13_POS     (13U) /**< Bit 13: Pending bit on line 13 position. */
#define PLAY32_EXTI_PR_PR14_POS     (14U) /**< Bit 14: Pending bit on line 14 position. */
#define PLAY32_EXTI_PR_PR15_POS     (15U) /**< Bit 15: Pending bit on line 15 position. */
#define PLAY32_EXTI_PR_PR16_POS     (16U) /**< Bit 16: Pending bit on line 16 (PVD) position. */
#define PLAY32_EXTI_PR_PR17_POS     (17U) /**< Bit 17: Pending bit on line 17 (RTC Alarm) position. */
#define PLAY32_EXTI_PR_PR18_POS     (18U) /**< Bit 18: Pending bit on line 18 (USB OTG FS Wakeup) position. */
#define PLAY32_EXTI_PR_PR21_POS     (21U) /**< Bit 21: Pending bit on line 21 (RTC Tamper/TimeStamp) position. */
#define PLAY32_EXTI_PR_PR22_POS     (22U) /**< Bit 22: Pending bit on line 22 (RTC Wakeup) position. */
#pragma endregion

#pragma region EXTI_PR_REGISTER_MASK
#define PLAY32_EXTI_PR_PR0_MSK      (1UL << PLAY32_EXTI_PR_PR0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_EXTI_PR_PR1_MSK      (1UL << PLAY32_EXTI_PR_PR1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_EXTI_PR_PR2_MSK      (1UL << PLAY32_EXTI_PR_PR2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_EXTI_PR_PR3_MSK      (1UL << PLAY32_EXTI_PR_PR3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_EXTI_PR_PR4_MSK      (1UL << PLAY32_EXTI_PR_PR4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_EXTI_PR_PR5_MSK      (1UL << PLAY32_EXTI_PR_PR5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_EXTI_PR_PR6_MSK      (1UL << PLAY32_EXTI_PR_PR6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_EXTI_PR_PR7_MSK      (1UL << PLAY32_EXTI_PR_PR7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_EXTI_PR_PR8_MSK      (1UL << PLAY32_EXTI_PR_PR8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_EXTI_PR_PR9_MSK      (1UL << PLAY32_EXTI_PR_PR9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_EXTI_PR_PR10_MSK     (1UL << PLAY32_EXTI_PR_PR10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_EXTI_PR_PR11_MSK     (1UL << PLAY32_EXTI_PR_PR11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_EXTI_PR_PR12_MSK     (1UL << PLAY32_EXTI_PR_PR12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_EXTI_PR_PR13_MSK     (1UL << PLAY32_EXTI_PR_PR13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_EXTI_PR_PR14_MSK     (1UL << PLAY32_EXTI_PR_PR14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_EXTI_PR_PR15_MSK     (1UL << PLAY32_EXTI_PR_PR15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_EXTI_PR_PR16_MSK     (1UL << PLAY32_EXTI_PR_PR16_POS) /**< Bit 16 mask (0x00010000). */
#define PLAY32_EXTI_PR_PR17_MSK     (1UL << PLAY32_EXTI_PR_PR17_POS) /**< Bit 17 mask (0x00020000). */
#define PLAY32_EXTI_PR_PR18_MSK     (1UL << PLAY32_EXTI_PR_PR18_POS) /**< Bit 18 mask (0x00040000). */
#define PLAY32_EXTI_PR_PR21_MSK     (1UL << PLAY32_EXTI_PR_PR21_POS) /**< Bit 21 mask (0x00200000). */
#define PLAY32_EXTI_PR_PR22_MSK     (1UL << PLAY32_EXTI_PR_PR22_POS) /**< Bit 22 mask (0x00400000). */
#pragma endregion

#pragma region EXTI_PR_REGISTER_ENUM
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending0;  /**< Pending status flag type for EXTI line 0. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending1;  /**< Pending status flag type for EXTI line 1. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending2;  /**< Pending status flag type for EXTI line 2. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending3;  /**< Pending status flag type for EXTI line 3. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending4;  /**< Pending status flag type for EXTI line 4. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending5;  /**< Pending status flag type for EXTI line 5. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending6;  /**< Pending status flag type for EXTI line 6. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending7;  /**< Pending status flag type for EXTI line 7. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending8;  /**< Pending status flag type for EXTI line 8. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending9;  /**< Pending status flag type for EXTI line 9. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending10; /**< Pending status flag type for EXTI line 10. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending11; /**< Pending status flag type for EXTI line 11. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending12; /**< Pending status flag type for EXTI line 12. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending13; /**< Pending status flag type for EXTI line 13. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending14; /**< Pending status flag type for EXTI line 14. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending15; /**< Pending status flag type for EXTI line 15. */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending16; /**< Pending status flag type for EXTI line 16 (PVD). */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending17; /**< Pending status flag type for EXTI line 17 (RTC Alarm). */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending18; /**< Pending status flag type for EXTI line 18 (USB OTG FS Wakeup). */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending21; /**< Pending status flag type for EXTI line 21 (RTC Tamper/TimeStamp). */
typedef PLAY32_EXTI_Flag PLAY32_EXTI_PR_Pending22; /**< Pending status flag type for EXTI line 22 (RTC Wakeup). */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_EXTI_PR_Types */

/** @} */ /* End of PLAY32_EXTI */

#endif /* PLAY32_EXTI_TYPES_H */
