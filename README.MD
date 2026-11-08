# Play32 HAL (STM32F401 CCU)

**Play32** is a lightweight, open-source, and completely free Hardware Abstraction Layer (HAL) for the STM32F401 microcontroller.

The project is built for the community with a core focus on **maximum performance (zero-cost abstractions)**, minimal binary footprint, and **strict Compile-time Type Safety** to eliminate register-level bugs before the code even runs.

## Key Features

- **X-Macro Architecture:** The entire register-level API is automatically generated from a single declarative table. Zero code duplication.
- **Strict Type Safety:** Every bit-field is bound to its own unique `enum` type. No more accidental invalid masks or shift offsets.
- **Zero-Cost Abstractions:** Generated functions are defined as `static inline`. The compiler resolves them directly into atomic hardware memory instructions—performance matches pure CMSIS/register-level code.
- **Interactive Structure:** Structured with `#pragma region` directives, ensuring clean, foldable, and human-readable source files inside modern IDEs.
- **Ultimate Freedom:** Distributed under the MIT License—use, modify, and distribute with no restrictions.

## Quick Start

Just include the main header file into your application:

```c
#include "timx.h"

void init_timer_example(void) {
    // 1. Enable Auto-Reload Preload (ARPE) for TIM2
    play32_timx_set_auto_reload_preload_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);
    
    // 2. Set Period (ARR) and Prescaler (PSC) directly
    play32_timx_set_auto_reload_reister(PLAY32_TIM2, 999); // 1000 clock cycles period
    play32_timx_set_prescaler(PLAY32_TIM2, 83);          // Clock frequency division by 84
    
    // 3. Start the timer counter
    play32_timx_set_counter_enable(PLAY32_TIM2, PLAY32_TIMx_SWITCH_ENABLED);
}
```

## Development Status

This project is actively under development. General-purpose timers **TIM2–TIM5 are 100% complete and fully operational**. Work is currently ongoing to expand this architecture to the remaining periphery of the MCU.

- [x] **TIM2–TIM5 (General-Purpose Timers): Fully Completed (100%)**
    - [x] Core structures, control logic (CR1, CR2, SMCR, DIER)
    - [x] Counters, prescalers, auto-reload layout (CNT, PSC, ARR)
    - [x] All Capture/Compare channels (CCR1–CCR4, CCER)
    - [x] Advanced DMA Burst control (DCR, DMAR)
- [ ] Remaining MCU periphery — *In Progress*

*Note: The core engine is finalized. Support for all remaining hardware timers is actively being integrated and will be included in the final stable release.*

## License

This project is licensed under the **MIT License**. It is completely free, open for any modification, and can be used in both commercial and private projects. We warmly welcome community contributions and Pull Requests!
