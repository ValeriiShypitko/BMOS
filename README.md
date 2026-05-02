# BMOS (Bare Metal OS)

An educational, preemptive Real-Time Operating System (RTOS) built for ARM Cortex-M microcontrollers.

## 📖 About
This is a custom RTOS kernel built from scratch as part of the **"Embedded Systems Programming on ARM Cortex-M Video Course"** by FastBit Embedded Brain Academy. 

Unlike using a pre-built OS like FreeRTOS, this project focuses on low-level kernel development, including manual stack frame manipulation and exception-based context switching.

## 🚀 Core Features
*   **Preemptive Round-Robin Scheduling**: Implements time-slicing using the `SysTick` timer to switch between tasks automatically.
*   **Hardware Context Switching**: Efficiently saves and restores task states using `PendSV` and `SVC` handlers implemented in ARM Assembly.
*   **Dual Stack Architecture**: Utilizes `MSP` (Main Stack Pointer) for the kernel and interrupt handlers, while using `PSP` (Process Stack Pointer) for user tasks.
*   **Blocking Task State**: Includes a non-blocking `delay` function that puts tasks into a `BLOCKED` state, allowing the CPU to execute other ready tasks.
*   **Fault Handling**: Includes basic handlers for `HardFault`, `MemManage`, and `UsageFault` for easier debugging.

## 🛠️ Technical Details
*   **Language**: C and ARM Inline Assembly.
*   **Architecture**: ARM Cortex-M4 (specifically tested on STM32F446RE).
*   **Compiler**: GCC ARM GNU Toolchain[.

## 🏗️ Project Structure
*   `Src/BMOS.c`: Core scheduler logic, context switching, and system initialization.
*   `Src/led.c`: Low-level GPIO driver for status LEDs.
*   `Inc/BMOS.h`: TCB (Task Control Block) definitions and OS constants.

## 🎓 Acknowledgments
This project was developed as part of the "Embedded Systems Programming on ARM Cortex-M3/M4 Processor" course series by **FastBit Embedded Brain Academy**. Special thanks to the instructors for the deep insights into ARM internals.

## 📋 Roadmap
- [ ] Implement Binary and Counting Semaphores
- [ ] Add Mutex support with Priority Inheritance
