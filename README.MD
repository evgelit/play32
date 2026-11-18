# Play32 HAL (STM32F401 CCU)

**Play32** is a lightweight, open-source, and completely free Hardware Abstraction Layer (HAL) for the STM32F401 microcontroller.

The project is built for the community with a core focus on **maximum performance (zero-cost abstractions)**, minimal binary footprint, and **strict Compile-time Type Safety** to eliminate register-level bugs before the code even runs.

## Key Features

- **X-Macro Architecture with Hardware-Aware Dispatch:** The entire register-level API is automatically generated from declarative tables with per-field hardware access modes (`SET_RMW`, `SET_DIRECT`, `SET_WO`, `CLEAR_RC_W0`, `RO`)—eliminating unnecessary bus reads and read-modify-write race conditions.
- **Strict Type Safety:** Every bit-field is bound to its own unique `enum` or `typedef`. No more accidental invalid masks or shift offsets.
- **Zero-Cost Abstractions:** Generated functions are defined as `static inline`. The compiler resolves them directly into atomic hardware memory instructions—performance matches pure CMSIS/register-level code.
- **Doxygen-Ready:** Full Doxygen annotations across register maps, bit offsets, masks, enumerations, and X-Macro generated inline accessors.
- **Interactive Structure:** Structured with `#pragma region` directives, ensuring clean, foldable, and human-readable source files inside modern IDEs.
- **Ultimate Freedom:** Distributed under the MIT License—use, modify, and distribute with no restrictions.

## Quick Start

Just include the peripheral header files into your application:

```c
#include "rcc.h"
#include "gpiox.h"
#include "timx.h"

void init_example(void) {
    // 1. Enable GPIOB and TIM2 peripheral clocks (+ dummy read for bus delay)
    play32_rcc_set_gpio_b_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_gpio_b_enable();

    play32_rcc_set_timer_2_enable(PLAY32_RCC_SWITCH_ENABLED);
    (void)play32_rcc_get_timer_2_enable();

    // 2. Configure PB3 as push-pull output
    play32_gpiox_set_mode3(PLAY32_GPIOB, PLAY32_GPIOx_MODER_MODE_OUTPUT);

    // 3. Configure TIM2 period (ARR) and prescaler (PSC) via direct writes
    play32_timx_set_auto_reload_preload_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);
    play32_timx_set_auto_reload_register(PLAY32_TIM2, 999UL); // 1000 clock cycles period
    play32_timx_set_prescaler(PLAY32_TIM2, 83UL);             // Clock frequency division by 84
    play32_timx_trigger_update_generation(PLAY32_TIM2);       // Load shadow registers (single STR)
    play32_timx_clear_update_interrupt_flag(PLAY32_TIM2);     // Atomic rc_w0 flag clear

    // 4. Start the timer counter
    play32_timx_set_counter_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);
}
```

## Development Status

This project is actively under development. Reset & Clock Control (**RCC**), General-Purpose Timers (**TIM2–TIM5**), and General-Purpose I/O (**GPIO**) are **100% complete and fully operational**, along with full Doxygen API documentation and a hardware-verified blinky example. Work is currently ongoing to expand this architecture to the remaining periphery of the MCU.

- [x] **RCC (Reset and Clock Control): Fully Completed (100%)**
  - [x] Oscillator & PLL control and status (`CR`, `PLLCFGR`, `PLLI2SCFGR`, `SSCGR`)
  - [x] System clock routing, bus prescalers, and MCO outputs (`CFGR`, `DCKCFGR`)
  - [x] Clock interrupts & Backup domain / RTC clock control (`CIR`, `BDCR`, `CSR`)
  - [x] Peripheral resets, clock enables, and Sleep-mode gating (`AHB1RSTR`–`APB2RSTR`, `AHB1ENR`–`APB2ENR`, `AHB1LPENR`–`APB2LPENR`)
- [x] **TIM2–TIM5 (General-Purpose Timers): Fully Completed (100%)**
  - [x] Core structures, control logic, and atomic status flags (`CR1`, `CR2`, `SMCR`, `DIER`, `SR`, `EGR`)
  - [x] Counters, prescalers, auto-reload layout (`CNT`, `PSC`, `ARR`)
  - [x] All Capture/Compare channels (`CCR1`–`CCR4`, `CCMR1`, `CCMR2`, `CCER`)
  - [x] Advanced DMA Burst control and trigger remapping (`DCR`, `DMAR`, `OR`)
- [x] **GPIO (General-Purpose I/O): Fully Completed (100%)**
  - [x] Port addressing & base peripheral mapping (`GPIOA`–`GPIOE`, `GPIOH`)
  - [x] Pin configuration & mode control (`MODER`, `OTYPER`, `OSPEEDR`, `PUPDR`)
  - [x] Atomic I/O data operations (`IDR`, `ODR`, `BSRR` single-bit and bulk set/reset/toggle)
  - [x] Configuration lock sequence & alternate functions (`LCKR`, `AFRL`, `AFRH`)
- [x] **Documentation & Examples:**
  - [x] Full Doxygen documentation across `RCC`, `GPIOx`, and `TIMx`
  - [x] Hardware-tested LED chaser example (`examples/01_blinky_tim2`)
- [ ] Remaining MCU periphery (`FLASH`, `PWR`, `USART`, `SPI`, `I2C`, `DMA`, `EXTI`) — *In Progress*

## Generating Documentation

This codebase includes full Doxygen annotations with X-Macro expansion enabled (`MACRO_EXPANSION = YES`):

```bash
doxygen Doxyfile
```

Open `html/index.html` in any browser to browse the generated register reference manual.

## License

This project is licensed under the **MIT License**. It is completely free, open for any modification, and can be used in both commercial and private projects. We warmly welcome community contributions and Pull Requests!
