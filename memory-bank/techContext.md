# Technical Context

## Platform Specifications

### Microcontroller
- **MCU**: STM32H723ZGT6
- **Architecture**: ARM Cortex-M7 @ 550MHz
- **Flash**: 1MB
- **RAM**: 564KB (including D1, D2, D3 domains)
- **Package**: LQFP144

### Development Environment
- **IDE**: STM32CubeIDE
- **Configuration**: STM32CubeMX (.ioc file)
- **Compiler**: ARM GCC
- **Debugger**: ST-LINK integration
- **Build System**: Make (auto-generated)

## Technology Stack

### Core Technologies
1. **STM32H7 HAL**: Hardware Abstraction Layer
   - Version: Latest STM32H7 HAL drivers
   - Peripherals: ADC, DAC, TIM, SPI, I2C, USART, FDCAN
   - DMA: Direct Memory Access for efficient data transfer

2. **FreeRTOS**: Real-Time Operating System
   - Version: Integrated with STM32 ecosystem
   - Features: Tasks, queues, semaphores, timers
   - Memory management: Static allocation preferred

3. **C++ with C Integration**
   - C++: Application logic and object-oriented design
   - C: STM32 HAL and low-level hardware access
   - Mixed compilation: Seamless C/C++ interop

### Peripheral Configuration
- **PWM Generation**: Advanced timers for motor control
- **ADC**: Multi-channel current and voltage sensing
- **Encoders**: Timer-based quadrature decoder
- **Communication**: SPI for motor driver, I2C for sensors
- **CAN**: FDCAN for system communication

## Dependencies

### Hardware Dependencies
1. **DRV8323**: Three-phase motor driver IC
   - Interface: SPI communication
   - Features: Current sensing, fault detection
   - Protection: Overcurrent, thermal shutdown

2. **Encoders**: Position feedback sensors
   - AB Incremental: Quadrature signals
   - Hall Sensors: Commutation feedback
   - Resolution: Configurable based on sensor

3. **Power Supply**: Motor and logic power domains
   - Logic: 3.3V for MCU and peripherals
   - Motor: Variable voltage for DRV8323

### Software Dependencies
1. **STM32 HAL Drivers**: Official ST drivers
   - Location: `Drivers/STM32H7xx_HAL_Driver/`
   - License: BSD 3-Clause
   - Features: All peripheral drivers

2. **CMSIS**: ARM Cortex Microcontroller Software Interface
   - Location: `Drivers/CMSIS/`
   - Version: ARM CMSIS v5.x
   - Components: Core, Device, DSP

3. **FreeRTOS**: Real-time kernel
   - Location: `Middlewares/Third_Party/FreeRTOS/`
   - License: MIT
   - Configuration: `Core/Inc/FreeRTOSConfig.h`

## Development Setup

### Build Configuration
- **Target**: STM32H723ZGTx
- **Optimization**: -Og for debug, -O2 for release
- **Linker Scripts**: 
  - `STM32H723ZGTX_FLASH.ld`: Flash execution
  - `STM32H723ZGTX_RAM.ld`: RAM execution
- **Startup**: `Core/Startup/startup_stm32h723zgtx.s`

### Memory Layout
- **Flash**: Program code and constants
- **SRAM**: Variables and stack (multiple domains)
- **Peripheral Memory**: Memory-mapped registers
- **Stack**: FreeRTOS task stacks in SRAM

### Debugging Configuration
- **Debug Format**: DWARF
- **Launch Config**: `Driver_on_H723.launch`
- **Symbols**: Available in debug builds
- **Real-time Debugging**: SWD interface

## Technical Constraints

### Real-Time Requirements
- **Control Loop**: 10kHz minimum for FOC
- **Latency**: <100μs for control response
- **Jitter**: <10μs for consistent timing
- **Priority**: Motor control tasks highest priority

### Resource Constraints
- **CPU Usage**: <80% for sustained operation
- **Memory**: Efficient use of 564KB RAM
- **Flash**: Code optimization for 1MB limit
- **Power**: Minimize consumption in idle states

### Safety Requirements
- **Fault Detection**: Hardware and software monitoring
- **Emergency Stop**: Immediate motor shutdown capability
- **Thermal Protection**: Temperature monitoring
- **Overcurrent**: Hardware-level protection

## Communication Protocols

### Internal Communication
- **SPI**: DRV8323 motor driver interface
- **I2C**: Sensor communication
- **GPIO**: Encoder signals, fault indicators
- **ADC**: Current/voltage sensing

### External Communication
- **FDCAN**: System-level communication
- **USART**: Debug/configuration interface
- **USB**: Development and diagnostics

## Performance Characteristics

### Timing Requirements
- **FOC Update**: 100μs (10kHz)
- **Encoder Reading**: 50μs maximum
- **Trajectory Update**: 1ms typical
- **Communication**: Background priority

### Accuracy Requirements
- **Position**: 0.1% of full scale
- **Current**: 1% accuracy
- **Voltage**: 1% accuracy
- **Timing**: <1% jitter

## Development Tools
- **STM32CubeIDE**: Primary development environment
- **STM32CubeMX**: Hardware configuration
- **ST-LINK**: Programming and debugging
- **STM32CubeMonitor**: Real-time monitoring
- **Version Control**: Git-based workflow
