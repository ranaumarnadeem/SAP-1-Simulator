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

    cout << "PLEASE ENTER THE OPERAND 1" << endl;
    cin >> op1;

    cout << "PLEASE ENTER THE OPERAND 2" << endl;
    cin >> op2;

    cout << "PLEASE ENTER THE OPERATION YOU WANT TO PERFORM (+) OR (-)" << endl;
    cin >> op;

    ram.writeData(op1, op, op2);
    
    CU.Decode_Send_Instruction(dataBus, addressBus, controlbus, ram, AC, IR, alu, op);

    return 0;
}


