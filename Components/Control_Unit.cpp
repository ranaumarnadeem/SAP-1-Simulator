
// using single inheritance in order to access the data memerbs of control bus 

class ControlUnit:public ControlBus
{
	public:
	
	void Decode_Send_Instruction_Register(InstructionRegister& IR,ControlBus& obj)
    {  
      // loop for 4 times as there are 4 instructions in the ram LDA,ADD/SUB,STA.
      for (int i=0;i<3;i++)
      {
        // READ SIGNAL PROGRAM COUNTER IS 1 IN ORDER TO FETCH THE FIRST INSTRUCTION ADDRESS AS THE PROGRAM STARTS THE FIRST THING IS TO FETCH THE PORGRAM COUNTER CONTENT.
        
        readsignalPC=1;
        
        //CALLING THE EXECUTE FUNCTION (SO THAT THE ADDRESS BUS CAN BRING THE ADDRESS TO THE RAM) TO GET THE ADDRESS.
        
        obj.execute(dataBus,addressBus,ram,AC,IR,readsignalPC,0,0,0,0,0,0);
        
        //READ SIGNAL RAM IN ORDER TO FETCH THE CONTENT OF THE RAM AT THE ADDRESS GIVEN BY THE PROGRAM COUNTER THORUGH THE ADDRESS BUS.
        
        readsignalRAM=1;
        
        // CALLING THE EXECUTE FUNCTION TO GET THE CONTENT OF THE ADDRESS BROUGHT BY THE ADDRESS BUS.
        
        obj.execute(dataBus,addressBus,ram, AC, IR,0,readsignalRAM,0,0,0,0,0);
        
        // LOAD SINGAL IN ORDER TO LOAD THE INSTRUCTION INTO THE INSTRUCTION REGISTER 
    
        loadsignalIR=1;
        
        // EXECUTE FUNCTION WHICH WILL BRING THE INSTRUCTION TO THE INSTRUCTION REGISTER THROUGH THE DATA BUS.
        
        obj.execute(dataBus,addressBus,ram, AC, IR,0,0,0,0,loadsignalIR,0,0);
        
        //CONTROL UNIT DECODING THE CONTENT OF THE INSTRUCTION REGISTER AND GENERATING SIGNAL ACCORDINGLY.
        
    	if(IR.instrcutionregister=="00000000")
    	{
    		// THIS INSTRUCTION MEANS TO BRING THE DATA INTO THE ACCUMULATOR.
    		
    		loadsignalAC=1;
    		// EXECUTE WILL BRING THE DATA INTO THE ACCUMUALTOR THROUGH THE DATA BUS.
    		
    		obj.execute(dataBus,addressBus,ram, AC, IR,0,0,0,loadsignalAC,0,0,0);
		}
		
		else if(IR.instrcutionregister=="00000001")
    	{
    		// IF THE INSTRUCTION IS THIS IT MEANS TO ADD THE NUMBERS ONE IN THE ACCUMUALTOR AND ONE IN THE RAM 
    		
    		addsignal=1;
    		obj.execute(dataBus,addressBus,ram, AC, IR,0,0,0,0,0,0,0);
		}
		
		else if(IR.instrcutionregister=="00000010")
    	{
    		// IF THE INSTRUCTION IS THIS IT MEANS TO SUBTRACT THE NUMBERS ONE IN THE ACCUMUALTOR AND ONE IN THE RAM.
    		subtractsignal=1;
    		obj.execute(dataBus,addressBus,ram, AC, IR,0,0,0,0,0,0,subtractsignal);
		}
		
		 else if(IR.instrcutionregister=="00000011")
    	{
    		// THIS INSTRUCTION MEASN TO STORE THE RESULT STORED TEMPERORLIY IN THE ACCUMUALOTR IN THE RAM .
    		writesignalRAM=1;
    		obj.execute(dataBus,addressBus,ram, AC, IR,0,0,writesignalRAM,0,0,0,0);
		}
		
		// INCREMENT THE PROGRAM COUNTER HERE 
        
	}
    }	
};
