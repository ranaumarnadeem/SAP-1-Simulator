#include "headers.hpp"
#include "ALU.hpp"
#include "Register.hpp"
#include "RAM.hpp"

class DataBus
{
public:
	// IT WILL BE CALLED BY THE ACCUMULATOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMULATOR AND THE INSTRUCTION REGISTER
	// We have taken the index as string so that we can use 8-bit address like for 1st location 00000000
	// and then used stoi function to convert it into integer; in this case, it would be 0.
	int getdata_Ram(RAM &obj, string index) const
	{
		return obj.read(to_string(stoi(index)));
	}

	// THIS WILL BE CALLED BY THE ALU AND THE RAM TO GET THE ACCUMULATOR CONTENT
	int get_AccumulatorData(Register &AC) const
	{
		return stoi(AC.read());
	}
};

class AddressBus
{
public:
	// THIS WILL BE USED TO ACCESS THE CONTENT OF THE RAM
	// RETURN TYPE IS STRING SINCE THE ADDRESS WOULD BE IN STRING TYPE REPRESENTING A BINARY VALUE
	// FOR EXAMPLE 00000000 WHICH IS STORED AS A STRING
	string getaddress_of_ProgramCounter() const
	{
		return ProgramCounter;
	}

private:
	string ProgramCounter;
};

class ControlBus
{
public:
	// Control signals for different components
	bool readsignalPC;
	bool readsignalRAM;
	bool writesignalRAM;
	bool loadsignalAC;
	bool loadsignalIR;
	bool addsignal;
	bool subtractsignal;

	// Constructor to initialize all control signals to false
	ControlBus()
		: readsignalPC(false), readsignalRAM(false), writesignalRAM(false),
		  loadsignalAC(false), loadsignalIR(false), addsignal(false), subtractsignal(false) {}

	// EXECUTE FUNCTION THAT CONTROLS THE FLOW OF DATA AND OPERATIONS BETWEEN COMPONENTS
	void execute(DataBus &dataBus, AddressBus &addressBus, RAM &ram, Register &AC, Register &IR,
				 bool readsignalPC = false, bool readsignalRAM = false, bool writesignalRAM = false,
				 bool loadsignalAC = false, bool loadsignalIR = false, bool addsignal = false, bool subtractsignal = false)
	{
		string address_PC; // Holds the program counter address
		string ramcontent; // Holds the content read from RAM

		// Read signal for Program Counter
		if (readsignalPC)
		{
			address_PC = addressBus.getaddress_of_ProgramCounter();
		}

		// Read signal for RAM
		else if (readsignalRAM)
		{
			ramcontent = to_string(dataBus.getdata_Ram(ram, address_PC));
		}

		// Load signal for Instruction Register
		else if (loadsignalIR)
		{
			IR.write(ramcontent);
		}

		// Load signal for Accumulator
		else if (loadsignalAC)
		{
			int address = stoi(ramcontent) + 1;				// Convert string to integer and increment
			string newAddress = to_string(address);			// Convert the incremented integer back to string
			AC.write(to_string(dataBus.getdata_Ram(ram, newAddress))); // Pass the updated string to getdata_Ram
		}

		// Add signal for ALU
		else if (addsignal)
		{
			// Perform addition using ALU and store result in Accumulator
			uint8_t add = alu.add(operand1, operand2);
			AC.write(bitset<8>(add).to_string());
		}

		// Subtract signal for ALU
		else if (subtractsignal)
		{
			// Perform subtraction using ALU and store result in Accumulator
			uint8_t sub = alu.subtract(operand1, operand2);
			AC.write(bitset<8>(sub).to_string());
		}

		// Write signal for RAM
		else if (writesignalRAM)
		{
			// Store the result in RAM using DataBus, previously stored in ALU temporarily
			ram.writeresult(std::to_string(dataBus.get_AccumulatorData(AC)));
		}
	}

private:
	uint8_t operand1; // First operand for ALU
	uint8_t operand2; // Second operand for ALU
	ALU alu;		  // ALU instance for arithmetic operations
};
