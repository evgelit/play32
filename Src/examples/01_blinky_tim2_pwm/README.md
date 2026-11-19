# Example 02: PWM Breathing LED with TIM2_CH1 and TIM3

Demonstrates hardware Pulse-Width Modulation (PWM) generation using **`TIM2` Channel 1** routed to pin **`PA0` (`AF1`)**, paired with **`TIM3`** millisecond polling delays to smoothly fade an LED on an **STM32F401** microcontroller using the **PLAY32 HAL**.

---

## What This Example Does

1. Enables the **AHB1** clock for `GPIOA` and the **APB1** clocks for `TIM2` and `TIM3` via `RCC`, including the mandatory read-back synchronization delay.
2. Configures pin **`PA0`** in **Alternate Function** mode (`AF1`) to output `TIM2_CH1`.
3. Configures **`TIM2`** in **PWM Mode 1** at **1 kHz** (`1000` resolution steps from `0%` to `100%` duty cycle), with **Auto-Reload Preload (`ARPE`)** and **Output Compare Preload (`OC1PE`)** enabled for glitch-free duty-cycle updates.
4. Uses **`TIM3`** (`1 kHz` / `1 ms` tick) to step the `TIM2_CCR1` duty cycle up and down every `10 ms`, creating a smooth **2-second** breathing fade cycle.

---

## Hardware Setup & Wiring

Connect an LED with a current-limiting resistor (`330 Ω`–`1 kΩ`) to **`PA0`**:

| MCU Pin | Alternate Function | Timer Channel | Connection |
| :---: | :--- | :--- | :--- |
| **`PA0`** | `AF1` | `TIM2_CH1` | Anode (`+`) via `330 Ω`–`1 kΩ` resistor → Cathode (`-`) to `GND` |

---

## Clock & PWM Timing Parameters

* **`SYSCLK` / `HCLK` / `APB1` Timer Clock:** `16 MHz` (default internal **HSI** RC oscillator after reset).
* **`TIM2` (PWM Generator):**
    * **Prescaler (`PSC`):** `16 - 1 = 15` → `1 MHz` counter clock (`1 µs` tick).
    * **Period (`ARR`):** `1000 - 1 = 999` → `1 kHz` PWM frequency (`1 ms` PWM period).
    * **Duty Cycle (`CCR1`):** Sweeps between `0` (`0%`) and `1000` (`100%`) in steps of `10` (`1%` per step).
* **`TIM3` (Delay Timer):**
    * **Prescaler (`PSC`):** `16000 - 1 = 15999` → `1 kHz` counter clock (`1 ms` tick).

---

## Expected Behavior

* The LED connected to **`PA0`** smoothly fades from **0% (off)** to **100% (full brightness)** over **1.0 second**, then fades back down to **0%** over **1.0 second**, repeating continuously.
