/**
 * @file    syscfg_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for System Configuration Controller (SYSCFG) of STM32F401 CCU.
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

#ifndef PLAY32_SYSCFG_TYPES_H
#define PLAY32_SYSCFG_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_SYSCFG System Configuration Controller (SYSCFG)
 * @brief Hardware register map, base address, bit masks, and type-safe enumerations for SYSCFG.
 * @{
 */

/**
 * @defgroup PLAY32_SYSCFG_Memory_Map Peripheral Base Address and Register Map
 * @brief APB2 base address calculation and memory-mapped register structure for SYSCFG.
 * @{
 */

/**
 * @brief  Base address of the APB2 peripheral bus (0x40010000).
 * @note   SYSCFG is mapped onto the APB2 peripheral bus in STM32F401.
 */
#define PLAY32_APB2_PERIPHERAL      ((1UL << 30) | (1UL << 16))

/**
 * @brief  Standard peripheral memory block stride (0x0400 bytes / 1 KB).
 */
#define PLAY32_BLOCK_SIZE           (1UL << 10)

/**
 * @brief  APB2 memory slot index for SYSCFG (offset 14 * 0x0400 = 0x3800).
 * @see    PLAY32_SYSCFG_BASE
 */
#define PLAY32_SYSCFG_BASE_POS      (14U)

/**
 * @brief  SYSCFG peripheral base address (0x40013800).
 * @note   Computed from @ref PLAY32_APB2_PERIPHERAL and @ref PLAY32_SYSCFG_BASE_POS.
 */
#define PLAY32_SYSCFG_BASE          (PLAY32_APB2_PERIPHERAL + (PLAY32_SYSCFG_BASE_POS * PLAY32_BLOCK_SIZE))

/**
 * @brief  System Configuration Controller (SYSCFG) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 7.2.7, offsets 0x00-0x20).
 */
typedef struct {
    volatile uint32_t MEMRMP;      /**< Offset: 0x00 - Memory remap register. */
    volatile uint32_t PMC;         /**< Offset: 0x04 - Peripheral mode configuration register. */
    volatile uint32_t EXTICR1;     /**< Offset: 0x08 - External interrupt configuration register 1 (EXTI0-EXTI3). */
    volatile uint32_t EXTICR2;     /**< Offset: 0x0C - External interrupt configuration register 2 (EXTI4-EXTI7). */
    volatile uint32_t EXTICR3;     /**< Offset: 0x10 - External interrupt configuration register 3 (EXTI8-EXTI11). */
    volatile uint32_t EXTICR4;     /**< Offset: 0x14 - External interrupt configuration register 4 (EXTI12-EXTI15). */
    uint32_t          RESERVED[2]; /**< Offset: 0x18-0x1C - Reserved. */
    volatile uint32_t CMPCR;       /**< Offset: 0x20 - Compensation cell control register. */
} PLAY32_SYSCFG_TypeDef;

/** @brief SYSCFG peripheral register map pointer (APB2, 0x40013800). */
#define PLAY32_SYSCFG ((PLAY32_SYSCFG_TypeDef *)PLAY32_SYSCFG_BASE)

/** @} */ /* End of PLAY32_SYSCFG_Memory_Map */

/**
 * @defgroup PLAY32_SYSCFG_Common_Types Common SYSCFG Enumerations
 * @brief Reusable control switch, status flag, and EXTI port source enumerations across SYSCFG registers.
 * @{
 */
#pragma region SYSCFG_COMMON_ENUM

/**
 * @brief  Standard active-high control switch states for SYSCFG feature enable bits.
 */
typedef enum {
    PLAY32_SYSCFG_SWITCH_DISABLED = 0U, /**< Feature disabled (0). */
    PLAY32_SYSCFG_SWITCH_ENABLED  = 1U  /**< Feature enabled (1). */
} PLAY32_SYSCFG_Switch;

/**
 * @brief  SYSCFG hardware status flag state enumeration.
 */
typedef enum {
    PLAY32_SYSCFG_FLAG_NOT_SET = 0U, /**< Status flag is cleared (0). */
    PLAY32_SYSCFG_FLAG_SET     = 1U  /**< Status flag is set (1). */
} PLAY32_SYSCFG_Flag;

/**
 * @brief  GPIO port source selection enumeration for `SYSCFG_EXTICR1`–`SYSCFG_EXTICR4` (`EXTIx[3:0]`).
 * @note   Shared across all 16 external interrupt lines (`EXTI0` to `EXTI15`) on STM32F401.
 */
typedef enum {
    PLAY32_SYSCFG_EXTI_PORT_GPIOA = 0U, /**< Select Port A (`PAx`) as EXTI line source (0000). */
    PLAY32_SYSCFG_EXTI_PORT_GPIOB = 1U, /**< Select Port B (`PBx`) as EXTI line source (0001). */
    PLAY32_SYSCFG_EXTI_PORT_GPIOC = 2U, /**< Select Port C (`PCx`) as EXTI line source (0010). */
    PLAY32_SYSCFG_EXTI_PORT_GPIOD = 3U, /**< Select Port D (`PDx`) as EXTI line source (0011). */
    PLAY32_SYSCFG_EXTI_PORT_GPIOE = 4U, /**< Select Port E (`PEx`) as EXTI line source (0100). */
    PLAY32_SYSCFG_EXTI_PORT_GPIOH = 7U  /**< Select Port H (`PHx`) as EXTI line source (0111). */
} PLAY32_SYSCFG_EXTIPortSource;

#pragma endregion
/** @} */ /* End of PLAY32_SYSCFG_Common_Types */
/**
 * @defgroup PLAY32_SYSCFG_MEMRMP_Types SYSCFG Memory Remap Register (SYSCFG_MEMRMP)
 * @brief Bit positions, masks, and boot memory mapping types for SYSCFG_MEMRMP (offset 0x00).
 * @{
 */
#pragma region SYSCFG_MEMRMP_REGISTER

#pragma region SYSCFG_MEMRMP_REGISTER_POSITION
#define PLAY32_SYSCFG_MEMRMP_MEM_MODE_POS   (0U) /**< Bits [1:0]: Memory mapping selection position. */
#pragma endregion

#pragma region SYSCFG_MEMRMP_REGISTER_MASK
#define PLAY32_SYSCFG_MEMRMP_MEM_MODE_MSK   (3UL << PLAY32_SYSCFG_MEMRMP_MEM_MODE_POS) /**< Bits [1:0] mask (0x00000003). */
#pragma endregion

#pragma region SYSCFG_MEMRMP_REGISTER_ENUM

/**
 * @brief  Memory mapping selection (`MEM_MODE[1:0]`) enumeration for address `0x00000000`.
 * @note   Read/Write 2-bit field (bits 1:0 of SYSCFG_MEMRMP, MEM_MODE[1:0]) initialized from
 *         the hardware `BOOT0` and `BOOT1` pins at reset and writable by software to remap
 *         the vector table at `0x00000000` (e.g., to Embedded SRAM for RAM-based bootloaders).
 */
typedef enum {
    PLAY32_SYSCFG_MEMRMP_MEMORY_MODE_MAIN_FLASH    = 0U, /**< Main Flash memory mapped at 0x00000000 (00). */
    PLAY32_SYSCFG_MEMRMP_MEMORY_MODE_SYSTEM_FLASH  = 1U, /**< System Flash memory (ST bootloader) mapped at 0x00000000 (01). */
    PLAY32_SYSCFG_MEMRMP_MEMORY_MODE_EMBEDDED_SRAM = 3U  /**< Embedded SRAM (96 KB) mapped at 0x00000000 (11). */
} PLAY32_SYSCFG_MEMRMP_MemoryMode;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_SYSCFG_MEMRMP_Types */

/**
 * @defgroup PLAY32_SYSCFG_PMC_Types SYSCFG Peripheral Mode Configuration Register (SYSCFG_PMC)
 * @brief Bit positions, masks, and ADC noise-reduction types for SYSCFG_PMC (offset 0x04).
 * @{
 */
#pragma region SYSCFG_PMC_REGISTER

#pragma region SYSCFG_PMC_REGISTER_POSITION
#define PLAY32_SYSCFG_PMC_ADC1DC2_POS       (16U) /**< Bit 16: ADC1 DC2 noise reduction bit position. */
#pragma endregion

#pragma region SYSCFG_PMC_REGISTER_MASK
#define PLAY32_SYSCFG_PMC_ADC1DC2_MSK       (1UL << PLAY32_SYSCFG_PMC_ADC1DC2_POS) /**< Bit 16 mask (0x00010000). */
#pragma endregion

#pragma region SYSCFG_PMC_REGISTER_ENUM

/**
 * @brief  ADC1 DC2 noise reduction (`ADC1DC2`) control state type.
 * @note   Read/Write control bit (bit 16 of SYSCFG_PMC, ADC1DC2) used alongside `ADCDC1` in `PWR_CR`
 *         to reduce internal switching noise during `ADC1` conversions per STM32F401 errata/datasheet.
 * @warning Must only be modified when `ADC1` is disabled (`ADON = 0`).
 * @see    PLAY32_SYSCFG_Switch
 */
typedef PLAY32_SYSCFG_Switch PLAY32_SYSCFG_PMC_ADC1DC2;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_SYSCFG_PMC_Types */
/**
 * @defgroup PLAY32_SYSCFG_EXTICR_Types SYSCFG External Interrupt Configuration Registers (SYSCFG_EXTICR1-4)
 * @brief Bit positions, masks, and port-mapping typedefs for EXTI0 through EXTI15 (offsets 0x08-0x14).
 * @{
 */
#pragma region SYSCFG_EXTICR_REGISTERS

#pragma region SYSCFG_EXTICR_REGISTER_POSITION
#define PLAY32_SYSCFG_EXTICR1_EXTI0_POS     (0U)  /**< Bits [3:0]: EXTI0 port configuration position. */
#define PLAY32_SYSCFG_EXTICR1_EXTI1_POS     (4U)  /**< Bits [7:4]: EXTI1 port configuration position. */
#define PLAY32_SYSCFG_EXTICR1_EXTI2_POS     (8U)  /**< Bits [11:8]: EXTI2 port configuration position. */
#define PLAY32_SYSCFG_EXTICR1_EXTI3_POS     (12U) /**< Bits [15:12]: EXTI3 port configuration position. */

#define PLAY32_SYSCFG_EXTICR2_EXTI4_POS     (0U)  /**< Bits [3:0]: EXTI4 port configuration position. */
#define PLAY32_SYSCFG_EXTICR2_EXTI5_POS     (4U)  /**< Bits [7:4]: EXTI5 port configuration position. */
#define PLAY32_SYSCFG_EXTICR2_EXTI6_POS     (8U)  /**< Bits [11:8]: EXTI6 port configuration position. */
#define PLAY32_SYSCFG_EXTICR2_EXTI7_POS     (12U) /**< Bits [15:12]: EXTI7 port configuration position. */

#define PLAY32_SYSCFG_EXTICR3_EXTI8_POS     (0U)  /**< Bits [3:0]: EXTI8 port configuration position. */
#define PLAY32_SYSCFG_EXTICR3_EXTI9_POS     (4U)  /**< Bits [7:4]: EXTI9 port configuration position. */
#define PLAY32_SYSCFG_EXTICR3_EXTI10_POS    (8U)  /**< Bits [11:8]: EXTI10 port configuration position. */
#define PLAY32_SYSCFG_EXTICR3_EXTI11_POS    (12U) /**< Bits [15:12]: EXTI11 port configuration position. */

#define PLAY32_SYSCFG_EXTICR4_EXTI12_POS    (0U)  /**< Bits [3:0]: EXTI12 port configuration position. */
#define PLAY32_SYSCFG_EXTICR4_EXTI13_POS    (4U)  /**< Bits [7:4]: EXTI13 port configuration position. */
#define PLAY32_SYSCFG_EXTICR4_EXTI14_POS    (8U)  /**< Bits [11:8]: EXTI14 port configuration position. */
#define PLAY32_SYSCFG_EXTICR4_EXTI15_POS    (12U) /**< Bits [15:12]: EXTI15 port configuration position. */
#pragma endregion

#pragma region SYSCFG_EXTICR_REGISTER_MASK
#define PLAY32_SYSCFG_EXTICR1_EXTI0_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR1_EXTI0_POS)  /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_SYSCFG_EXTICR1_EXTI1_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR1_EXTI1_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_SYSCFG_EXTICR1_EXTI2_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR1_EXTI2_POS)  /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_SYSCFG_EXTICR1_EXTI3_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR1_EXTI3_POS)  /**< Bits [15:12] mask (0x0000F000). */

#define PLAY32_SYSCFG_EXTICR2_EXTI4_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR2_EXTI4_POS)  /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_SYSCFG_EXTICR2_EXTI5_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR2_EXTI5_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_SYSCFG_EXTICR2_EXTI6_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR2_EXTI6_POS)  /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_SYSCFG_EXTICR2_EXTI7_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR2_EXTI7_POS)  /**< Bits [15:12] mask (0x0000F000). */

#define PLAY32_SYSCFG_EXTICR3_EXTI8_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR3_EXTI8_POS)  /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_SYSCFG_EXTICR3_EXTI9_MSK     (0xFUL << PLAY32_SYSCFG_EXTICR3_EXTI9_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_SYSCFG_EXTICR3_EXTI10_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR3_EXTI10_POS) /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_SYSCFG_EXTICR3_EXTI11_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR3_EXTI11_POS) /**< Bits [15:12] mask (0x0000F000). */

#define PLAY32_SYSCFG_EXTICR4_EXTI12_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR4_EXTI12_POS) /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_SYSCFG_EXTICR4_EXTI13_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR4_EXTI13_POS) /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_SYSCFG_EXTICR4_EXTI14_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR4_EXTI14_POS) /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_SYSCFG_EXTICR4_EXTI15_MSK    (0xFUL << PLAY32_SYSCFG_EXTICR4_EXTI15_POS) /**< Bits [15:12] mask (0x0000F000). */
#pragma endregion

#pragma region SYSCFG_EXTICR_REGISTER_ENUM
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR1_ExternalInterrupt0;  /**< Port source type for EXTI line 0. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR1_ExternalInterrupt1;  /**< Port source type for EXTI line 1. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR1_ExternalInterrupt2;  /**< Port source type for EXTI line 2. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR1_ExternalInterrupt3;  /**< Port source type for EXTI line 3. */

typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR2_ExternalInterrupt4;  /**< Port source type for EXTI line 4. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR2_ExternalInterrupt5;  /**< Port source type for EXTI line 5. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR2_ExternalInterrupt6;  /**< Port source type for EXTI line 6. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR2_ExternalInterrupt7;  /**< Port source type for EXTI line 7. */

typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR3_ExternalInterrupt8;  /**< Port source type for EXTI line 8. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR3_ExternalInterrupt9;  /**< Port source type for EXTI line 9. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR3_ExternalInterrupt10; /**< Port source type for EXTI line 10. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR3_ExternalInterrupt11; /**< Port source type for EXTI line 11. */

typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR4_ExternalInterrupt12; /**< Port source type for EXTI line 12. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR4_ExternalInterrupt13; /**< Port source type for EXTI line 13. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR4_ExternalInterrupt14; /**< Port source type for EXTI line 14. */
typedef PLAY32_SYSCFG_EXTIPortSource PLAY32_SYSCFG_EXTICR4_ExternalInterrupt15; /**< Port source type for EXTI line 15. */
#pragma endregion

#pragma endregion
/** @} */ /* End of PLAY32_SYSCFG_EXTICR_Types */

/**
 * @defgroup PLAY32_SYSCFG_CMPCR_Types SYSCFG Compensation Cell Control Register (SYSCFG_CMPCR)
 * @brief Bit positions, masks, and I/O compensation cell types for SYSCFG_CMPCR (offset 0x20).
 * @{
 */
#pragma region SYSCFG_CMPCR_REGISTER

#pragma region SYSCFG_CMPCR_REGISTER_POSITION
#define PLAY32_SYSCFG_CMPCR_CMP_PD_POS      (0U) /**< Bit 0: Compensation cell power-down position. */
#define PLAY32_SYSCFG_CMPCR_READY_POS       (8U) /**< Bit 8: Compensation cell ready flag position. */
#pragma endregion

#pragma region SYSCFG_CMPCR_REGISTER_MASK
#define PLAY32_SYSCFG_CMPCR_CMP_PD_MSK      (1UL << PLAY32_SYSCFG_CMPCR_CMP_PD_POS) /**< Bit 0 mask (0x00000001). */
#define PLAY32_SYSCFG_CMPCR_READY_MSK       (1UL << PLAY32_SYSCFG_CMPCR_READY_POS)  /**< Bit 8 mask (0x00000100). */
#pragma endregion

#pragma region SYSCFG_CMPCR_REGISTER_ENUM

/**
 * @brief  I/O compensation cell power-down (`CMP_PD`) control enumeration.
 * @note   Read/Write control bit (bit 0 of SYSCFG_CMPCR, CMP_PD). Enabling the compensation cell
 *         reduces I/O switching noise on the power supply when GPIO pins operate at > 50 MHz (`OSPEEDR = High/Very High`).
 * @warning May only be enabled when supply voltage `VDD` is between `2.4 V` and `3.6 V`.
 */
typedef enum {
    PLAY32_SYSCFG_CMPCR_COMPENSATION_CELL_POWER_DOWN = 0U, /**< I/O compensation cell powered down (0). */
    PLAY32_SYSCFG_CMPCR_COMPENSATION_CELL_ENABLED    = 1U  /**< I/O compensation cell enabled (1). */
} PLAY32_SYSCFG_CMPCR_CompensationCellPowerDown;

/**
 * @brief  I/O compensation cell ready (`READY`) status flag type.
 * @note   Read-only flag (bit 8 of SYSCFG_CMPCR, READY) set by hardware once the I/O compensation
 *         cell has stabilized after setting `CMP_PD = 1`.
 * @see    PLAY32_SYSCFG_Flag
 */
typedef PLAY32_SYSCFG_Flag PLAY32_SYSCFG_CMPCR_Ready;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_SYSCFG_CMPCR_Types */

/** @} */ /* End of PLAY32_SYSCFG */

#endif /* PLAY32_SYSCFG_TYPES_H */
