# Example 03: USART2 Periodic String Transmission (25 MHz HSE)

Demonstrates asynchronous serial (UART) transmission using **`USART2`** routed to pins **`PA2` (`TX`)** and **`PA3` (`RX`)** in **`AF7`**, clocked from the external **25 MHz HSE** crystal oscillator, with **`TIM3`** providing 1-second polling intervals on an **STM32F401** microcontroller using the **PLAY32 HAL**.

---

## What This Example Does

1. Enables the external **25 MHz HSE** crystal oscillator via `RCC` and switches **`SYSCLK`** (and `HCLK` / `PCLK1`) to `HSE` for high-precision baud-rate timing.
2. Enables the **AHB1** clock for `GPIOA` and the **APB1** clocks for `USART2` and `TIM3`, including read-back synchronization delays.
3. Configures **`PA2`** (`TX`) and **`PA3`** (`RX`, with internal pull-up enabled) in **Alternate Function `AF7`**.
4. Computes the **`USART_BRR`** baud-rate divider (`2604` = `0x0A2C`) at compile time from `SYSCLK_HZ` (`25 MHz`) and `USART2_BAUD_RATE` (`9600` baud), configures frame format (`9`-bit word length, `1` stop bit, no parity), and enables `USART2`.
5. Transmits a message string every **1.0 second** using `TXE` / `TC` status flag polling and `TIM3` millisecond delays.

---

## Hardware Setup & Wiring

Connect a **3.3 V USB-to-TTL serial adapter** (e.g., CP2102, CH340, FT232RL) cross-over to `PA2`/`PA3`:

| STM32F401 Pin | Alternate Function | USART2 Signal | USB-TTL Adapter Pin |
| :---: | :--- | :--- | :--- |
| **`PA2`** | `AF7` | `USART2_TX` | **`RXD`** |
| **`PA3`** | `AF7` | `USART2_RX` (Pull-Up) | **`TXD`** |
| **`GND`** | — | Ground | **`GND`** |

---

## Clock & Serial Timing Parameters

* **`SYSCLK` / `HCLK` / `PCLK1`:** `25 MHz` (external **HSE** crystal oscillator).
* **`USART2` Configuration:**
  * **Baud Rate:** `9600` bit/s (`BRR = round(25,000,000 / 9600) = 2604 = 0x0A2C` at 16x oversampling).
  * **Frame Format:** `9` data bits (`M = 1`), `1` stop bit (`STOP = 00`), no parity (`PCE = 0`).
* **`TIM3` (Interval Timer):**
  * **Prescaler (`PSC`):** `25000 - 1 = 24999` → `1 kHz` counter clock (`1 ms` tick).
  * **Transmit Period (`ARR`):** `1000` ticks → `1.0 s` interval between messages.

---

## Expected Behavior

* Open any serial monitor (CLion Serial Monitor, PuTTY, Tera Term) on your adapter's `COM` port at **`9600` baud**.
* Every **1.0 second**, the following line appears cleanly in the terminal:
  ```text
  Hello, this is STM32 UART test. This string was transmitted via PLAY32 HAL
  ```
