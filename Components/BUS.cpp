#include "../Lib/headers.cpp"
class DataBus
{  
public:
  //IT WILL BE CALLED BY THE ACCUMUALTOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMUALTOR AND THE INSTRUCTION REGISTER
  // We have taken the index as string so that we can use 8 bit address like for 1st location 00000000 and then used stoi function to convert it into integer in this case it would be 0 
  
  int getdata_Ram(RAM obj,string index )
  {
  	return obj.ram[stoi(index)];
  }
  
  //THIS FUNCTION  WILL BE CALLED BY THE CONTROL UNIT IN ORDER TO DECODE THE INSTRUCTION AND GENERATE APPROPIATE CONTROL SIGNAL
  
  int getdata_InstructionRegister(Register obj)
  {
  	return obj.InstructioRegister;
  }
  // THIS WILL BE CALLED BY THE ALU AND THE RAM to get the accumulator content
  int get_AccumulatorData(Register obj)
  {
  	return obj.Accumulator;
  }
};


class AddressBus
{

  public:
  //THIS WILL BE USED TO ACCESS THE CONTENT OF THE RAM 
  //RETURN TYPE IS INT SINCE THE ADDRESS WOULD BE IN INT TYPE NOT IN HEXADECIMAL AS WE WILL RPERESENT THE ADDRESSS IN THE BINARY VALUE FOR EXAMPLE 00000000 WHICH WOULD BE STORED AS A STRING
  
  int getaddress_of_ProgramCounter(Register obj)  
  {
  	return obj.ProgramCounter;
  }
  
  int getaddress_of_RAM(RAM obj,string index)
  {
  	return obj.ram[stoi(index)];
  }
  
};

class ControlBus {
private:
    bool readsignal;
    bool writesignal;
    bool loadsignal;
    bool addsignal;
    bool subtractsignal;

public:
    ControlBus() : readsignal(1), writesignal(1), loadsignal(1), addsignal(1), subtractsignal(1) {}

    void execute(DataBus& dataBus, AddressBus& addressBus, RAM& ram, Register& accumulator, ALU& alu, char op) {
    if (readsignal) {
        // Reading from ram
        uint8_t address = addressBus.getaddress_of_ProgramCounter(accumulator);
        uint8_t data = ram.read(to_string(address));
        cout << "Data read from RAM: " << data << endl;
    }

    if (loadsignal) {
        // loading data to accumaltor
        uint8_t address = addressBus.getaddress_of_ProgramCounter(accumulator);
        uint8_t data = dataBus.getdata_Ram(ram, to_string(address));
        accumulator.write(data);
        cout << "Data loaded into accumulator: " << static_cast<int>(data) << endl;
    }

    if (writesignal) {
        // Writing data from accumalator in ram
        uint8_t address = addressBus.getaddress_of_ProgramCounter(accumulator);
        uint8_t data = accumulator.read();
        ram.write(data);
        cout << "Data written to RAM: " << static_cast<int>(data) << endl;
    }

    if (op == '+' && addsignal) {
        // Perform addition using the ALU
        uint8_t operand1 = accumulator.read();
        uint8_t address = addressBus.getaddress_of_ProgramCounter(accumulator);
        uint8_t operand2 = dataBus.getdata_Ram(ram, to_string(address));
        uint8_t result = alu.add(operand1, operand2);
        accumulator.write(result);
        cout << "Addition result: " << static_cast<int>(result) << endl;
    }

    if (op == '-' && subtractsignal) {
        // Perform subtraction using the ALU
        uint8_t operand1 = accumulator.read();
        uint8_t address = addressBus.getaddress_of_ProgramCounter(accumulator);
        uint8_t operand2 = dataBus.getdata_Ram(ram, to_string(address));
        uint8_t result = alu.subtract(operand1, operand2);
        accumulator.write(result);
        cout << "Subtraction result: " << static_cast<int>(result) << endl;
    }
}
};