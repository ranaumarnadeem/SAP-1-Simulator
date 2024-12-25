#pragma once

#include "headers.hpp"
#include "ALU.hpp"
#include "Register.hpp"
#include "RAM.hpp"

class DataBus 
{
public:
	
	DataBus(){};
	~DataBus(){};
	
    // IT WILL BE CALLED BY THE ACCUMULATOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMULATOR AND THE INSTRUCTION REGISTER
    // We have taken the index as string so that we can use 8-bit address like for 1st location 00000000
    // and then used stoi function to convert it into integer; in this case, it would be 0.
    string getdata_Ram(RAM &obj, int index)  
	{
        cout << "DATA IS BEING READ FROM THE RAM ...." << endl;
        cout << endl;
        cout << "DATA IS SUCCESSFULLY READ FROM THE RAM " << endl;
        cout << endl;
        return obj.read(index);
    }

    // THIS WILL BE CALLED BY THE RAM TO STORE THE ACCUMULATOR CONTENT IN THE RAM.
    void store_AccumulatorData(Register &AC, RAM &ram)  
	{
        cout << "FINAL RESULT IS BEING LOADED FROM ACCUMULATOR TO THE RAM " << endl;
        cout << endl;
        string temp = AC.readAC();
        ram.writeresult(temp);
        cout << "FINAL RESULT " << ram.read(5) << " IS SUCCESSFULLY STORED IN THE RAM " << endl;
        cout << endl;
    }

    void Load_Data_Into_Instrction_Register(Register &IR, string content) {
        cout << "DATA BUS IS TAKING THE RAM CONTENT INTO THE INSTRUCTION REGISTER " << endl;
        cout << endl;
        IR.writeIR(content);
        cout << "DATA IS SUCCESSFULLY WRITTEN IN THE INSTRUCTION REGISTER" << endl;
        cout << endl;
    }

    // THIS FUNCTION IS USED TO STORE THE DATA FROM RAM INTO THE ACCUMULATOR
    void Load_Data_Into_Accumulator(Register &AC, RAM &obj, int index) {
        static string temp=getdata_Ram(obj, index);
        cout << "THIS OPERAND 1 IS BEING LOADED INTO THE ACCUMULATOR BY THE DATA BUS " << endl;
        cout << endl;
        AC.writeAC(temp);
        cout << "OPERAND 1 IS SUCCESSFULLY STORED IN THE ACCUMULATOR " << endl;
        cout << endl;
    }

    // TO LOAD OPERAND 1 FROM ACCUMULATOR TO ALU
    void Load_Data_To_Alu(Register &AC, ALU &alu, RAM &ram, char op) 
	{
        cout << "OPERAND 1 AND OPERAND 2 ARE BEING LOADED FROM ACCUMULATOR AND RAM RESPECTIVELY  TO ALU " << endl;
        cout << endl;
       // Reading data from the accumulator
        string temp1 = AC.readAC();
        //converting the string datat type to bitset 
        
        bitset<8> bitset1(temp1);
        
         // converting the bitset to int 
         //to_ulong()convert the bitset to int long data type 
        int temp2 = bitset1.to_ulong(); 
       

        cout << "OPERAND 2 IS BEING LOADED FROM RAM TO ALU " << endl;
        cout << endl;

        // Reading data from RAM
        string temp3 = ram.read(2);  // Assuming you're reading at address 2
        //converting the string data type to bitset
        
        bitset<8> bitset2(temp3);
        //converting the bitset to ulong
        
        int temp4 =bitset2.to_ulong();

        // Perform operation based on the operator
        if (op == '+') {
          int temp=	alu.add(temp2, temp4);
        
        	string result;
        	result=bitset<8>(temp).to_string();
        	// Perform addition
			AC.writeAC(result);
        }
        else 
		{
        	string result;
            result =bitset<8>(alu.subtract(temp2, temp4)).to_string();  // Perform subtraction
            AC.writeAC(result);
        }

        cout << "OPERAND 1 AND OPERAND 2 ARE SUCCESSFULLY LOADED INTO THE ALU " << endl;
        cout << endl;
    }
};

class AddressBus {
public:
	
	AddressBus(){};
	~AddressBus(){};
    // THIS WILL BE USED TO ACCESS THE CONTENT OF THE RAM
    int getaddress_of_ProgramCounter() const {
        return ProgramCounter;
    }

    void calladdressbus() 
	{
        string Program_Counter_Content = bitset<8>(ProgramCounter).to_string();
        cout << "ADDRESS " << Program_Counter_Content << " IS BEING READ FROM THE RAM " << endl;
        cout << endl;
    }
};

class ControlBus {
public:
   ControlBus(){};
  ~ControlBus(){};

    // EXECUTE FUNCTION THAT CONTROLS THE FLOW OF DATA AND OPERATIONS BETWEEN COMPONENTS
    void execute(DataBus &dataBus, AddressBus &addressBus, RAM &ram, Register &AC, Register &IR, ALU &alu, bool ReadsignalPC = false, bool ReadsignalRAM = false, bool WritesignalRAM = false, bool LoadsignalAC = false, bool LoadsignalIR = false, bool Addsignal = false, bool Subtractsignal = false, char op = 0) {
        
		int address_PC;
        static string ramcontent; // Holds the content read from RAM

        // Read signal for Program Counter
        if (ReadsignalPC) 
		{
            addressBus.calladdressbus();
            address_PC = addressBus.getaddress_of_ProgramCounter();
        }

        // Read signal for RAM
        else if (ReadsignalRAM)
		 {
            ramcontent = dataBus.getdata_Ram(ram, address_PC);
        }

        // Load signal for Instruction Register
        else if (LoadsignalIR) 
		{
            dataBus.Load_Data_Into_Instrction_Register(IR, ramcontent);
        }

        // Load signal for Accumulator
        else if (LoadsignalAC) 
		{
            dataBus.Load_Data_Into_Accumulator(AC, ram, 1);
        }

        // Add signal for ALU
        else if (Addsignal) {
            dataBus.Load_Data_To_Alu(AC, alu, ram, op);
        }

        // Subtract signal for ALU
        else if (Subtractsignal) {
            dataBus.Load_Data_To_Alu(AC, alu, ram, op);
        }

        // Write signal for RAM
        else if (WritesignalRAM) 
		{
            // Store the result in RAM using DataBus, previously stored in ALU temporarily
            dataBus.store_AccumulatorData(AC, ram);
        }
    }
};
