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

    int op1;
    int op2;
    char op;

    cout << "PLEASE ENTER THE OPERAND 1" << endl;
    cin >> op1;
    
    cout << "PLEASE ENTER THE OPERAND 2" << endl;
    cin >> op2;
    
    cout << "PLEASE ENTER THE OPERATION YOU WANT TO PERFORM (+) OR (-)" << endl;
    cin >> op;
    
    try 
    {
     if( op1<0 || op>255 || op2<0||op2>255)
		{
			throw 0;
		}
	
	}
	
	catch(int a)
	{
		cout << "CHECK YOUR OPERAND 1 AND OPERAND 2 IT MUST BE BETWEEN 0 AND 255 INCLUSIVE .... TERMINATING THE PROGRAM	" << endl;
		return 0;
	}

    ram.writeData(op1, op, op2);
    
    CU.Decode_Send_Instruction(dataBus, addressBus, controlbus, ram, AC, IR, alu, op);
     
    return 0;
}


