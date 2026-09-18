# FreeRTOS Event Management on ATmega328P (Bare-Metal)

This repository contains a real-time embedded C project implementing event synchronization using **FreeRTOS Event Groups** on an ATmega328P microcontroller. 

The project is built entirely **bare-metal** using a custom toolchain (`avr-gcc`, `make`, `avrdude`) without any IDE dependency (Arduino IDE or Microchip Studio).

---

## 📌 Project Overview
The system handles 3 distinct asynchronous event tasks triggered by external push buttons and a manager task that synchronizes LED outputs using FreeRTOS Event Groups.

- **Task 1, 2, 3:** Monitor digital inputs (PD2, PD3, PD4) and set corresponding event bits (`EVT1`, `EVT2`, `EVT3`) upon detection.
- **Task 4 (Manager):** Waits for event bits using `xEventGroupWaitBits()` and triggers output LEDs (PB0, PB1, PB2) accordingly.

---

## 🛠 Tech Stack & Toolchain
- **Microcontroller:** ATmega328P (16 MHz)
- **RTOS:** FreeRTOS (Event Groups, Task Management)
- **Language:** Embedded C
- **Compiler:** `avr-gcc`
- **Build System:** Custom `Makefile`
- **Simulation:** Proteus VSM

---

## ⚙️ Compilation & Build Instructions

1. **Clean previous builds:**
   ```bash
   make clean