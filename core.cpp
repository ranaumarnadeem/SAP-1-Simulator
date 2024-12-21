#include "headers.hpp"
#include "components.cpp"
#include "Utilities.cpp"

int main() 
{
    ControlUnit CU;
    ControlBus controlbus;
    RAM ram;
    AddressBus addressBus;
    DataBus dataBus;
    Register IR;
    Register AC;
    ALU alu;

    uint8_t op1;
    uint8_t op2;
    char op;

    cout << "===== SAP-1 SIMULATOR =====" << endl;
    
    // Get user input for operands and operation
    cout << "Enter Operand 1 (0-255): ";
    cin >> op1;

    cout << "Enter Operand 2 (0-255): ";
    cin >> op2;

    cout << "Enter Operation (+ or -): ";
    cin >> op;

    cout << "\nWriting Data to RAM..." << endl;
    ram.writeData(op1, op, op2);
    cout << "Data successfully written to RAM!\n" << endl;

    cout << "\n===== EXECUTING INSTRUCTIONS =====\n" << endl;

    // Start instruction execution cycle
    CU.Decode_Send_Instruction(dataBus, addressBus, controlbus, ram, AC, IR, alu, op);

    // Display results
    cout << "\n===== FINAL RESULT =====" << endl;
    cout << "Result stored at RAM[5]: ";
    string result = ram.read(5);
    cout << result << " (Decimal: " << stoi(result, nullptr, 2) << ")\n" << endl;

    cout << "SAP-1 Simulation Complete!\n" << endl;
    return 0;
}
