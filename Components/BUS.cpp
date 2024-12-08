#include "../Lib/headers.cpp"
class DataBus
{  
public:
  //IT WILL BE CALLED BY THE ACCUMUALTOR AND INSTRUCTION REGISTER AND STORE IT IN THE ACCUMUALTOR AND THE INSTRUCTION REGISTER
  // We Have taken the index as string so that we can use 8 bit address like for 1st location 00000000 and then used stoi function to convert it into integer in this case it would be 0 
  
  int getdata_Ram(RAM obj,string index )
  {
  	return obj.read(stoi(index));
  }
  
  // THIS WILL BE CALLED BY THE ALU AND THE RAM to get the accumulator content
  int get_AccumulatorData(Accumualtor AC)
  {
  	return obj.Accumulator;
  }
  
  
  
  
};


class AddressBus
{

  public:
  //THIS WILL BE USED TO ACCESS THE CONTENT OF THE RAM 
  //RETURN TYPE IS INT SINCE THE ADDRESS WOULD BE IN INT TYPE NOT IN HEXADECIMAL AS WE WILL RPERESENT THE ADDRESSS IN THE BINARY VALUE FOR EXAMPLE 00000000 WHICH WOULD BE STORED AS A STRING
  
  string getaddress_of_ProgramCounter(ProgramCounter obj)  
  {
  	return obj.ProgramCounter;
  }
  
};

class ControlBus

{   public:
	bool readsignalPC;
    bool readsignalRAM;
	bool writesignalRAM;
	bool loadsignalAC;
	bool loadsignalIR;
	bool addsignal;
	bool subtractsignal;
	
	public:
	ControlBus():readsignal(1),writesignal(1),loadsignal(1),addsignal(1),subtractsignal(1){}
	
	void execute(DataBus& dataBus, AddressBus& addressBus, RAM& ram, Accumulator& AC,InstructionRegister& IR,ProgramCounter& PC,bool readsignalPC=0,bool readsignalRAM=0,bool writesignalRAM=0,bool loadsignalAC=0,	bool loadsignalIR=0,bool addsignal=0,bool subtractsignal=0)
	{
	
	if(readsignalPC==1)
	{
	  static string address_PC=addressBus.getaddress_of_ProgramCounter(PC);
	}
	
	else if(readsignalRAM==1)
	{
	  static string ramcontent=dataBus.getdata_Ram(ram,stoi(address_PC);
	}
	else if(loadsignalIR==1)
	{
		IR.instrcutionregister=dataBus.getdata_Ram(ram,stoi(address_PC);
	}
     else if(loadsignalAC==1)
	{
		  static AC.accumualtor=dataBus.getdata_Ram(ram,stoi(ramcontent)+1);
		
	}

    else if (addsignal==1)
	{
	  static uint8_t add =alu.add(operand1, operand2);
	  static AC.accumulator=bitset<8>(add);
	}
	else if(subtractsignal==1)
	{
	static uint8_t sub=alu.subtract (operand1, operand2);
	static AC.accumulator=bitset<8>(sub);
	}
	
	}
    else if(writesignalRAM==1)
    // stroign the result int the ram using data bus which was stored inside the alu temprorily.
    
	{
	static ram.writeresult(get_AccumulatorData(Register obj));
		
	}
	

};
