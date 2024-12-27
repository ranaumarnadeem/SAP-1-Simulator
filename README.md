# **SAP-1 Simulator**

## **Overview**
This project is a simulator for the SAP-1 (Simple As Possible) architecture implemented in C++. It simulates the core components of the SAP-1 computer, including memory, registers, control unit, and ALU, and provides output through a graphical interface (using Qt) and command-line interactions.

---

## **Folder Structure**


---

## **Features**
- Simulates the core components of SAP-1:
  - **RAM**: 16 bytes of memory for instructions and data.
  - **Registers**: Temporary storage for instructions and data.
  - **Control Unit**: Manages the execution of instructions.
  - **ALU**: Performs basic arithmetic and logic operations.
  - **BUS**: Connects all components.
- GUI for visualizing outputs (using Qt).
- Command-line interface (CLI) for interacting with the simulator.

---

## **Dependencies**
### **System Requirements**
- C++17 or later
- Qt framework (for GUI)
- Compiler: GCC, Clang, or MSVC

### **Libraries Used**
- Standard C++ libraries (`<iostream>`, `<array>`, etc.)
- Custom utility library (`utilities.cpp`)
- Qt library for GUI.

---

## **Installation**
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/SAP-1-Simulator.git
   cd SAP-1-Simulator
## **Usage**
1. Launch the program.
2. Use the CLI to:
   - Load programs into memory.
   - Execute instructions step-by-step or continuously.
3. View results in the GUI:
   - Visualize memory, register states, and the control unit's operations.

---

## **Code Organization**

### **Core File**
- `core.cpp`: Initializes and orchestrates the simulator.

### **Lib Folder**
- `header.h`: Contains all required includes, such as standard headers and SAP-1 component headers.
- `utilities.cpp`: Includes constants like memory size, helper functions, and debugging utilities.

### **Components Folder**
Contains the core components of the SAP-1 simulator:
- **RAM.cpp**: Implements memory operations like `read()`, `write()`, and `reset()`.
- **Control_Unit.cpp**: Encodes the fetch-decode-execute cycle.
- **Register.cpp**: Implements basic registers (e.g., Accumulator, Instruction Register).
- **BUS.cpp**: Manages data transfer between components.
- **ALU.cpp**: Handles arithmetic and logic operations.

---

## **Authors**
- **Rana Umar Nadeem** ([@ranaumarnadeem](https://github.com/ranaumarnadeem))
- **Muhammad Asad Naseem** ([@asad209999](https://github.com/asad209999))


