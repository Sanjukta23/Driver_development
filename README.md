# Bare-Metal STM32 Peripheral Drivers

Peripheral drivers for the STM32F446RE (ARM Cortex-M4), written from scratch at
register level in Embedded C **without HAL or CubeMX**. Every driver is built
directly from the device reference manual and datasheets, with the microcontroller's
memory-mapped registers and NVIC configured by hand for full control of the hardware.

## Overview

This repository implements a complete set of bare-metal drivers for the STM32F446RE
Nucleo board, each exposing a clean, reusable API and supporting both polling and
interrupt-driven operation. The drivers are exercised by a series of application
programs that run on real hardware, with several peripherals validated against an
Arduino acting as the communication slave.

The aim of the project was to understand — rather than abstract away — how
peripherals are clocked, configured and driven, and to debug genuine hardware
behaviour with a logic analyser instead of relying on generated code.

## Drivers

| Driver | Description |
|--------|-------------|
| GPIO   | Input/output, alternate-function and pull-up/down configuration, plus external-interrupt (EXTI) support with NVIC enable and priority configuration |
| RCC    | Peripheral clock control and clock configuration (used to derive peripheral clock speeds for baud-rate and timing calculations) |
| SPI    | Full-duplex master communication, blocking and interrupt-mode transfers (`SPI_SendDataIT` / `SPI_ReceiveDataIT`) and IRQ handling |
| I2C    | Master and slave operation, blocking and interrupt-mode transfers, and slave callback events |
| USART  | Configurable UART/USART communication with baud-rate setup, flag handling and an application event callback |

All interrupt handling (GPIO/EXTI, SPI, I2C) is configured directly through the
Cortex-M4 NVIC registers defined in the MCU header.

## Hardware and tools

- **Board:** STM32 Nucleo-F446RE (ARM Cortex-M4)
- **Slave device:** Arduino, configured as an SPI / I2C / UART slave for testing (see `arduino as slave/`)
- **Analysis:** 8-channel Saleae logic analyser (Logic 2) for capturing live bus waveforms
- **Toolchain:** STM32CubeIDE (GCC ARM, bare-metal — no HAL)
- **Bench:** Breadboard, jumper wires, push button and LEDs

## Repository structure

```
Driver_development/
├── stm32f4466xx_drivers/              # STM32CubeIDE project
│   ├── drivers/
│   │   ├── Inc/                       # MCU header + driver headers
│   │   │   ├── stm32f4466xx.h         # Device header: registers, bit definitions, NVIC
│   │   │   ├── stm32f4466xx_gpio_driver.h
│   │   │   ├── stm32f4466xx_rcc_driver.h
│   │   │   ├── stm32f4466xx_spi_driver.h
│   │   │   ├── stm32f4466xx_i2c_driver.h
│   │   │   └── stm32f4466xx_usart_driver.h
│   │   └── Src/                       # Driver implementations (.c)
│   └── Src/                           # Application / test programs
└── arduino as slave/                 # Arduino slave sketches (SPI / I2C / UART)
```

## Application programs

The `Src/` folder contains test programs that build progressively from basic GPIO
up to interrupt-driven communication:

- **GPIO:** LED toggle, LED + button, external button, frequency control
- **Interrupts:** push-button EXTI interrupt
- **SPI:** transmit testing, transmit to Arduino, command handling, interrupt-based receive
- **I2C:** master transmit/receive (blocking and interrupt), slave transmit string
- **USART:** UART transmit, case-conversion exchange with the Arduino

## How it was tested

- Implemented and run on **real hardware**, not simulation.
- SPI, I2C and USART communication validated against an **Arduino acting as the slave**.
- Bus timing and data integrity verified by capturing live waveforms on the
  **Saleae logic analyser**.
- Interrupt-driven input and communication tested on hardware (EXTI, SPI/I2C IT modes).

## Debugging highlights

Real hardware behaviour worked through during development included:

- **Active-low button polarity** on the Nucleo board (vs. the active-high wiring used in some references).
- Correct **EXTI line to NVIC** mapping and interrupt-priority configuration.

## Build and run

1. Clone the repository:
   ```bash
   git clone https://github.com/Sanjukta23/Driver_development.git
   ```
2. Open **STM32CubeIDE** → *File → Open Projects from File System…* and select the
   `stm32f4466xx_drivers` folder.
3. Select the application program to run in `Src/`, build the project and flash it to
   a connected Nucleo-F446RE.
4. For the SPI / I2C / UART tests, load the matching sketch from `arduino as slave/`
   onto an Arduino and wire it as the slave device.

## Skills demonstrated

Embedded C, register-level driver development, STM32F446RE / ARM Cortex-M4,
SPI, I2C, USART/UART, GPIO, RCC clock configuration, interrupt handling (NVIC / EXTI),
bare-metal firmware, logic-analyser debugging, and Git version control.

## Author

**Sanjukta Aparna Venkatachalam** 
