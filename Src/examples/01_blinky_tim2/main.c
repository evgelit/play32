/**
 * @file    main.c
 * @example 01_blinky_tim2/main.c
 * @author  Eugene Litvin
 * @brief   GPIO chaser / blinky example using RCC, GPIOx, and TIM2 polling delay.
 *
 * @details Demonstrates:
 *          - Enabling peripheral clocks via RCC (`GPIOB` and `TIM2`) with bus read-back delay.
 *          - Configuring pins `PB3`–`PB9` as push-pull outputs.
 *          - Configuring `TIM2` as a 1 kHz (1 ms tick) one-shot timer assuming 16 MHz `SYSCLK`.
 *          - Toggling pins atomically using `play32_gpiox_toggle()`.
 */

#include <stddef.h>
#include "include/rcc.h"
#include "include/gpiox.h"
#include "include/timx.h"

/* System clock & timing configuration (16 MHz default HSI clock) */
#define SYSCLK_HZ           (16000000UL)
#define TIMER_TICK_HZ       (1000UL)
#define TIM2_PRESCALER_VAL  ((SYSCLK_HZ / TIMER_TICK_HZ) - 1UL)
#define STEP_DELAY_MS       (50UL)

/* LED chaser pin sequence on Port B (PB9 down to PB3) */
static const PLAY32_GPIOx_PinList LED_PINS[] = {
    PLAY32_GPIOx_PIN_9,
    PLAY32_GPIOx_PIN_8,
    PLAY32_GPIOx_PIN_7,
    PLAY32_GPIOx_PIN_6,
    PLAY32_GPIOx_PIN_5,
    PLAY32_GPIOx_PIN_4,
    PLAY32_GPIOx_PIN_3,
};

/**
 * @brief  Blocking millisecond delay using TIM2 update event polling.
 * @param  ms  Delay duration in milliseconds (0 returns immediately).
 */
static void delay_ms(uint32_t ms) {
    if (ms == 0UL) {
        return;
    }

    play32_timx_set_counter(PLAY32_TIM2, 0UL);
    play32_timx_set_auto_reload_register(PLAY32_TIM2, ms);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM2);
    play32_timx_set_counter_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);

    while (play32_timx_get_update_interrupt_flag(PLAY32_TIM2) != PLAY32_TIMx_FLAG_SET) {
        /* Wait for TIM2 update event */
    }

    play32_timx_set_counter_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_DISABLED);
}

/**
 * @brief  Initializes GPIOB output pins and configures TIM2 for 1 ms ticks.
 */
static void hardware_init(void) {
    /* 1. Enable AHB1/APB1 peripheral clocks + dummy read for bus synchronization */
    play32_rcc_set_gpio_b_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_gpio_b_enable();

    play32_rcc_set_timer_2_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_timer_2_enable();

    /* 2. Configure PB3-PB9 as general-purpose outputs */
    play32_gpiox_set_mode9(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode8(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode7(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode6(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode5(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode4(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);
    play32_gpiox_set_mode3(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);

    /* 3. Configure TIM2 prescaler for 1 kHz (1 ms) resolution and load shadow registers */
    play32_timx_set_prescaler(PLAY32_TIM2, TIM2_PRESCALER_VAL);
    play32_timx_trigger_update_generation(PLAY32_TIM2);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM2);
}

[[noreturn]] int main(void) {
    hardware_init();
    const size_t pin_count = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
    for (;;) {
        for (size_t i = 0U; i < pin_count; i++) {
            play32_gpiox_toggle(PLAY32_GPIOB, LED_PINS[i]);
            delay_ms(STEP_DELAY_MS);
        }
    }
}
