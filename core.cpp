#include "headers.hpp"
#include "components.cpp"
#include "Utilities.cpp"

int main() {
    // Initialize components
    InstructionRegister IR;
    ControlBus controlBus;
    Accumulator accumulator;

    // Example instruction to decode and execute
    IR.loadInstruction("11001010"); // Example binary instruction

    // Decode and send instruction
    ControlUnit controlUnit;
    controlUnit.Decode_Send_Instruction_Register(IR, controlBus);

    // Read and display accumulator content
    std::cout << "Accumulator content: " << toDecimal(toBinary(accumulator.read())) << std::endl;

    return 0;
}