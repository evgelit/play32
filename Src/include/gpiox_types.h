/**
 * @file    gpiox_types.h
 * @author  Eugene Litvin
 * @brief   Universal type definitions, bit positions, masks, and enums
 *          for General-Purpose Input-Output (GPIOA-GPIOH) of STM32F401 CCU.
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

#ifndef PLAY32_GPIOx_TYPES_H
#define PLAY32_GPIOx_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_GPIOx General-Purpose Input-Output (GPIOA-GPIOH)
 * @brief Hardware register map, base addresses, bit masks, and type-safe enumerations for GPIO ports.
 * @{
 */

/**
 * @defgroup PLAY32_GPIOx_Memory_Map Peripheral Base Addresses and Instances
 * @brief AHB1 base addresses, address offsets, and peripheral pointer declarations for GPIOA-GPIOH.
 * @{
 */

/**
 * @brief  Base address of the AHB1 GPIO peripheral block (0x40020000).
 * @note   GPIOA through GPIOE and GPIOH are mapped sequentially on the AHB1 bus in STM32F401.
 */
#define PLAY32_GPIOx_PERIPHERAL    ((1UL << 30) + (1UL << 17))

/**
 * @brief  Memory block size allocated per GPIO port instance (0x0400 bytes / 1 KB).
 * @note   Used as the address stride between consecutive AHB1 GPIO port boundaries.
 */
#define PLAY32_GPIOx_SIZE          (0x0400U)

/**
 * @brief  AHB1 memory slot index for GPIOA (offset 0x0000).
 * @see    PLAY32_GPIOA_BASE
 */
#define PLAY32_GPIOA_BASE_POS      (0U)

/**
 * @brief  AHB1 memory slot index for GPIOB (offset 0x0400).
 * @see    PLAY32_GPIOB_BASE
 */
#define PLAY32_GPIOB_BASE_POS      (1U)

/**
 * @brief  AHB1 memory slot index for GPIOC (offset 0x0800).
 * @see    PLAY32_GPIOC_BASE
 */
#define PLAY32_GPIOC_BASE_POS      (2U)

/**
 * @brief  AHB1 memory slot index for GPIOD (offset 0x0C00).
 * @see    PLAY32_GPIOD_BASE
 */
#define PLAY32_GPIOD_BASE_POS      (3U)

/**
 * @brief  AHB1 memory slot index for GPIOE (offset 0x1000).
 * @see    PLAY32_GPIOE_BASE
 */
#define PLAY32_GPIOE_BASE_POS      (4U)

/**
 * @brief  AHB1 memory slot index for GPIOH (offset 0x1C00).
 * @note   Slots 5 (GPIOF) and 6 (GPIOG) are not present on the STM32F401 device.
 * @see    PLAY32_GPIOH_BASE
 */
#define PLAY32_GPIOH_BASE_POS      (7U)

/**
 * @brief  GPIOA peripheral base address (0x40020000).
 * @see    PLAY32_GPIOA
 */
#define PLAY32_GPIOA_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOA_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  GPIOB peripheral base address (0x40020400).
 * @see    PLAY32_GPIOB
 */
#define PLAY32_GPIOB_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOB_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  GPIOC peripheral base address (0x40020800).
 * @see    PLAY32_GPIOC
 */
#define PLAY32_GPIOC_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOC_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  GPIOD peripheral base address (0x40020C00).
 * @see    PLAY32_GPIOD
 */
#define PLAY32_GPIOD_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOD_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  GPIOE peripheral base address (0x40021000).
 * @see    PLAY32_GPIOE
 */
#define PLAY32_GPIOE_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOE_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  GPIOH peripheral base address (0x40021C00).
 * @see    PLAY32_GPIOH
 */
#define PLAY32_GPIOH_BASE          (PLAY32_GPIOx_PERIPHERAL + (PLAY32_GPIOH_BASE_POS * PLAY32_GPIOx_SIZE))

/**
 * @brief  General-Purpose I/O (GPIOA-GPIOH) hardware register map structure.
 * @note   Matches the memory-mapped register layout in STM32F401 RM0368 (Section 8.4).
 * @warning Remember to enable the corresponding GPIOx peripheral clock in `RCC_AHB1ENR`
 *          (and allow a 2-cycle AHB1 bus delay) before accessing any port registers.
 */
typedef struct {
    volatile uint32_t MODER;        /**< Offset: 0x00 - GPIO port mode register. */
    volatile uint32_t OTYPER;       /**< Offset: 0x04 - GPIO port output type register. */
    volatile uint32_t OSPEEDR;      /**< Offset: 0x08 - GPIO port output speed register. */
    volatile uint32_t PUPDR;        /**< Offset: 0x0C - GPIO port pull-up/pull-down register. */
    volatile uint32_t IDR;          /**< Offset: 0x10 - GPIO port input data register (read-only). */
    volatile uint32_t ODR;          /**< Offset: 0x14 - GPIO port output data register. */
    volatile uint32_t BSRR;         /**< Offset: 0x18 - GPIO port bit set/reset register (write-only). */
    volatile uint32_t LCKR;         /**< Offset: 0x1C - GPIO port configuration lock register. */
    volatile uint32_t AFRL;         /**< Offset: 0x20 - GPIO alternate function low register (pins 0-7). */
    volatile uint32_t AFRH;         /**< Offset: 0x24 - GPIO alternate function high register (pins 8-15). */
} PLAY32_GPIOx_TypeDef;

/** @brief GPIOA peripheral register map pointer (pins PA0-PA15; PA13-PA15 default to JTAG/SWD after reset). */
#define PLAY32_GPIOA ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOA_BASE)

/** @brief GPIOB peripheral register map pointer (pins PB0-PB15; PB3-PB4 default to JTAG/SWD after reset). */
#define PLAY32_GPIOB ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOB_BASE)

/** @brief GPIOC peripheral register map pointer (pins PC0-PC15). */
#define PLAY32_GPIOC ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOC_BASE)

/** @brief GPIOD peripheral register map pointer (pins PD0-PD15). */
#define PLAY32_GPIOD ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOD_BASE)

/** @brief GPIOE peripheral register map pointer (pins PE0-PE15). */
#define PLAY32_GPIOE ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOE_BASE)

/** @brief GPIOH peripheral register map pointer (pins PH0-PH1 / HSE oscillator pins). */
#define PLAY32_GPIOH ((PLAY32_GPIOx_TypeDef *)PLAY32_GPIOH_BASE)

/** @} */ /* End of PLAY32_GPIOx_Memory_Map */
/**
 * @defgroup PLAY32_GPIOx_Common_Types Common GPIO Enumerations
 * @brief Reusable logic level, pin bitmask, and alternate function enumerations across GPIOx registers.
 * @{
 */
#pragma region GPIOx_COMMON_ENUM

/**
 * @brief  GPIO pin digital logic level enumeration.
 * @note   Generic 1-bit logic state type used across IDR, ODR, and BSRR operations
 *         to represent low (0 V) or high (VDD) pin states.
 * @see    PLAY32_GPIOx_PinList
 */
typedef enum {
    PLAY32_GPIOx_LEVEL_LOW  = 0U, /**< Logic low state (0). */
    PLAY32_GPIOx_LEVEL_HIGH = 1U  /**< Logic high state (1). */
} PLAY32_GPIOx_Level;

/**
 * @brief  GPIO port pin bitmask enumeration (Pins 0 to 15).
 * @note   16-bit one-hot bitmask type where each enumerator represents a single pin position
 *         (bits [15:0]) and can be bitwise-ORed to address multiple pins simultaneously
 *         in IDR, ODR, BSRR, and LCKR operations.
 * @warning Not all ports expose all 16 pins (e.g., GPIOH only exposes PH0 and PH1 on STM32F401).
 *          PA13-PA15 and PB3-PB4 default to JTAG/SWD debug functions after reset.
 */
typedef enum {
    PLAY32_GPIOx_PIN_0   = (1UL << 0),  /**< Pin 0 bitmask (0x0001). */
    PLAY32_GPIOx_PIN_1   = (1UL << 1),  /**< Pin 1 bitmask (0x0002). */
    PLAY32_GPIOx_PIN_2   = (1UL << 2),  /**< Pin 2 bitmask (0x0004). */
    PLAY32_GPIOx_PIN_3   = (1UL << 3),  /**< Pin 3 bitmask (0x0008). */
    PLAY32_GPIOx_PIN_4   = (1UL << 4),  /**< Pin 4 bitmask (0x0010). */
    PLAY32_GPIOx_PIN_5   = (1UL << 5),  /**< Pin 5 bitmask (0x0020). */
    PLAY32_GPIOx_PIN_6   = (1UL << 6),  /**< Pin 6 bitmask (0x0040). */
    PLAY32_GPIOx_PIN_7   = (1UL << 7),  /**< Pin 7 bitmask (0x0080). */
    PLAY32_GPIOx_PIN_8   = (1UL << 8),  /**< Pin 8 bitmask (0x0100). */
    PLAY32_GPIOx_PIN_9   = (1UL << 9),  /**< Pin 9 bitmask (0x0200). */
    PLAY32_GPIOx_PIN_10  = (1UL << 10), /**< Pin 10 bitmask (0x0400). */
    PLAY32_GPIOx_PIN_11  = (1UL << 11), /**< Pin 11 bitmask (0x0800). */
    PLAY32_GPIOx_PIN_12  = (1UL << 12), /**< Pin 12 bitmask (0x1000). */
    PLAY32_GPIOx_PIN_13  = (1UL << 13), /**< Pin 13 bitmask (0x2000). */
    PLAY32_GPIOx_PIN_14  = (1UL << 14), /**< Pin 14 bitmask (0x4000). */
    PLAY32_GPIOx_PIN_15  = (1UL << 15), /**< Pin 15 bitmask (0x8000). */
    PLAY32_GPIOx_PIN_ALL = 0xFFFFUL     /**< All 16 port pins bitmask (0xFFFF). */
} PLAY32_GPIOx_PinList;

/**
 * @brief  GPIO alternate function multiplexer selection (AF0-AF15) enumeration.
 * @note   4-bit selection value written to GPIOx_AFRL (pins 0-7) or GPIOx_AFRH (pins 8-15)
 *         when the corresponding pin is configured in Alternate Function mode (`MODER = 10`).
 * @warning Ensure the pin is configured to Alternate Function mode in `GPIOx_MODER` and
 *          check the STM32F401 datasheet alternate function mapping table for valid pin-to-AF combinations.
 */
typedef enum {
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_0  = 0U,  /**< AF0: System (MCO1, MCO2, JTAG/SWD, RTC_50Hz). */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_1  = 1U,  /**< AF1: TIM1 / TIM2. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_2  = 2U,  /**< AF2: TIM3 / TIM4 / TIM5. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_3  = 3U,  /**< AF3: TIM9 / TIM10 / TIM11. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_4  = 4U,  /**< AF4: I2C1 / I2C2 / I2C3. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_5  = 5U,  /**< AF5: SPI1 / SPI2 / I2S2 / SPI3 / SPI4. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_6  = 6U,  /**< AF6: SPI3 / I2S3. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_7  = 7U,  /**< AF7: USART1 / USART2 / I2S3ext. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_8  = 8U,  /**< AF8: USART6. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_9  = 9U,  /**< AF9: I2C2 / I2C3 (SDA/SCL remaps). */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_10 = 10U, /**< AF10: OTG_FS (USB On-The-Go Full-Speed). */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_11 = 11U, /**< AF11: Reserved on STM32F401. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_12 = 12U, /**< AF12: SDIO. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_13 = 13U, /**< AF13: Reserved on STM32F401. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_14 = 14U, /**< AF14: Reserved on STM32F401. */
    PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_15 = 15U  /**< AF15: EVENTOUT. */
} PLAY32_GPIOx_AlternateFunction;

#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_Common_Types */

/**
 * @defgroup PLAY32_GPIOx_MODER_Types GPIO Port Mode Register (GPIOx_MODER)
 * @brief Bit positions, masks, and pin mode enumeration for GPIOx_MODER (offset 0x00).
 * @{
 */
#pragma region GPIOx_MODER_REGISTER

#pragma region GPIOx_MODER_REGISTER_POSITION
#define PLAY32_GPIOx_MODER_MODER_0_POS     (0U)  /**< Bits [1:0]: Port pin 0 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_1_POS     (2U)  /**< Bits [3:2]: Port pin 1 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_2_POS     (4U)  /**< Bits [5:4]: Port pin 2 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_3_POS     (6U)  /**< Bits [7:6]: Port pin 3 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_4_POS     (8U)  /**< Bits [9:8]: Port pin 4 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_5_POS     (10U) /**< Bits [11:10]: Port pin 5 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_6_POS     (12U) /**< Bits [13:12]: Port pin 6 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_7_POS     (14U) /**< Bits [15:14]: Port pin 7 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_8_POS     (16U) /**< Bits [17:16]: Port pin 8 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_9_POS     (18U) /**< Bits [19:18]: Port pin 9 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_10_POS    (20U) /**< Bits [21:20]: Port pin 10 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_11_POS    (22U) /**< Bits [23:22]: Port pin 11 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_12_POS    (24U) /**< Bits [25:24]: Port pin 12 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_13_POS    (26U) /**< Bits [27:26]: Port pin 13 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_14_POS    (28U) /**< Bits [29:28]: Port pin 14 mode configuration position. */
#define PLAY32_GPIOx_MODER_MODER_15_POS    (30U) /**< Bits [31:30]: Port pin 15 mode configuration position. */
#pragma endregion

#pragma region GPIOx_MODER_REGISTER_MASK
#define PLAY32_GPIOx_MODER_MODER_0_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_0_POS)  /**< Bits [1:0] mask (0x00000003). */
#define PLAY32_GPIOx_MODER_MODER_1_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_1_POS)  /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_GPIOx_MODER_MODER_2_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_2_POS)  /**< Bits [5:4] mask (0x00000030). */
#define PLAY32_GPIOx_MODER_MODER_3_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_3_POS)  /**< Bits [7:6] mask (0x000000C0). */
#define PLAY32_GPIOx_MODER_MODER_4_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_4_POS)  /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_GPIOx_MODER_MODER_5_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_5_POS)  /**< Bits [11:10] mask (0x00000C00). */
#define PLAY32_GPIOx_MODER_MODER_6_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_6_POS)  /**< Bits [13:12] mask (0x00003000). */
#define PLAY32_GPIOx_MODER_MODER_7_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_7_POS)  /**< Bits [15:14] mask (0x0000C000). */
#define PLAY32_GPIOx_MODER_MODER_8_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_8_POS)  /**< Bits [17:16] mask (0x00030000). */
#define PLAY32_GPIOx_MODER_MODER_9_MSK     (3UL << PLAY32_GPIOx_MODER_MODER_9_POS)  /**< Bits [19:18] mask (0x000C0000). */
#define PLAY32_GPIOx_MODER_MODER_10_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_10_POS) /**< Bits [21:20] mask (0x00300000). */
#define PLAY32_GPIOx_MODER_MODER_11_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_11_POS) /**< Bits [23:22] mask (0x00C00000). */
#define PLAY32_GPIOx_MODER_MODER_12_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_12_POS) /**< Bits [25:24] mask (0x03000000). */
#define PLAY32_GPIOx_MODER_MODER_13_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_13_POS) /**< Bits [27:26] mask (0x0C000000). */
#define PLAY32_GPIOx_MODER_MODER_14_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_14_POS) /**< Bits [29:28] mask (0x30000000). */
#define PLAY32_GPIOx_MODER_MODER_15_MSK    (3UL << PLAY32_GPIOx_MODER_MODER_15_POS) /**< Bits [31:30] mask (0xC0000000). */
#pragma endregion

#pragma region GPIOx_MODER_REGISTER_ENUM

/**
 * @brief  GPIO I/O direction and functional mode (MODERy) enumeration.
 * @note   Read/Write 2-bit field (`MODERy[1:0]` in `GPIOx_MODER`, offset 0x00) used to configure
 *         the operating direction or peripheral multiplexing of each port pin.
 * @warning Reset state is `0xA8000000` for `GPIOA` (PA13-PA15 in Alternate Function mode for JTAG/SWD),
 *         0x00000280` for `GPIOB` (PB3-PB4 in Alternate Function mode for JTAG), and `0x00000000`
 *         (Input mode) for all other ports. Modifying debug pins disconnects the debugger.
 * @see    PLAY32_GPIOx_AlternateFunction
 */
typedef enum {
    PLAY32_GPIOx_MODER_MODE_INPUT       = 0U, /**< Input mode (reset state for standard pins). */
    PLAY32_GPIOx_MODER_MODE_OUTPUT      = 1U, /**< General-purpose output mode. */
    PLAY32_GPIOx_MODER_MODE_ALTERNATIVE = 2U, /**< Alternate function mode (routed via GPIOx_AFRL / GPIOx_AFRH). */
    PLAY32_GPIOx_MODER_MODE_ANALOG      = 3U  /**< Analog mode (ADC input or low-power pin isolation). */
} PLAY32_GPIOx_MODER_Mode;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_MODER_Types */

/**
 * @defgroup PLAY32_GPIOx_OTYPER_Types GPIO Port Output Type Register (GPIOx_OTYPER)
 * @brief Bit positions, masks, and output driver type enumeration for GPIOx_OTYPER (offset 0x04).
 * @{
 */
#pragma region GPIOx_OTYPER_REGISTER

#pragma region GPIOx_OTYPER_REGISTER_POSITION
#define PLAY32_GPIOx_OTYPER_OT_0_POS     (0U)  /**< Bit 0: Port pin 0 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_1_POS     (1U)  /**< Bit 1: Port pin 1 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_2_POS     (2U)  /**< Bit 2: Port pin 2 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_3_POS     (3U)  /**< Bit 3: Port pin 3 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_4_POS     (4U)  /**< Bit 4: Port pin 4 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_5_POS     (5U)  /**< Bit 5: Port pin 5 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_6_POS     (6U)  /**< Bit 6: Port pin 6 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_7_POS     (7U)  /**< Bit 7: Port pin 7 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_8_POS     (8U)  /**< Bit 8: Port pin 8 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_9_POS     (9U)  /**< Bit 9: Port pin 9 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_10_POS    (10U) /**< Bit 10: Port pin 10 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_11_POS    (11U) /**< Bit 11: Port pin 11 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_12_POS    (12U) /**< Bit 12: Port pin 12 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_13_POS    (13U) /**< Bit 13: Port pin 13 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_14_POS    (14U) /**< Bit 14: Port pin 14 output type configuration position. */
#define PLAY32_GPIOx_OTYPER_OT_15_POS    (15U) /**< Bit 15: Port pin 15 output type configuration position. */
#pragma endregion

#pragma region GPIOx_OTYPER_REGISTER_MASK
#define PLAY32_GPIOx_OTYPER_OT_0_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_GPIOx_OTYPER_OT_1_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_GPIOx_OTYPER_OT_2_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_GPIOx_OTYPER_OT_3_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_GPIOx_OTYPER_OT_4_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_GPIOx_OTYPER_OT_5_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_GPIOx_OTYPER_OT_6_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_GPIOx_OTYPER_OT_7_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_GPIOx_OTYPER_OT_8_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_GPIOx_OTYPER_OT_9_MSK     (1UL << PLAY32_GPIOx_OTYPER_OT_9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_GPIOx_OTYPER_OT_10_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_GPIOx_OTYPER_OT_11_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_GPIOx_OTYPER_OT_12_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_GPIOx_OTYPER_OT_13_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_GPIOx_OTYPER_OT_14_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_GPIOx_OTYPER_OT_15_MSK    (1UL << PLAY32_GPIOx_OTYPER_OT_15_POS) /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region GPIOx_OTYPER_REGISTER_ENUM

/**
 * @brief  GPIO output driver configuration (OTy) enumeration.
 * @note   Read/Write control bit (`OTy` in `GPIOx_OTYPER`, offset 0x04, bits [15:0]) used to select
 *         push-pull or open-drain output stage when the pin is in Output or Alternate Function mode.
 * @warning Open-drain mode (`PLAY32_GPIOx_OTYPER_TYPE_OPEN_DRAIN`) requires an internal or external
 *          pull-up resistor to drive a logic high level (mandatory for I2C SDA/SCL lines).
 *          Bits [31:16] are reserved and must be kept at reset value (0).
 * @see    PLAY32_GPIOx_MODER_Mode
 */
typedef enum {
    PLAY32_GPIOx_OTYPER_TYPE_PUSH_PULL  = 0U, /**< Output push-pull (reset state; drives both high and low actively). */
    PLAY32_GPIOx_OTYPER_TYPE_OPEN_DRAIN = 1U  /**< Output open-drain (pulls low actively, high-impedance when set to 1). */
} PLAY32_GPIOx_OTYPER_OutputType;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_OTYPER_Types */

/**
 * @defgroup PLAY32_GPIOx_PUPDR_Types GPIO Port Pull-Up/Pull-Down Register (GPIOx_PUPDR)
 * @brief Bit positions, masks, and internal pull resistor enumeration for GPIOx_PUPDR (offset 0x0C).
 * @{
 */
#pragma region GPIOx_PUPDR_REGISTER

#pragma region GPIOx_PUPDR_REGISTER_POSITION
#define PLAY32_GPIOx_PUPDR_PUPDR_0_POS     (0U)  /**< Bits [1:0]: Port pin 0 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_1_POS     (2U)  /**< Bits [3:2]: Port pin 1 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_2_POS     (4U)  /**< Bits [5:4]: Port pin 2 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_3_POS     (6U)  /**< Bits [7:6]: Port pin 3 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_4_POS     (8U)  /**< Bits [9:8]: Port pin 4 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_5_POS     (10U) /**< Bits [11:10]: Port pin 5 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_6_POS     (12U) /**< Bits [13:12]: Port pin 6 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_7_POS     (14U) /**< Bits [15:14]: Port pin 7 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_8_POS     (16U) /**< Bits [17:16]: Port pin 8 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_9_POS     (18U) /**< Bits [19:18]: Port pin 9 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_10_POS    (20U) /**< Bits [21:20]: Port pin 10 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_11_POS    (22U) /**< Bits [23:22]: Port pin 11 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_12_POS    (24U) /**< Bits [25:24]: Port pin 12 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_13_POS    (26U) /**< Bits [27:26]: Port pin 13 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_14_POS    (28U) /**< Bits [29:28]: Port pin 14 pull-up/pull-down configuration position. */
#define PLAY32_GPIOx_PUPDR_PUPDR_15_POS    (30U) /**< Bits [31:30]: Port pin 15 pull-up/pull-down configuration position. */
#pragma endregion

#pragma region GPIOx_PUPDR_REGISTER_MASK
#define PLAY32_GPIOx_PUPDR_PUPDR_0_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_0_POS)  /**< Bits [1:0] mask (0x00000003). */
#define PLAY32_GPIOx_PUPDR_PUPDR_1_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_1_POS)  /**< Bits [3:2] mask (0x0000000C). */
#define PLAY32_GPIOx_PUPDR_PUPDR_2_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_2_POS)  /**< Bits [5:4] mask (0x00000030). */
#define PLAY32_GPIOx_PUPDR_PUPDR_3_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_3_POS)  /**< Bits [7:6] mask (0x000000C0). */
#define PLAY32_GPIOx_PUPDR_PUPDR_4_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_4_POS)  /**< Bits [9:8] mask (0x00000300). */
#define PLAY32_GPIOx_PUPDR_PUPDR_5_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_5_POS)  /**< Bits [11:10] mask (0x00000C00). */
#define PLAY32_GPIOx_PUPDR_PUPDR_6_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_6_POS)  /**< Bits [13:12] mask (0x00003000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_7_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_7_POS)  /**< Bits [15:14] mask (0x0000C000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_8_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_8_POS)  /**< Bits [17:16] mask (0x00030000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_9_MSK     (3UL << PLAY32_GPIOx_PUPDR_PUPDR_9_POS)  /**< Bits [19:18] mask (0x000C0000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_10_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_10_POS) /**< Bits [21:20] mask (0x00300000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_11_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_11_POS) /**< Bits [23:22] mask (0x00C00000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_12_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_12_POS) /**< Bits [25:24] mask (0x03000000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_13_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_13_POS) /**< Bits [27:26] mask (0x0C000000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_14_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_14_POS) /**< Bits [29:28] mask (0x30000000). */
#define PLAY32_GPIOx_PUPDR_PUPDR_15_MSK    (3UL << PLAY32_GPIOx_PUPDR_PUPDR_15_POS) /**< Bits [31:30] mask (0xC0000000). */
#pragma endregion

#pragma region GPIOx_PUPDR_REGISTER_ENUM

/**
 * @brief  GPIO internal pull-up / pull-down resistor (PUPDRy) enumeration.
 * @note   Read/Write 2-bit field (`PUPDRy[1:0]` in `GPIOx_PUPDR`, offset 0x0C) used to enable
 *         or disable weak internal pull-up or pull-down resistors on each port pin.
 * @warning Value `3U` (`0b11`) is reserved by hardware and must not be written.
 *          Reset state is `0x64000000` for `GPIOA` (PA15 pull-up, PA14 pull-down, PA13 pull-up),
 *          `0x00000100` for `GPIOB` (PB4 pull-up), and `0x00000000` for all other ports.
 *          When a pin is configured in Analog mode (`MODER = 11`), internal pull resistors
 *          are automatically disabled by hardware.
 * @see    PLAY32_GPIOx_MODER_Mode
 */
typedef enum {
    PLAY32_GPIOx_PUPDR_PULL_UP_PULL_DOWN_NO_PULL_UP_PULL_DOWN = 0U, /**< No pull-up, no pull-down (floating input / standard output). */
    PLAY32_GPIOx_PUPDR_PULL_UP_PULL_DOWN_PULL_UP              = 1U, /**< Weak internal pull-up resistor enabled. */
    PLAY32_GPIOx_PUPDR_PULL_UP_PULL_DOWN_PULL_DOWN            = 2U  /**< Weak internal pull-down resistor enabled. */
} PLAY32_GPIOx_PUPDR_PullUpPullDown;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_PUPDR_Types */


/**
 * @defgroup PLAY32_GPIOx_IDR_Types GPIO Port Input Data Register (GPIOx_IDR)
 * @brief Bit positions, masks, and input state type for GPIOx_IDR (offset 0x10).
 * @{
 */
#pragma region GPIOx_IDR_REGISTER

#pragma region GPIOx_IDR_REGISTER_POSITION
#define PLAY32_GPIOx_IDR_IDR_0_POS     (0U)  /**< Bit 0: Port pin 0 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_1_POS     (1U)  /**< Bit 1: Port pin 1 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_2_POS     (2U)  /**< Bit 2: Port pin 2 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_3_POS     (3U)  /**< Bit 3: Port pin 3 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_4_POS     (4U)  /**< Bit 4: Port pin 4 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_5_POS     (5U)  /**< Bit 5: Port pin 5 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_6_POS     (6U)  /**< Bit 6: Port pin 6 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_7_POS     (7U)  /**< Bit 7: Port pin 7 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_8_POS     (8U)  /**< Bit 8: Port pin 8 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_9_POS     (9U)  /**< Bit 9: Port pin 9 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_10_POS    (10U) /**< Bit 10: Port pin 10 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_11_POS    (11U) /**< Bit 11: Port pin 11 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_12_POS    (12U) /**< Bit 12: Port pin 12 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_13_POS    (13U) /**< Bit 13: Port pin 13 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_14_POS    (14U) /**< Bit 14: Port pin 14 input data bit position. */
#define PLAY32_GPIOx_IDR_IDR_15_POS    (15U) /**< Bit 15: Port pin 15 input data bit position. */
#pragma endregion

#pragma region GPIOx_IDR_REGISTER_MASK
#define PLAY32_GPIOx_IDR_IDR_0_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_GPIOx_IDR_IDR_1_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_GPIOx_IDR_IDR_2_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_GPIOx_IDR_IDR_3_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_GPIOx_IDR_IDR_4_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_GPIOx_IDR_IDR_5_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_GPIOx_IDR_IDR_6_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_GPIOx_IDR_IDR_7_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_GPIOx_IDR_IDR_8_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_GPIOx_IDR_IDR_9_MSK     (1UL << PLAY32_GPIOx_IDR_IDR_9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_GPIOx_IDR_IDR_10_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_GPIOx_IDR_IDR_11_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_GPIOx_IDR_IDR_12_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_GPIOx_IDR_IDR_13_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_GPIOx_IDR_IDR_14_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_GPIOx_IDR_IDR_15_MSK    (1UL << PLAY32_GPIOx_IDR_IDR_15_POS) /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region GPIOx_IDR_REGISTER_ENUM

/**
 * @brief  GPIO port input data bit (IDRy) state type.
 * @note   Read-only status bit (`IDRy` in `GPIOx_IDR`, offset 0x10, bits [15:0]) sampled at
 *         every AHB1 clock cycle to reflect the logic state applied to the corresponding I/O pin.
 * @warning This register is read-only and can only be accessed in word (32-bit) mode;
 *          bits [31:16] are reserved and always read as 0. When a pin is configured in Analog
 *          mode (`MODER = 11`), the input Schmitt trigger is disabled and `IDRy` always reads 0.
 * @see    PLAY32_GPIOx_LEVEL
 * @see    PLAY32_GPIOx_MODER_Mode
 */
typedef PLAY32_GPIOx_Level PLAY32_GPIOx_IDR_InputDirection;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_IDR_Types */


/**
 * @defgroup PLAY32_GPIOx_ODR_Types GPIO Port Output Data Register (GPIOx_ODR)
 * @brief Bit positions, masks, and output data state type for GPIOx_ODR (offset 0x14).
 * @{
 */
#pragma region GPIOx_ODR_REGISTER

#pragma region GPIOx_ODR_REGISTER_POSITION
#define PLAY32_GPIOx_ODR_ODR_0_POS     (0U)  /**< Bit 0: Port pin 0 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_1_POS     (1U)  /**< Bit 1: Port pin 1 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_2_POS     (2U)  /**< Bit 2: Port pin 2 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_3_POS     (3U)  /**< Bit 3: Port pin 3 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_4_POS     (4U)  /**< Bit 4: Port pin 4 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_5_POS     (5U)  /**< Bit 5: Port pin 5 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_6_POS     (6U)  /**< Bit 6: Port pin 6 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_7_POS     (7U)  /**< Bit 7: Port pin 7 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_8_POS     (8U)  /**< Bit 8: Port pin 8 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_9_POS     (9U)  /**< Bit 9: Port pin 9 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_10_POS    (10U) /**< Bit 10: Port pin 10 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_11_POS    (11U) /**< Bit 11: Port pin 11 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_12_POS    (12U) /**< Bit 12: Port pin 12 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_13_POS    (13U) /**< Bit 13: Port pin 13 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_14_POS    (14U) /**< Bit 14: Port pin 14 output data bit position. */
#define PLAY32_GPIOx_ODR_ODR_15_POS    (15U) /**< Bit 15: Port pin 15 output data bit position. */
#pragma endregion

#pragma region GPIOx_ODR_REGISTER_MASK
#define PLAY32_GPIOx_ODR_ODR_0_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_GPIOx_ODR_ODR_1_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_GPIOx_ODR_ODR_2_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_GPIOx_ODR_ODR_3_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_GPIOx_ODR_ODR_4_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_GPIOx_ODR_ODR_5_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_GPIOx_ODR_ODR_6_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_GPIOx_ODR_ODR_7_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_GPIOx_ODR_ODR_8_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_GPIOx_ODR_ODR_9_MSK     (1UL << PLAY32_GPIOx_ODR_ODR_9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_GPIOx_ODR_ODR_10_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_GPIOx_ODR_ODR_11_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_GPIOx_ODR_ODR_12_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_GPIOx_ODR_ODR_13_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_GPIOx_ODR_ODR_14_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_GPIOx_ODR_ODR_15_MSK    (1UL << PLAY32_GPIOx_ODR_ODR_15_POS) /**< Bit 15 mask (0x00008000). */
#pragma endregion

#pragma region GPIOx_ODR_REGISTER_ENUM

/**
 * @brief  GPIO port output data bit (ODRy) state type.
 * @note   Read/Write control bit (`ODRy` in `GPIOx_ODR`, offset 0x14, bits [15:0]) used to read back
 *         or set the output latch state of a port pin configured in General-Purpose Output mode.
 * @warning Performing read-modify-write operations directly on `GPIOx_ODR` is not atomic and can
 *          cause race conditions if an ISR modifies another pin on the same port. Prefer writing
 *          to `GPIOx_BSRR` for atomic single-bit set/reset operations. Bits [31:16] are reserved.
 * @see    PLAY32_GPIOx_Level
 * @see    PLAY32_GPIOx_TypeDef::BSRR
 */
typedef PLAY32_GPIOx_Level PLAY32_GPIOx_ODR_OutputDirection;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_ODR_Types */

/**
 * @defgroup PLAY32_GPIOx_BSRR_Types GPIO Port Bit Set/Reset Register (GPIOx_BSRR)
 * @brief Bit positions, masks, and atomic bit set/reset types for GPIOx_BSRR (offset 0x18).
 * @{
 */
#pragma region GPIOx_BSRR_REGISTER

#pragma region GPIOx_BSRR_REGISTER_POSITION
/* Atomic Bit Set positions (bits [15:0]) */
#define PLAY32_GPIOx_BSRR_BS_0_POS     (0U)  /**< Bit 0: Port pin 0 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_1_POS     (1U)  /**< Bit 1: Port pin 1 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_2_POS     (2U)  /**< Bit 2: Port pin 2 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_3_POS     (3U)  /**< Bit 3: Port pin 3 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_4_POS     (4U)  /**< Bit 4: Port pin 4 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_5_POS     (5U)  /**< Bit 5: Port pin 5 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_6_POS     (6U)  /**< Bit 6: Port pin 6 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_7_POS     (7U)  /**< Bit 7: Port pin 7 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_8_POS     (8U)  /**< Bit 8: Port pin 8 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_9_POS     (9U)  /**< Bit 9: Port pin 9 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_10_POS    (10U) /**< Bit 10: Port pin 10 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_11_POS    (11U) /**< Bit 11: Port pin 11 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_12_POS    (12U) /**< Bit 12: Port pin 12 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_13_POS    (13U) /**< Bit 13: Port pin 13 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_14_POS    (14U) /**< Bit 14: Port pin 14 atomic set bit position. */
#define PLAY32_GPIOx_BSRR_BS_15_POS    (15U) /**< Bit 15: Port pin 15 atomic set bit position. */

/* Atomic Bit Reset positions (bits [31:16]) */
#define PLAY32_GPIOx_BSRR_BR_0_POS     (16U) /**< Bit 16: Port pin 0 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_1_POS     (17U) /**< Bit 17: Port pin 1 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_2_POS     (18U) /**< Bit 18: Port pin 2 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_3_POS     (19U) /**< Bit 19: Port pin 3 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_4_POS     (20U) /**< Bit 20: Port pin 4 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_5_POS     (21U) /**< Bit 21: Port pin 5 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_6_POS     (22U) /**< Bit 22: Port pin 6 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_7_POS     (23U) /**< Bit 23: Port pin 7 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_8_POS     (24U) /**< Bit 24: Port pin 8 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_9_POS     (25U) /**< Bit 25: Port pin 9 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_10_POS    (26U) /**< Bit 26: Port pin 10 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_11_POS    (27U) /**< Bit 27: Port pin 11 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_12_POS    (28U) /**< Bit 28: Port pin 12 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_13_POS    (29U) /**< Bit 29: Port pin 13 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_14_POS    (30U) /**< Bit 30: Port pin 14 atomic reset bit position. */
#define PLAY32_GPIOx_BSRR_BR_15_POS    (31U) /**< Bit 31: Port pin 15 atomic reset bit position. */
#pragma endregion

#pragma region GPIOx_BSRR_REGISTER_MASK
#define PLAY32_GPIOx_BSRR_BS_0_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_0_POS)  /**< Bit 0 mask (0x00000001). */
#define PLAY32_GPIOx_BSRR_BS_1_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_1_POS)  /**< Bit 1 mask (0x00000002). */
#define PLAY32_GPIOx_BSRR_BS_2_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_2_POS)  /**< Bit 2 mask (0x00000004). */
#define PLAY32_GPIOx_BSRR_BS_3_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_3_POS)  /**< Bit 3 mask (0x00000008). */
#define PLAY32_GPIOx_BSRR_BS_4_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_4_POS)  /**< Bit 4 mask (0x00000010). */
#define PLAY32_GPIOx_BSRR_BS_5_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_5_POS)  /**< Bit 5 mask (0x00000020). */
#define PLAY32_GPIOx_BSRR_BS_6_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_6_POS)  /**< Bit 6 mask (0x00000040). */
#define PLAY32_GPIOx_BSRR_BS_7_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_7_POS)  /**< Bit 7 mask (0x00000080). */
#define PLAY32_GPIOx_BSRR_BS_8_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_8_POS)  /**< Bit 8 mask (0x00000100). */
#define PLAY32_GPIOx_BSRR_BS_9_MSK     (1UL << PLAY32_GPIOx_BSRR_BS_9_POS)  /**< Bit 9 mask (0x00000200). */
#define PLAY32_GPIOx_BSRR_BS_10_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_10_POS) /**< Bit 10 mask (0x00000400). */
#define PLAY32_GPIOx_BSRR_BS_11_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_11_POS) /**< Bit 11 mask (0x00000800). */
#define PLAY32_GPIOx_BSRR_BS_12_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_12_POS) /**< Bit 12 mask (0x00001000). */
#define PLAY32_GPIOx_BSRR_BS_13_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_13_POS) /**< Bit 13 mask (0x00002000). */
#define PLAY32_GPIOx_BSRR_BS_14_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_14_POS) /**< Bit 14 mask (0x00004000). */
#define PLAY32_GPIOx_BSRR_BS_15_MSK    (1UL << PLAY32_GPIOx_BSRR_BS_15_POS) /**< Bit 15 mask (0x00008000). */
#define PLAY32_GPIOx_BSRR_BR_0_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_0_POS)  /**< Bit 16 mask (0x00010000). */
#define PLAY32_GPIOx_BSRR_BR_1_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_1_POS)  /**< Bit 17 mask (0x00020000). */
#define PLAY32_GPIOx_BSRR_BR_2_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_2_POS)  /**< Bit 18 mask (0x00040000). */
#define PLAY32_GPIOx_BSRR_BR_3_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_3_POS)  /**< Bit 19 mask (0x00080000). */
#define PLAY32_GPIOx_BSRR_BR_4_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_4_POS)  /**< Bit 20 mask (0x00100000). */
#define PLAY32_GPIOx_BSRR_BR_5_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_5_POS)  /**< Bit 21 mask (0x00200000). */
#define PLAY32_GPIOx_BSRR_BR_6_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_6_POS)  /**< Bit 22 mask (0x00400000). */
#define PLAY32_GPIOx_BSRR_BR_7_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_7_POS)  /**< Bit 23 mask (0x00800000). */
#define PLAY32_GPIOx_BSRR_BR_8_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_8_POS)  /**< Bit 24 mask (0x01000000). */
#define PLAY32_GPIOx_BSRR_BR_9_MSK     (1UL << PLAY32_GPIOx_BSRR_BR_9_POS)  /**< Bit 25 mask (0x02000000). */
#define PLAY32_GPIOx_BSRR_BR_10_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_10_POS) /**< Bit 26 mask (0x04000000). */
#define PLAY32_GPIOx_BSRR_BR_11_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_11_POS) /**< Bit 27 mask (0x08000000). */
#define PLAY32_GPIOx_BSRR_BR_12_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_12_POS) /**< Bit 28 mask (0x10000000). */
#define PLAY32_GPIOx_BSRR_BR_13_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_13_POS) /**< Bit 29 mask (0x20000000). */
#define PLAY32_GPIOx_BSRR_BR_14_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_14_POS) /**< Bit 30 mask (0x40000000). */
#define PLAY32_GPIOx_BSRR_BR_15_MSK    (1UL << PLAY32_GPIOx_BSRR_BR_15_POS) /**< Bit 31 mask (0x80000000). */
#pragma endregion

#pragma region GPIOx_BSRR_REGISTER_ENUM

/**
 * @brief  GPIO port atomic bit set (`BSy`) control type.
 * @note   Write-only control bit (`BSy` in `GPIOx_BSRR`, offset 0x18, bits [15:0]).
 *         Writing @ref PLAY32_GPIOx_LEVEL_HIGH (1) atomically sets the corresponding `ODRy` bit
 *         to 1 in a single bus write; writing 0 has no effect.
 * @warning This register is write-only; reading `GPIOx_BSRR` always returns `0x00000000`.
 *          If both `BSy` and `BRy` are set simultaneously in the same write, `BSy` takes priority.
 * @see    PLAY32_GPIOx_Level
 * @see    PLAY32_GPIOx_BSRR_BitReset
 */
typedef PLAY32_GPIOx_Level PLAY32_GPIOx_BSRR_BitSet;

/**
 * @brief  GPIO port atomic bit reset (`BRy`) control type.
 * @note   Write-only control bit (`BRy` in `GPIOx_BSRR`, offset 0x18, bits [31:16]).
 *         Writing @ref PLAY32_GPIOx_LEVEL_HIGH (1) atomically clears the corresponding `ODRy` bit
 *         to 0 in a single bus write; writing 0 has no effect.
 * @warning This register is write-only; reading `GPIOx_BSRR` always returns `0x00000000`.
 *          If both `BSy` and `BRy` are set simultaneously in the same write, `BSy` takes priority.
 * @see    PLAY32_GPIOx_Level
 * @see    PLAY32_GPIOx_BSRR_BitSet
 */
typedef PLAY32_GPIOx_Level PLAY32_GPIOx_BSRR_BitReset;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_BSRR_Types */

/**
 * @defgroup PLAY32_GPIOx_AFRL_Types GPIO Alternate Function Low Register (GPIOx_AFRL)
 * @brief Bit positions, masks, and alternate function type for GPIOx_AFRL (offset 0x20, pins 0-7).
 * @{
 */
#pragma region GPIOx_AFRL_REGISTER

#pragma region GPIOx_AFRL_REGISTER_POSITION
#define PLAY32_GPIOx_AFRL_AFRL_0_POS    (0U)  /**< Bits [3:0]: Port pin 0 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_1_POS    (4U)  /**< Bits [7:4]: Port pin 1 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_2_POS    (8U)  /**< Bits [11:8]: Port pin 2 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_3_POS    (12U) /**< Bits [15:12]: Port pin 3 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_4_POS    (16U) /**< Bits [19:16]: Port pin 4 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_5_POS    (20U) /**< Bits [23:20]: Port pin 5 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_6_POS    (24U) /**< Bits [27:24]: Port pin 6 alternate function selection position. */
#define PLAY32_GPIOx_AFRL_AFRL_7_POS    (28U) /**< Bits [31:28]: Port pin 7 alternate function selection position. */
#pragma endregion

#pragma region GPIOx_AFRL_REGISTER_MASK
#define PLAY32_GPIOx_AFRL_AFRL_0_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_0_POS) /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_GPIOx_AFRL_AFRL_1_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_1_POS) /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_GPIOx_AFRL_AFRL_2_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_2_POS) /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_GPIOx_AFRL_AFRL_3_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_3_POS) /**< Bits [15:12] mask (0x0000F000). */
#define PLAY32_GPIOx_AFRL_AFRL_4_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_4_POS) /**< Bits [19:16] mask (0x000F0000). */
#define PLAY32_GPIOx_AFRL_AFRL_5_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_5_POS) /**< Bits [23:20] mask (0x00F00000). */
#define PLAY32_GPIOx_AFRL_AFRL_6_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_6_POS) /**< Bits [27:24] mask (0x0F000000). */
#define PLAY32_GPIOx_AFRL_AFRL_7_MSK    (15UL << PLAY32_GPIOx_AFRL_AFRL_7_POS) /**< Bits [31:28] mask (0xF0000000). */
#pragma endregion

#pragma region GPIOx_AFRL_REGISTER_ENUM

/**
 * @brief  GPIO alternate function low register (`AFRLy`) selection type.
 * @note   Read/Write 4-bit field (`AFRLy[3:0]` in `GPIOx_AFRL`, offset 0x20, covering pins 0 to 7)
 *         used to route one of 16 peripheral alternate functions (AF0-AF15) to the pin.
 * @warning Takes effect only when the corresponding pin is set to Alternate Function mode
 *          (@ref PLAY32_GPIOx_MODER_MODE_ALTERNATIVE) in `GPIOx_MODER`.
 * @see    PLAY32_GPIOx_AlternateFunction
 * @see    PLAY32_GPIOx_MODER_Mode
 */
typedef PLAY32_GPIOx_AlternateFunction PLAY32_GPIOx_AFRL_AlternateFunction;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_AFRL_Types */

/**
 * @defgroup PLAY32_GPIOx_AFRH_Types GPIO Alternate Function High Register (GPIOx_AFRH)
 * @brief Bit positions, masks, and alternate function type for GPIOx_AFRH (offset 0x24, pins 8-15).
 * @{
 */
#pragma region GPIOx_AFRH_REGISTER

#pragma region GPIOx_AFRH_REGISTER_POSITION
#define PLAY32_GPIOx_AFRH_AFRH_8_POS     (0U)  /**< Bits [3:0]: Port pin 8 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_9_POS     (4U)  /**< Bits [7:4]: Port pin 9 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_10_POS    (8U)  /**< Bits [11:8]: Port pin 10 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_11_POS    (12U) /**< Bits [15:12]: Port pin 11 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_12_POS    (16U) /**< Bits [19:16]: Port pin 12 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_13_POS    (20U) /**< Bits [23:20]: Port pin 13 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_14_POS    (24U) /**< Bits [27:24]: Port pin 14 alternate function selection position. */
#define PLAY32_GPIOx_AFRH_AFRH_15_POS    (28U) /**< Bits [31:28]: Port pin 15 alternate function selection position. */
#pragma endregion

#pragma region GPIOx_AFRH_REGISTER_MASK
#define PLAY32_GPIOx_AFRH_AFRH_8_MSK     (15UL << PLAY32_GPIOx_AFRH_AFRH_8_POS)  /**< Bits [3:0] mask (0x0000000F). */
#define PLAY32_GPIOx_AFRH_AFRH_9_MSK     (15UL << PLAY32_GPIOx_AFRH_AFRH_9_POS)  /**< Bits [7:4] mask (0x000000F0). */
#define PLAY32_GPIOx_AFRH_AFRH_10_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_10_POS) /**< Bits [11:8] mask (0x00000F00). */
#define PLAY32_GPIOx_AFRH_AFRH_11_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_11_POS) /**< Bits [15:12] mask (0x0000F000). */
#define PLAY32_GPIOx_AFRH_AFRH_12_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_12_POS) /**< Bits [19:16] mask (0x000F0000). */
#define PLAY32_GPIOx_AFRH_AFRH_13_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_13_POS) /**< Bits [23:20] mask (0x00F00000). */
#define PLAY32_GPIOx_AFRH_AFRH_14_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_14_POS) /**< Bits [27:24] mask (0x0F000000). */
#define PLAY32_GPIOx_AFRH_AFRH_15_MSK    (15UL << PLAY32_GPIOx_AFRH_AFRH_15_POS) /**< Bits [31:28] mask (0xF0000000). */
#pragma endregion

#pragma region GPIOx_AFRH_REGISTER_ENUM

/**
 * @brief  GPIO alternate function high register (`AFRHy`) selection type.
 * @note   Read/Write 4-bit field (`AFRHy[3:0]` in `GPIOx_AFRH`, offset 0x24, covering pins 8 to 15)
 *         used to route one of 16 peripheral alternate functions (AF0-AF15) to the pin.
 * @warning Takes effect only when the corresponding pin is set to Alternate Function mode
 *          (@ref PLAY32_GPIOx_MODER_MODE_ALTERNATIVE) in `GPIOx_MODER`. Pins PA13-PA15 default
 *          to AF0 (JTAG/SWD) after reset.
 * @see    PLAY32_GPIOx_AlternateFunction
 * @see    PLAY32_GPIOx_MODER_Mode
 */
typedef PLAY32_GPIOx_AlternateFunction PLAY32_GPIOx_AFRH_AlternateFunction;

#pragma endregion
#pragma endregion
/** @} */ /* End of PLAY32_GPIOx_AFRH_Types */

/** @} */ /* End of PLAY32_GPIOx */

#endif /* PLAY32_GPIOx_TYPES_H */

