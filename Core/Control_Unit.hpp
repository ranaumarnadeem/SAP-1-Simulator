#pragma once

#include "headers.hpp"
#include "ALU.hpp"
#include "Register.hpp"
#include "RAM.hpp"
#include "BUS.hpp"
class ControlUnit 
{
public:
	
	ControlUnit(){};
	~ControlUnit(){};
	
    void Decode_Send_Instruction(DataBus &dataBus, AddressBus &addressBus, ControlBus &controlbus, RAM &ram, Register &AC, Register &IR, ALU &alu, char op) {
        bool enable;
        // loop for 3 times as there are 3 instructions in the ram LDA, ADD/SUB, STA.
        for (int i=0; i<3; i++) 
		{
            enable = true;
            // CALLING THE EXECUTE FUNCTION TO GET THE ADDRESS.
            controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, enable, 0, 0, 0, 0, 0, 0, op);

            // CALLING THE EXECUTE FUNCTION TO GET THE CONTENT OF THE ADDRESS BROUGHT BY THE ADDRESS BUS.
            controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, enable, 0, 0, 0, 0, 0, op);

            // EXECUTE FUNCTION WHICH WILL BRING THE INSTRUCTION TO THE INSTRUCTION REGISTER THROUGH THE DATA BUS.
            controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, 0, 0, 0, enable, 0, 0, op);
             
            // CONTROL UNIT DECODING THE CONTENT OF THE INSTRUCTION REGISTER AND GENERATING SIGNAL ACCORDINGLY.
            if (IR.readIR()=="00000000") {
                // THIS INSTRUCTION MEANS TO BRING THE DATA INTO THE ACCUMULATOR.
                controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, 0, 0, enable, 0, 0, 0, op);
                // INCREMENTING THE PROGRAM COUNTER AS THE FIRST INSTRUCTION IS EXECUTED SUCCESSFULLY.
                ProgramCounter=3;
                
            }
             else if (IR.readIR() == "00000001") 
			 {
                // IF THE INSTRUCTION IS THIS IT MEANS TO ADD THE NUMBERS ONE IN THE ACCUMULATOR AND ONE IN THE RAM.
                controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, 0, 0, 0, 0, enable, 0, op);
            // INCREMENTING THE PROGRAM COUNTER AS THE 2nd  INSTRUCTION IS EXECUTED SUCCESSFULLY.
                ProgramCounter=4;
            }
            
             else if (IR.readIR() == "00000010") {
                // IF THE INSTRUCTION IS THIS IT MEANS TO SUBTRACT THE NUMBERS ONE IN THE ACCUMULATOR AND ONE IN THE RAM.
                controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, 0, 0, 0, 0, 0, enable, op);
                // INCREMENTING THE PROGRAM COUNTER AS THE 2nd INSTRUCTION IS EXECUTED SUCCESSFULLY.
                ProgramCounter=4;
            }
             
                
             if (IR.readIR() == "00000011") {
                // THIS INSTRUCTION MEANS TO STORE THE RESULT STORED TEMPORARILY IN THE ACCUMULATOR IN THE RAM.
                controlbus.execute(dataBus, addressBus, ram, AC, IR, alu, 0, 0, enable, 0, 0, 0, 0, op);
            }
     }
    }
};
