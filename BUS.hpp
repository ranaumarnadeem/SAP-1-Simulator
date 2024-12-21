#include "headers.hpp"
#include "ALU.hpp"
#include "Register.hpp"
#include "RAM.hpp"

class DataBus {
public:
    // IT WILL BE CALLED BY THE ACCUMULATOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMULATOR AND THE INSTRUCTION REGISTER
    // We have taken the index as string so that we can use 8-bit address like for 1st location 00000000
    // and then used stoi function to convert it into integer; in this case, it would be 0.
    string getdata_Ram(RAM &obj, int index) const {
        cout << "DATA IS BEING FETCHED FROM THE RAM ...." << endl;
        cout << "DATA IS SUCCESSFULLY FETCHED FROM THE RAM " << endl;
        return obj.read(index);
    }

    // THIS WILL BE CALLED BY THE RAM TO STORE THE ACCUMULATOR CONTENT IN THE RAM.
    void store_AccumulatorData(Register &AC, RAM &ram) const {
        cout << "FINAL RESULT IS BEING LOADED FROM ACCUMULATOR TO THE RAM " << endl;
        string temp = AC.read();
        ram.writeresult(temp);
        cout << "FINAL RESULT " << temp << " IS SUCCESSFULLY STORED IN THE RAM " << endl;
    }

    void Load_Data_Into_Instrction_Register(Register &IR, string content) {
        cout << "DATA BUS IS TAKING THE RAM CONTENT INTO THE INSTRUCTION REGISTER " << endl;
        IR.write(content);
        cout << "DATA IS SUCCESSFULLY WRITTEN IN THE INSTRUCTION REGISTER" << endl;
    }

    // THIS FUNCTION IS USED TO STORE THE DATA FROM RAM INTO THE ACCUMULATOR
    void Load_Data_Into_Accumulator(Register &AC, RAM &obj, int index) {
        static string temp = getdata_Ram(obj, index);
        cout << "THIS OPERAND 1 IS BEING LOADED INTO THE ACCUMULATOR BY THE DATA BUS " << endl;
        AC.write(temp);
        cout << "OPERAND 1 IS SUCCESSFULLY STORED IN THE ACCUMULATOR " << endl;
    }

    // TO LOAD OPERAND 1 FROM ACCUMULATOR TO ALU
    void Load_Data_To_Alu(Register &AC, ALU &alu, RAM &ram, char op) {
        cout << "OPERAND 1 AND OPERAND 2 ARE BEING LOADED FROM ACCUMULATOR TO ALU " << endl;

        // Reading data from the accumulator
        string temp1 = AC.read();
        uint8_t temp2 = static_cast<uint8_t>(stoi(temp1));  // Convert string to uint8_t

        cout << "OPERAND 2 IS BEING LOADED FROM RAM TO ALU " << endl;

        // Reading data from RAM
        string temp3 = ram.read(2);  // Assuming you're reading at address 2
        uint8_t temp4 = static_cast<uint8_t>(stoi(temp3));  // Convert string to uint8_t

        // Perform operation based on the operator
        if (op == '+') {
            alu.add(temp2, temp4);  // Perform addition
        }
        else {
            alu.subtract(temp2, temp4);  // Perform subtraction
        }

        cout << "OPERAND 1 AND OPERAND 2 ARE SUCCESSFULLY LOADED INTO THE ALU " << endl;
    }
};

class AddressBus {
public:
    // THIS WILL BE USED TO ACCESS THE CONTENT OF THE RAM
    int getaddress_of_ProgramCounter() const {
        return ProgramCounter;
    }

    void calladdressbus() 
	{
        string Program_Counter_Content = bitset<8>(ProgramCounter).to_string();
        cout << "ADDRESS " << Program_Counter_Content << " IS BEING READ FROM THE RAM " << endl;
    }
};

class ControlBus {
public:
    // Control signals for different components
    bool readsignalPC;
    bool readsignalRAM;
    bool writesignalRAM;
    bool loadsignalAC;
    bool loadsignalIR;
    bool addsignal;
    bool subtractsignal;

    // EXECUTE FUNCTION THAT CONTROLS THE FLOW OF DATA AND OPERATIONS BETWEEN COMPONENTS
    void execute(DataBus &dataBus, AddressBus &addressBus, RAM &ram, Register &AC, Register &IR, ALU &alu, bool ReadsignalPC = false, bool ReadsignalRAM = false, bool WritesignalRAM = false, bool LoadsignalAC = false, bool LoadsignalIR = false, bool Addsignal = false, bool Subtractsignal = false, char op = 0) {
        int address_PC;
        string ramcontent; // Holds the content read from RAM

        // Read signal for Program Counter
        if (readsignalPC) {
            addressBus.calladdressbus();
            address_PC = addressBus.getaddress_of_ProgramCounter();
        }

        // Read signal for RAM
        else if (readsignalRAM) {
            ramcontent = dataBus.getdata_Ram(ram, address_PC);
        }

        // Load signal for Instruction Register
        else if (loadsignalIR) {
            dataBus.Load_Data_Into_Instrction_Register(IR, ramcontent);
        }

        // Load signal for Accumulator
        else if (loadsignalAC) {
            dataBus.Load_Data_Into_Accumulator(AC, ram, 1);
        }

        // Add signal for ALU
        else if (addsignal) {
            dataBus.Load_Data_To_Alu(AC, alu, ram, op);
        }

        // Subtract signal for ALU
        else if (subtractsignal) {
            dataBus.Load_Data_To_Alu(AC, alu, ram, op);
        }

        // Write signal for RAM
        else if (writesignalRAM) {
            // Store the result in RAM using DataBus, previously stored in ALU temporarily
            dataBus.store_AccumulatorData(AC, ram);
        }
    }
};

