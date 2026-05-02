# BMOS (Bare Metal OS)

An educational, preemptive Real-Time Operating System (RTOS) built for ARM Cortex-M microcontrollers.

## 📖 About
This project is a custom implementation of a task scheduler developed while following the professional curriculum by **FastBit Embedded Brain Academy**. It serves as a deep dive into the internal mechanics of RTOS kernels and ARM Cortex-M processor architecture.

## 🚀 Core Features
*   **Preemptive Round-Robin Scheduling**: Implements time-slicing using the `SysTick` timer to switch between tasks automatically[cite: 1].
*   **Hardware Context Switching**: Efficiently saves and restores task states using `PendSV` and `SVC` handlers implemented in ARM Assembly[cite: 1].
*   **Dual Stack Architecture**: Utilizes `MSP` (Main Stack Pointer) for the kernel and interrupt handlers, while using `PSP` (Process Stack Pointer) for user tasks[cite: 1].
*   **Blocking Task State**: Includes a non-blocking `delay` function that puts tasks into a `BLOCKED` state, allowing the CPU to execute other ready tasks[cite: 1].
*   **Fault Handling**: Includes basic handlers for `HardFault`, `MemManage`, and `UsageFault` for easier debugging[cite: 1].

## 🛠️ Technical Details
*   **Language**: C and ARM Inline Assembly[cite: 1].
*   **Architecture**: ARM Cortex-M4 (specifically tested on STM32F446RE)[cite: 1].
*   **Compiler**: GCC ARM GNU Toolchain[cite: 1].

## 🏗️ Project Structure
*   `Src/BMOS.c`: Core scheduler logic, context switching, and system initialization[cite: 1].
*   `Src/led.c`: Low-level GPIO driver for status LEDs[cite: 1].
*   `Inc/BMOS.h`: TCB (Task Control Block) definitions and OS constants[cite: 1].

## 🎓 Acknowledgments
This project was developed as part of the "Mastering RTOS: Hands on FreeRTOS and STM32" course series by **FastBit Embedded Brain Academy**. Special thanks to the instructors for the deep insights into ARM internals.

## 📋 Roadmap
- [ ] Implement Binary and Counting Semaphores
- [ ] Add Mutex support with Priority Inheritance
- [ ] Integrate UART for system logging