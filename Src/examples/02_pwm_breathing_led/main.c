/**
 * @file    main.c
 * @example 02_pwm_breathing_led/main.c
 * @author  Eugene Litvin
 * @brief   PWM breathing LED example using TIM2_CH1 (PA0) and TIM3 polling delay.
 *
 * @details Demonstrates:
 *          - Routing TIM2 Channel 1 output to pin PA0 via Alternate Function AF1.
 *          - Configuring TIM2 in PWM Mode 1 at 1 kHz (1000 duty-cycle steps) assuming 16 MHz SYSCLK.
 *          - Enabling Auto-Reload Preload (ARPE) and Output Compare Preload (OC1PE) for glitch-free duty updates.
 *          - Smoothly ramping LED brightness up and down using TIM3 millisecond delays.
 */

#include <stdint.h>
#include "include/rcc.h"
#include "include/gpiox.h"
#include "include/timx.h"

/* System clock & PWM timing configuration (16 MHz default HSI clock) */
#define SYSCLK_HZ              (16000000UL)

/* TIM2: 1 MHz timer tick, 1000 ticks period -> 1 kHz PWM frequency */
#define TIM2_TICK_HZ           (1000000UL)
#define TIM2_PRESCALER_VAL     ((SYSCLK_HZ / TIM2_TICK_HZ) - 1UL)
#define PWM_PERIOD_TICKS       (1000UL)
#define PWM_MAX_DUTY           (PWM_PERIOD_TICKS)

/* TIM3: 1 kHz timer tick -> 1 ms resolution for smooth brightness steps */
#define TIM3_TICK_HZ           (1000UL)
#define TIM3_PRESCALER_VAL     ((SYSCLK_HZ / TIM3_TICK_HZ) - 1UL)
#define RAMP_STEP_VALUE        (10UL)
#define RAMP_STEP_DELAY_MS     (10UL)

/**
 * @brief  Blocking millisecond delay using TIM3 update event polling.
 * @param  ms  Delay duration in milliseconds (0 returns immediately).
 */
static void delay_ms(uint32_t ms) {
    if (ms == 0UL) {
        return;
    }

    play32_timx_set_counter(PLAY32_TIM3, 0UL);
    play32_timx_set_auto_reload_register(PLAY32_TIM3, ms);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM3);
    play32_timx_set_counter_enable(PLAY32_TIM3, PLAY32_TIMx_SWITCH_ENABLED);

    while (play32_timx_get_update_interrupt_flag(PLAY32_TIM3) != PLAY32_TIMx_FLAG_SET) {
        /* Wait for TIM3 update event */
    }

    play32_timx_set_counter_enable(PLAY32_TIM3, PLAY32_TIMx_SWITCH_DISABLED);
}

/**
 * @brief  Initializes PA0 (TIM2_CH1 AF1), TIM2 PWM output, and TIM3 delay timer.
 */
static void hardware_init(void) {
    /* 1. Enable peripheral clocks for GPIOA, TIM2, and TIM3 + bus sync read-back */
    play32_rcc_set_gpio_a_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_gpio_a_enable();

    play32_rcc_set_timer_2_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_timer_2_enable();

    play32_rcc_set_timer_3_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_timer_3_enable();

    /* 2. Configure PA0 as Alternate Function AF1 (TIM2_CH1) */
    play32_gpiox_set_mode0(PLAY32_GPIOA, PLAY32_GPIOx_MODER_MODE_ALTERNATIVE);
    play32_gpiox_set_alternate_function0(PLAY32_GPIOA, PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_1);

    /* 3. Configure TIM2 for 1 kHz PWM Mode 1 on Channel 1 */
    play32_timx_set_prescaler(PLAY32_TIM2, TIM2_PRESCALER_VAL);
    play32_timx_set_auto_reload_register(PLAY32_TIM2, PWM_PERIOD_TICKS - 1UL);
    play32_timx_set_capture_compare_1_reister(PLAY32_TIM2, 0UL);

    play32_timx_set_capture_compare_1_selection(PLAY32_TIM2, PLAY32_TIMx_CCMR1_CAPTURE_COMPARE_1_SELECTION_CC1_AS_OUTPUT);
    play32_timx_set_output_compare_1_mode(PLAY32_TIM2, PLAY32_TIMx_CCMR1_OUTPUT_COMPARE_1_MODE_PWM_1);
    play32_timx_set_output_compare_1_preload_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);
    play32_timx_set_auto_reload_preload_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);

    /* Enable Channel 1 output with active-high polarity */
    play32_timx_set_capture_compare_1_polarity(PLAY32_TIM2, PLAY32_TIMx_CCER_CAPTURE_COMPARE_1_POLARITY_ACTIVE_HIGH);
    play32_timx_set_capture_compare_1_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);

    /* Load shadow registers and start TIM2 PWM generation */
    play32_timx_trigger_update_generation(PLAY32_TIM2);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM2);
    play32_timx_set_counter_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);

    /* 4. Configure TIM3 prescaler for 1 kHz (1 ms) delay ticks */
    play32_timx_set_prescaler(PLAY32_TIM3, TIM3_PRESCALER_VAL);
    play32_timx_trigger_update_generation(PLAY32_TIM3);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM3);
}

[[noreturn]] int main(void) {
    hardware_init();

    uint32_t duty = 0UL;
    int32_t step = (int32_t)RAMP_STEP_VALUE;

    for (;;) {
        play32_timx_set_capture_compare_1_reister(PLAY32_TIM2, duty);
        delay_ms(RAMP_STEP_DELAY_MS);

        if (duty >= PWM_MAX_DUTY) {
            step = -(int32_t)RAMP_STEP_VALUE;
        } else if (duty == 0UL) {
            step = (int32_t)RAMP_STEP_VALUE;
        }

        duty = (uint32_t)((int32_t)duty + step);
    }
}
