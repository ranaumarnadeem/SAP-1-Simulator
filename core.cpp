#include "headers.hpp"
#include "components.cpp"
#include "Utilities.cpp"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: ./sap1_simulator <operand1> <operand2> <operation>" << std::endl;
        return 1;
    }

    // Only declare op1, op2, and op once
    uint8_t op1 = std::stoi(argv[1]);
    uint8_t op2 = std::stoi(argv[2]);
    char op = argv[3][0]; // Assuming operation is passed as '+' or '-'

    // Create the SAP-1 components
    ControlUnit CU;
    ControlBus controlbus;
    RAM ram;
    AddressBus addressBus;
    DataBus dataBus;
    Register IR;
    Register AC;
    ALU alu;

    // Check if operands are within the valid range (0 to 255)
    try 
    {
        if(op1 < 0 || op1 > 255 || op2 < 0 || op2 > 255) {
            throw 0;
        }
    }
    catch(int a)
    {
        std::cout << "CHECK YOUR OPERAND 1 AND OPERAND 2. IT MUST BE BETWEEN 0 AND 255 INCLUSIVE .... TERMINATING THE PROGRAM." << std::endl;
        return 0;
    }

    // Write data to RAM
    ram.writeData(op1, op, op2);
    
    // Decode and execute the instruction
    CU.Decode_Send_Instruction(dataBus, addressBus, controlbus, ram, AC, IR, alu, op);

    return 0;
}
