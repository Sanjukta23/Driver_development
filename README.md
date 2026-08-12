# STM32F4 Peripheral Driver Development

A hand-written, register-level peripheral driver library for the STM32F4 (referred to in this repo as `stm32f4466xx`) microcontroller, built entirely from the reference manual — no vendor HAL or CMSIS drivers. The goal of this project is to implement each peripheral driver from first principles: register maps, bit definitions, init/de-init routines, polling and interrupt-driven APIs, and application-facing callbacks, in the style of a production embedded driver library.

## What's implemented

The core header (`stm32f4466xx.h`) defines the processor and peripheral register maps and pulls in one driver per peripheral:

| Driver | Header | Covers |
|---|---|---|
| GPIO | `stm32f4466xx_gpio_driver.h` | Pin mode, speed, pull-up/down, output type, alternate function configuration; interrupt (EXTI) support |
| SPI | `stm32f4466xx_spi_driver.h` | Master/slave mode, full-duplex/half-duplex/simplex bus configs, clock polarity/phase, polling and interrupt-driven send/receive with a state machine (`SPI_READY` / `SPI_BUSY_IN_RX` / `SPI_BUSY_IN_TX`) and application event callbacks |
| I2C | `stm32f4466xx_i2c_driver.h` | Register-level I2C configuration and communication |
| USART | `stm32f4466xx_usart_driver.h` | Register-level USART/UART configuration and communication |
| RCC | `stm32f4466xx_rcc_driver.h` | Clock source and peripheral clock management |

Every driver follows the same pattern seen in the SPI driver: a `*_Config_t` struct for peripheral settings, a `*_Handle_t` struct combining the peripheral base pointer with its config and (where applicable) Tx/Rx buffer state, peripheral clock control, init/de-init, blocking and interrupt-based data transfer, IRQ configuration/priority/handling, and flag/status helpers.

Common peripheral infrastructure includes:

- Full register-definition structs for GPIO, RCC, EXTI, SYSCFG, SPI, I2C, and USART
- Clock enable/disable and peripheral reset macros for every peripheral instance
- NVIC IRQ number definitions and priority macros for all EXTI, SPI, I2C, and USART interrupt lines
- Bit-position macros for every control/status register used by the drivers

## Repository layout

```
Driver_development/
├── stm32f4466xx_drivers/
│   ├── drivers/
│   │   ├── Inc/     # stm32f4466xx.h + one *_driver.h per peripheral
│   │   └── Src/     # One *_driver.c implementation per peripheral
│   └── Src/         # Application/test programs exercising the drivers (e.g. 001led_toggle.c)
├── arduino as slave/ # Arduino-side counterpart project for I2C/SPI slave communication tests
└── .metadata/        # STM32CubeIDE / Eclipse workspace metadata
```

Application test programs in `stm32f4466xx_drivers/Src/` are built against the driver library to validate each peripheral — for example, `001led_toggle.c` configures `GPIOA` pin 5 as an open-drain output through the GPIO driver and toggles it in a loop.

## Hardware

- STM32F4-series development board (Discovery or Nucleo)
- Arduino board used as an I2C/SPI slave counterpart for communication testing (`arduino as slave/`)

## Toolchain

- STM32CubeIDE (Eclipse-based) for the STM32 side
- Arduino IDE for the Arduino slave sketches
- ARM GCC (arm-none-eabi-gcc) and ST-Link for building and flashing the STM32 target

## Building

1. Import `stm32f4466xx_drivers` into STM32CubeIDE as an existing project.
2. Select the application file to build in `Src/` (only one `main` should be active at a time).
3. Build and flash to the target board via ST-Link.
4. For I2C/SPI slave tests, flash the corresponding sketch in `arduino as slave/` to an Arduino board and wire it to the STM32 target.

## Status

Actively developed peripheral driver library — GPIO, SPI, I2C, USART, and RCC drivers are implemented; application tests in `Src/` exercise them individually.
