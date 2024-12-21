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

    cout << "\n===== FETCH INSTRUCTION =====" << endl;
    cout << "Program Counter (PC) initialized to 0" << endl;

    // Start instruction execution cycle
    for (int i = 0; i < 3; i++) {
        cout << "\nCycle " << i + 1 << " STARTED:" << endl;
        cout << "Step 1: Address from PC loaded onto Address Bus." << endl;
        cout << "Step 2: RAM reads instruction from address and places it on Data Bus." << endl;
        cout << "Step 3: Data Bus transfers instruction to Instruction Register (IR)." << endl;
        CU.Decode_Send_Instruction(dataBus, addressBus, controlbus, ram, AC, IR, alu, op);
        cout << "Step 4: IR decodes instruction and sends control signals." << endl;
        cout << "Step 5: Operand fetched from RAM into AC (if required)." << endl;
        cout << "Step 6: ALU performs operation, result placed in AC." << endl;
        cout << "Step 7: Result stored in RAM at specified address." << endl;
        cout << "Cycle " << i + 1 << " COMPLETED." << endl;
        cout << "Instruction Register (IR) contains: " << IR.read() << endl;
        cout << "Accumulator (AC) contains: " << AC.read() << endl;
    }

    // Display results
    cout << "\n===== FINAL RESULT =====" << endl;
    cout << "Result stored at RAM[5]: ";
    string result = ram.read(5);
    cout << result << " (Decimal: " << stoi(result, nullptr, 2) << ")\n" << endl;

    cout << "SAP-1 Simulation Complete!\n" << endl;
    return 0;
}
