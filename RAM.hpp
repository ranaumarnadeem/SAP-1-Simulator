	#include "headers.hpp"
	#include "Utilities.cpp"
	
	//global counter to keep track of the memory locations
	const int counter_ram=0;

class RAM

{
	protected:
	//  Array represents 16 memory regions of the ram in sap 1.

	string *ram = new string [MEMORY_SIZE];

	string ram[MEMORY_SIZE];

	public:
	// AT THE INDEX 0  4 5 THERE ARE INSTRUCTIONS NOT THE NUMBERS THAT WE WANT TO ADD OR THEIR RESULT 
	// AT 0 INDEX WE HAVE LDA INSTRUCTION
	// AT INDEX 4/5  WE HAVE ADD/SUBTRACTION INSTRUCTION 
	//AT INDEX 6 WE HAVE A STORE INSTRUCTION
	
	// Function to write in the memory locations
	void writeData(int num1,char op ,int num2)
	{
	// Condition to check for the valid memory regions 
	 if(counter<MEMORY_SIZE)
	 {
	 	// DEMONSTARTING LDA INSTRUCTION (LOAD THE DATA FROM MEMORY THIS MEMORY TO THE ACCUMULATOR)
	 	//bitset basically converts the decimal number to 8 bit binary number 
	 	
		ram[counter_ram]=bitset<8>(0).to_string();
		counter_ram++;
	 	ram[counter_ram]=bitset<8>(num1).to_string();
	 	counter++;
	 	ram[counter_ram]=bitset<8>(num2).to_string();
	 	
		if (op=='+')
	 	{
		// DEMONSTARTING ADD INSTRUCTION  (ADDING  THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)
		// 2 IS THE DECIMAL EQUIVLIANT OF OPCODE OF ADD INSTRUCTION WHICH IS CONVERTED TO 8 BIT BINARY USING THE BITSET<> COMMAND
		ram[counter_ram]=bitset<8>(1).to_string();
		counter_ram++;
     	}
     	
     	else if(op =='-')
     	{
     	// DEMONSTARTING SUBTRACT INSTRUCTION  (ADDING  THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)	
     	// 3 REPRESENTS THE BINARY EQUIVLANT OF HTE OPCODE OF THE SUB INSTRUCTION WHICH WOULD BE CONVERTED TO THE 8 BIT BINARY USING THE BITSET COMMAND
     	ram[counter_ram]=bitset<8>(2).to_string();
		counter_ram++;
		}
		
		else
		{
			cout << "INVLAID INSTRUCTION " << endl;
		}
		//TO STORE THE STA INSTRUCTION (STORE THE ACCUMULATOR RESULT IN THE MEMEORY.
		ram[counter_ram]=bitset<8>(3).to_string();
			counter_ram++;
	 }
}
	 
void writeresult(string result)
{
  ram[3]= result;// // HERE STORE THE ADDITION OR SUBTRACTION RESULT AT INDEX 3
}
    //Read function so that the instruction register can call the appropiate address
    
    // HERE THE ADDRESS( THE INT *PTR VARIBALE) WILL COME FROM THE PROGRAM COUNTER (ADDRESS OF THE INSTRUCTION  AND STORE THE RETURN VALUE INSIDE THE INSTRUCTION REGISTER
    
    int read(string index) const
	 {
	 	
        if (stoi[index]<=index<= stoi[index]) 
		{
            return bitset<8>(ram[stoi(index));
        } 
		else 
		{
            cout << "CAN'T ACCESS THIS MEMORY LOCATION" << endl;
        }
    }
    	
	}
	
	// destructor to deallocate dyanmically allocated array.
	
	~RAM()
	{
		delete[] ram;
	}
	
	
};

