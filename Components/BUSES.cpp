#include <String>
#include <bitset>

class DataBus
{  
public:
  //IT WILL BE CALLED BY THE ACCUMUALTOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMUALTOR AND THE INSTRUCTION REGISTER
  // We jave taken the index as string so that we can use 8 bit address like for 1st location 00000000 and then used stoi function to convert it into integer in this case it would be 0 
  
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

class ControlBus

{   private:
	bool readsignal;
	bool writesignal;
	bool loadsignal;
	bool addsignal;
	bool subtractsignal;
	
	public:
	ControlBus():readsignal(1),writesignal(1),loadsignal(1),addsignal(1),subtractsignal(1){}
	
	void execute(DataBus& dataBus, AddressBus& addressBus, RAM& ram, Accumulator& accumulator,char op)
	{
	
	if(readsignal==1)
	{
	  //call the read function of the program counter of the ram using the address bus
	}
	
	else if(loadsignal==1)
	{
		// get data from ram using the data bus (getdata_ram) function and load it into the accumulator.
	}
	
	else if(writesignal==1)
	{
		
	 //call the write function of the ram along  the address bus and the data bus write functions.
		
	}
	
	if (op=='+')
	{
     (addsignal==1)
	{
	// Trigger the ALU to add the two numbers one in the accumualtor and one in the memory.
	}
    }
	else(subtractsignal==1)
	{
		// Trigger the ALU to subtract the two numbers one in the  accumualtor and one in the memoory
	}
	
	
 }
};
