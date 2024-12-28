# **SAP-1 Simulator**

## **Overview**
This project is a simulator for the SAP-1 (Simple As Possible) architecture implemented in C++. It simulates the core components of the SAP-1 computer, including memory, registers, control unit, and ALU, and provides output through a graphical interface (using Tkinter) and command-line interactions.

---

## **Folder Structure**
- Core.cpp contains all the backend files eg core,control unit etc all written in c++.
- Main contains gui.py that is frontend linked with backend.

---

## **Features**
- Simulates the core components of SAP-1:
  - **RAM**: 16 bytes of memory for instructions and data.
  - **Registers**: Temporary storage for instructions and data.
  - **Control Unit**: Manages the execution of instructions.
  - **ALU**: Performs basic arithmetic and logic operations.
  - **BUS**: Connects all components.
- GUI for visualizing outputs (Tkinter).
- Command-line interface (CLI) for interacting with the simulator.
- Keyboard shortcuts has also been added press `Escape` to close Application, `Ctrl+R` to refresh and `Enter` to start simulation.

---

## **Dependencies**
### **System Requirements**
- C++17 or later
- Python3
- Compiler: GCC, Clang, or MSVC

### **Libraries Used**
- Standard C++ libraries (`<iostream>`, `<array>`, etc.)
- Custom utility library (`utilities.cpp`)
- Tkinter for GUI

---

## **Installation**
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/SAP-1-Simulator.git
   cd SAP-1-Simulator
## **Usage**
1. Launch the gui.py in folder Main.

2. View results in the GUI


---

## **Code Organization**

### **Main File**
- `gui.py` :Run it to see whole simulation
- `core.cpp`: Initializes and orchestrates the simulator.

### **Supporting Files**
- `header.hpp`: Contains all required includes, such as standard headers and SAP-1 component headers.
- `utilities.cpp`: Includes constants like memory size, helper functions, and debugging utilities.

### **Components **
Contains the core components of the SAP-1 simulator:
- **RAM.hpp**: Implements memory operations like `read()`, `write()`, and `reset()`.
- **Control_Unit.hpp**: Encodes the fetch-decode-execute cycle.
- **Register.hpp**: Implements basic registers (e.g., Accumulator, Instruction Register).
- **BUS.hpp**: Manages data transfer between components.
- **ALU.hpp**: Handles arithmetic and logic operations.

---

## **Authors**
- **Rana Umar Nadeem** ([@ranaumarnadeem](https://github.com/ranaumarnadeem))
- **Muhammad Asad Naseem** ([@asad209999](https://github.com/asad209999))

