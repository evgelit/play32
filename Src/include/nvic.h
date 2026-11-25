/**
 * @file    nvic.h
 * @author  Eugene Litvin
 * @brief   Cortex-M4 Nested Vectored Interrupt Controller (NVIC) register map,
 *          STM32F401 IRQ vector numbers, and zero-cost inline control API.
 * @version 1.0.0
 * @date    2026-11-25
 *
 * @license This project is open-source, free, and community-driven.
 *          Distributed under the MIT License. See LICENSE for details.
 *          Feel free to use, modify, and distribute for any purpose.
 */

#ifndef PLAY32_NVIC_H
#define PLAY32_NVIC_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup PLAY32_NVIC Nested Vectored Interrupt Controller (NVIC)
 * @brief Cortex-M4 NVIC memory map, STM32F401 peripheral IRQn definitions, and inline helpers.
 * @{
 */

/** @brief Cortex-M4 NVIC base address in System Control Space (0xE000E100). */
#define PLAY32_NVIC_BASE            (0xE000E100UL)

/** @brief Number of implemented priority bits in STM32F401 NVIC (4 bits -> levels 0..15). */
#define PLAY32_NVIC_PRIO_BITS       (4U)

/**
 * @brief  Cortex-M4 NVIC hardware register map structure.
 */
typedef struct {
    volatile uint32_t ISER[8U];       /**< Offset: 0x000 - Interrupt Set Enable Registers. */
    uint32_t          RESERVED0[24U]; /**< Offset: 0x020 - Reserved. */
    volatile uint32_t ICER[8U];       /**< Offset: 0x080 - Interrupt Clear Enable Registers. */
    uint32_t          RESERVED1[24U]; /**< Offset: 0x0A0 - Reserved. */
    volatile uint32_t ISPR[8U];       /**< Offset: 0x100 - Interrupt Set Pending Registers. */
    uint32_t          RESERVED2[24U]; /**< Offset: 0x120 - Reserved. */
    volatile uint32_t ICPR[8U];       /**< Offset: 0x180 - Interrupt Clear Pending Registers. */
    uint32_t          RESERVED3[24U]; /**< Offset: 0x1A0 - Reserved. */
    volatile uint32_t IABR[8U];       /**< Offset: 0x200 - Interrupt Active Bit Registers. */
    uint32_t          RESERVED4[56U]; /**< Offset: 0x220 - Reserved. */
    volatile uint8_t  IPR[240U];      /**< Offset: 0x300 - Interrupt Priority Registers (8-bit wide). */
} PLAY32_NVIC_TypeDef;

/** @brief NVIC peripheral register map pointer (0xE000E100). */
#define PLAY32_NVIC ((PLAY32_NVIC_TypeDef *)PLAY32_NVIC_BASE)

/**
 * @brief  STM32F401 external peripheral interrupt vector numbers (`IRQn`, RM0368 Table 37).
 */
typedef enum {
    PLAY32_IRQ_WWDG               = 0U,  /**< Window Watchdog interrupt. */
    PLAY32_IRQ_PVD                = 1U,  /**< PVD through EXTI Line detection interrupt. */
    PLAY32_IRQ_TAMP_STAMP         = 2U,  /**< Tamper and TimeStamp interrupts through EXTI. */
    PLAY32_IRQ_RTC_WKUP           = 3U,  /**< RTC Wakeup interrupt through EXTI. */
    PLAY32_IRQ_FLASH              = 4U,  /**< FLASH global interrupt. */
    PLAY32_IRQ_RCC                = 5U,  /**< RCC global interrupt. */
    PLAY32_IRQ_EXTI0              = 6U,  /**< EXTI Line0 interrupt. */
    PLAY32_IRQ_EXTI1              = 7U,  /**< EXTI Line1 interrupt. */
    PLAY32_IRQ_EXTI2              = 8U,  /**< EXTI Line2 interrupt. */
    PLAY32_IRQ_EXTI3              = 9U,  /**< EXTI Line3 interrupt. */
    PLAY32_IRQ_EXTI4              = 10U, /**< EXTI Line4 interrupt. */
    PLAY32_IRQ_DMA1_STREAM0       = 11U, /**< DMA1 Stream 0 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM1       = 12U, /**< DMA1 Stream 1 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM2       = 13U, /**< DMA1 Stream 2 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM3       = 14U, /**< DMA1 Stream 3 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM4       = 15U, /**< DMA1 Stream 4 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM5       = 16U, /**< DMA1 Stream 5 global interrupt. */
    PLAY32_IRQ_DMA1_STREAM6       = 17U, /**< DMA1 Stream 6 global interrupt. */
    PLAY32_IRQ_ADC                = 18U, /**< ADC1 global interrupt. */
    PLAY32_IRQ_EXTI9_5            = 23U, /**< External Line[9:5] interrupts. */
    PLAY32_IRQ_TIM1_BRK_TIM9      = 24U, /**< TIM1 Break interrupt and TIM9 global interrupt. */
    PLAY32_IRQ_TIM1_UP_TIM10      = 25U, /**< TIM1 Update interrupt and TIM10 global interrupt. */
    PLAY32_IRQ_TIM1_TRG_COM_TIM11 = 26U, /**< TIM1 Trigger and Commutation interrupts and TIM11 global interrupt. */
    PLAY32_IRQ_TIM1_CC            = 27U, /**< TIM1 Capture Compare interrupt. */
    PLAY32_IRQ_TIM2               = 28U, /**< TIM2 global interrupt. */
    PLAY32_IRQ_TIM3               = 29U, /**< TIM3 global interrupt. */
    PLAY32_IRQ_TIM4               = 30U, /**< TIM4 global interrupt. */
    PLAY32_IRQ_I2C1_EV            = 31U, /**< I2C1 Event interrupt. */
    PLAY32_IRQ_I2C1_ER            = 32U, /**< I2C1 Error interrupt. */
    PLAY32_IRQ_I2C2_EV            = 33U, /**< I2C2 Event interrupt. */
    PLAY32_IRQ_I2C2_ER            = 34U, /**< I2C2 Error interrupt. */
    PLAY32_IRQ_SPI1               = 35U, /**< SPI1 global interrupt. */
    PLAY32_IRQ_SPI2               = 36U, /**< SPI2 global interrupt. */
    PLAY32_IRQ_USART1             = 37U, /**< USART1 global interrupt. */
    PLAY32_IRQ_USART2             = 38U, /**< USART2 global interrupt. */
    PLAY32_IRQ_EXTI15_10          = 40U, /**< External Line[15:10] interrupts. */
    PLAY32_IRQ_RTC_ALARM          = 41U, /**< RTC Alarm (A and B) through EXTI Line interrupt. */
    PLAY32_IRQ_OTG_FS_WKUP        = 42U, /**< USB OTG FS Wakeup through EXTI line interrupt. */
    PLAY32_IRQ_DMA1_STREAM7       = 47U, /**< DMA1 Stream 7 global interrupt. */
    PLAY32_IRQ_SDIO               = 49U, /**< SDIO global interrupt. */
    PLAY32_IRQ_TIM5               = 50U, /**< TIM5 global interrupt. */
    PLAY32_IRQ_SPI3               = 51U, /**< SPI3 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM0       = 56U, /**< DMA2 Stream 0 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM1       = 57U, /**< DMA2 Stream 1 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM2       = 58U, /**< DMA2 Stream 2 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM3       = 59U, /**< DMA2 Stream 3 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM4       = 60U, /**< DMA2 Stream 4 global interrupt. */
    PLAY32_IRQ_OTG_FS             = 67U, /**< USB OTG FS global interrupt. */
    PLAY32_IRQ_DMA2_STREAM5       = 68U, /**< DMA2 Stream 5 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM6       = 69U, /**< DMA2 Stream 6 global interrupt. */
    PLAY32_IRQ_DMA2_STREAM7       = 70U, /**< DMA2 Stream 7 global interrupt. */
    PLAY32_IRQ_USART6             = 71U, /**< USART6 global interrupt. */
    PLAY32_IRQ_I2C3_EV            = 72U, /**< I2C3 Event interrupt. */
    PLAY32_IRQ_I2C3_ER            = 73U, /**< I2C3 Error interrupt. */
    PLAY32_IRQ_FPU                = 81U, /**< FPU global interrupt. */
    PLAY32_IRQ_SPI4               = 84U  /**< SPI4 global interrupt. */
} PLAY32_IRQn;

/**
 * @brief  Enables a peripheral interrupt vector in the NVIC.
 * @param[in] irqn  Interrupt vector number (@see PLAY32_IRQn).
 */
static inline void play32_nvic_enable_irq(const PLAY32_IRQn irqn) {
    PLAY32_NVIC->ISER[(uint32_t)irqn >> 5U] = (1UL << ((uint32_t)irqn & 0x1FU));
}

/**
 * @brief  Disables a peripheral interrupt vector in the NVIC.
 * @param[in] irqn  Interrupt vector number (@see PLAY32_IRQn).
 */
static inline void play32_nvic_disable_irq(const PLAY32_IRQn irqn) {
    PLAY32_NVIC->ICER[(uint32_t)irqn >> 5U] = (1UL << ((uint32_t)irqn & 0x1FU));
}

/**
 * @brief  Sets the priority of an interrupt vector (`0` = highest, `15` = lowest).
 * @param[in] irqn      Interrupt vector number (@see PLAY32_IRQn).
 * @param[in] priority  Priority level (`0..15`).
 */
static inline void play32_nvic_set_priority(const PLAY32_IRQn irqn, const uint8_t priority) {
    PLAY32_NVIC->IPR[(uint32_t)irqn] = (uint8_t)((priority & 0x0FU) << (8U - PLAY32_NVIC_PRIO_BITS));
}

/**
 * @brief  Clears the pending flag of an interrupt vector in the NVIC.
 * @param[in] irqn  Interrupt vector number (@see PLAY32_IRQn).
 */
static inline void play32_nvic_clear_pending_irq(const PLAY32_IRQn irqn) {
    PLAY32_NVIC->ICPR[(uint32_t)irqn >> 5U] = (1UL << ((uint32_t)irqn & 0x1FU));
}

/**
 * @brief  Globally enables maskable interrupts (`CPSIE I`).
 */
static inline void play32_nvic_enable_global_interrupts(void) {
    __asm volatile ("cpsie i" ::: "memory");
}

/**
 * @brief  Globally disables maskable interrupts (`CPSID I`).
 */
static inline void play32_nvic_disable_global_interrupts(void) {
    __asm volatile ("cpsid i" ::: "memory");
}

/** @} */ /* End of PLAY32_NVIC */

#endif /* PLAY32_NVIC_H */
