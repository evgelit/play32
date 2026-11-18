# Example 01: LED Chaser with TIM2 Polling Delay

Demonstrates basic peripheral clock setup, GPIO output configuration, atomic pin toggling, and hardware timer polling on an **STM32F401** microcontroller using the **PLAY32 HAL**.

---

## What This Example Does

1. Enables the **AHB1** clock for `GPIOB` and the **APB1** clock for `TIM2` via `RCC`, including the mandatory read-back synchronization delay.
2. Configures pins **`PB3` through `PB9`** as general-purpose push-pull outputs.
3. Configures **`TIM2`** (32-bit timer) with a prescaler of `15999` (`16 MHz / 16000 = 1 kHz`), yielding a **1 ms** counter tick.
4. Sequentially toggles **`PB9` → `PB8` → `PB7` → `PB6` → `PB5` → `PB4` → `PB3`** every **50 ms** using atomic `BSRR` writes (`play32_gpiox_toggle()`).

---

## Hardware Setup & Wiring

Connect 7 LEDs (with current-limiting resistors, e.g., `330 Ω`–`1 kΩ` to `GND`) to the following **Port B** pins:

| Step Order | MCU Pin | Default Reset Function | Note |
| :---: | :--- | :--- | :--- |
| 1 | **`PB9`** | GPIO | Standard I/O |
| 2 | **`PB8`** | GPIO | Standard I/O |
| 3 | **`PB7`** | GPIO | Standard I/O |
| 4 | **`PB6`** | GPIO | Standard I/O |
| 5 | **`PB5`** | GPIO | Standard I/O |
| 6 | **`PB4`** | `NJTRST` (JTAG) | Reconfigured to GPIO output; SWD (`PA13`/`PA14`) remains active |
| 7 | **`PB3`** | `JTDO` / `SWO` | Reconfigured to GPIO output; SWD (`PA13`/`PA14`) remains active |

---

## Clock Assumptions

* **`SYSCLK` / `HCLK` / `APB1` Timer Clock:** `16 MHz` (default internal **HSI** RC oscillator after reset, with no PLL or APB1 prescaler configured).
* **`TIM2` Prescaler (`PSC`):** `16000 - 1 = 15999` → `1 kHz` counter frequency (`1 ms` per tick).
* If you configure a different `SYSCLK` or `PPRE1` prescaler, update `SYSCLK_HZ` in `main.c` accordingly.

---

## Expected Behavior

* **Pass 1:** LEDs turn **ON** one by one from `PB9` down to `PB3` at 50 ms intervals (`350 ms` total).
* **Pass 2:** LEDs turn **OFF** one by one from `PB9` down to `PB3` at 50 ms intervals (`350 ms` total).
* The sequence repeats indefinitely.
