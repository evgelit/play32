/**
 * @file    main.c
 * @example 03_usart_tx/main.c
 * @author  Eugene Litvin
 * @brief   USART2 periodic string transmission example over PA2/PA3 using 25 MHz HSE clock.
 *
 * @details Demonstrates:
 *          - Switching the system clock (`SYSCLK`) from internal HSI to the external 25 MHz HSE crystal.
 *          - Routing `USART2` (`AF7`) to `PA2` (`TX`) and `PA3` (`RX` with internal pull-up).
 *          - Computing the `USART_BRR` divider directly from clock and baud-rate constants at compile time.
 *          - Transmitting a string via `TXE` / `TC` status flag polling with `TIM3` 1-second delays.
 */

#include <stdint.h>
#include <stddef.h>
#include "include/rcc.h"
#include "include/gpiox.h"
#include "include/timx.h"
#include "include/usart.h"

/* External 25 MHz HSE crystal frequency */
#define SYSCLK_HZ              (25000000UL)

/* USART2 baud rate & compile-time BRR calculation (16x oversampling: BRR = round(f_PCLK / Baud)) */
#define USART2_BAUD_RATE       (9600UL)
#define USART2_BRR_VAL         ((uint16_t)((SYSCLK_HZ + (USART2_BAUD_RATE / 2UL)) / USART2_BAUD_RATE))

/* TIM3: 1 kHz counter clock -> 1 ms tick resolution */
#define TIM3_TICK_HZ           (1000UL)
#define TIM3_PRESCALER_VAL     ((SYSCLK_HZ / TIM3_TICK_HZ) - 1UL)
#define TX_INTERVAL_MS         (1000UL)

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
 * @brief  Transmits a buffer of bytes over USART2 and waits for frame completion.
 * @param  data  Pointer to the byte buffer to transmit.
 * @param  len   Number of bytes to send.
 */
static void usart2_write(const char *data, size_t len) {
    for (size_t i = 0U; i < len; ++i) {
        while (play32_usart_get_transmit_data_register_empty(PLAY32_USART2) != PLAY32_USART_FLAG_SET) {
            /* Wait until TXE indicates TDR is empty */
        }
        play32_usart_set_data(PLAY32_USART2, (uint8_t)data[i]);
    }

    while (play32_usart_get_transmission_complete(PLAY32_USART2) != PLAY32_USART_FLAG_SET) {
        /* Wait until TC indicates the last frame has shifted out */
    }
}

/**
 * @brief  Switches SYSCLK to 25 MHz HSE and initializes GPIOA, USART2, and TIM3.
 */
static void hardware_init(void) {
    /* 1. Enable external 25 MHz HSE crystal and switch SYSCLK to HSE */
    play32_rcc_set_high_speed_external_clock_enable(PLAY32_RCC_SWITCH_ENABLED);
    while (play32_rcc_get_high_speed_external_clock_ready() != PLAY32_RCC_FLAG_SET) {
        /* Wait for HSE oscillator to stabilize */
    }

    play32_rcc_set_system_clock_switch(PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_HSE);
    while (play32_rcc_get_system_clock_switch_status() != PLAY32_RCC_CFGR_SYSTEM_CLOCK_SWITCH_STATUS_HSE) {
        /* Wait for SYSCLK switch to complete */
    }

    /* 2. Enable peripheral clocks for GPIOA (AHB1), USART2 (APB1), and TIM3 (APB1) */
    play32_rcc_set_gpio_a_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_gpio_a_enable();

    play32_rcc_set_usart_2_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_usart_2_enable();

    play32_rcc_set_timer_3_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_timer_3_enable();

    /* 3. Configure PA2 (TX) and PA3 (RX with internal pull-up) in Alternate Function AF7 */
    play32_gpiox_set_mode2(PLAY32_GPIOA, PLAY32_GPIOx_MODER_MODE_ALTERNATIVE);
    play32_gpiox_set_mode3(PLAY32_GPIOA, PLAY32_GPIOx_MODER_MODE_ALTERNATIVE);
    play32_gpiox_set_pull_up_pull_down3(PLAY32_GPIOA, PLAY32_GPIOx_PUPDR_PULL_UP);
    play32_gpiox_set_alternate_function2(PLAY32_GPIOA, PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_7);
    play32_gpiox_set_alternate_function3(PLAY32_GPIOA, PLAY32_GPIOx_ALTERNATE_FUNCTION_AF_7);

    /* 4. Configure USART2 frame format, compile-time baud rate, and enable TX/RX */
    play32_usart_set_word_length(PLAY32_USART2, PLAY32_USART_CR1_WORD_LENGTH_9_BITS);
    play32_usart_set_stop_bits(PLAY32_USART2, PLAY32_USART_CR2_STOP_BITS_1);
    play32_usart_set_baud_rate_register(PLAY32_USART2, USART2_BRR_VAL);
    play32_usart_set_receiver_enable(PLAY32_USART2, PLAY32_USART_SWITCH_ENABLED);
    play32_usart_set_transmitter_enable(PLAY32_USART2, PLAY32_USART_SWITCH_ENABLED);
    play32_usart_set_usart_enable(PLAY32_USART2, PLAY32_USART_SWITCH_ENABLED);

    /* 5. Configure TIM3 prescaler for 1 kHz (1 ms) delay ticks */
    play32_timx_set_prescaler(PLAY32_TIM3, TIM3_PRESCALER_VAL);
    play32_timx_trigger_update_generation(PLAY32_TIM3);
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM3);
}

[[noreturn]] int main(void) {
    hardware_init();

    static constexpr char msg[] = "Hello, this is STM32 UART test. This string was transmitted via PLAY32 HAL\r\n";
    constexpr size_t msg_len = sizeof(msg) - 1U;

    for (;;) {
        usart2_write(msg, msg_len);
        delay_ms(TX_INTERVAL_MS);
    }
}
