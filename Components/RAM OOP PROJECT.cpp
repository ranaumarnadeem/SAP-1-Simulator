	//global counter to keep track of the memory locations
	const int counter_ram=0;

class RAM

{
	protected:
	//  Array represents 16 memory regions of the ram in sap 1.
	string ram[16];

	public:
	// AT THE INDEX 0  4 5 THERE ARE INSTRUCTIONS NOT THE NUMBERS THAT WE WANT TO ADD OR THEIR RESULT 
	// AT 0 INDEX WE HAVE LDA INSTRUCTION
	// AT INDEX 4 WE HAVE ADD INSTRUCTION 
	//AT INDEX 5 WE HAVE SUB INSTURCTION 
	
	// Function to write in the memory locations
	void write(int num1,char op ,int num2)
	{
	// Condition to check for the valid memory regions 
	 if(counter<16)
	 {
	 	// DEMONSTARTING LDA INSTRUCTION (LOAD THE DATA FROM MEMORY THIS MEMORY TO THE ACCUMULATOR)
	 	//bitset basically converts the decimal number to 8 bit binary number 
	 	//to_ulong basically converts that binary number into a integer format
	 	
		ram[counter_ram]=bitset<8>(1).to_string();
			counter_ram++;
	 	ram[counter_ram]=bitset<8>(num1).to_string();
	 	counter++;
	 	ram[counter_ram]=bitset<8>(num2).to_string();
	 	
		if (op=='+')
	 	{
		// DEMONSTARTING ADD INSTRUCTION  (ADDING  THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)
		// 2 IS THE DECIMAL EQUIVLIANT OF OPCODE OF ADD INSTRUCTION WHICH IS CONVERTED TO 8 BIT BINARY USING THE BITSET<> COMMAND
		ram[counter_ram]=bitset<8>(2).to_string();
		counter_ram++;
     	}
     	
     	else if('-')
     	{
     	// DEMONSTARTING SUBTRACT INSTRUCTION  (ADDING  THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)	
     	// 3 REPRESENTS THE BINARY EQUIVLANT OF HTE OPCODE OF THE SUB INSTRUCTION WHICH WOULD BE CONVERTED TO THE 8 BIT BINARY USING THE BITSET COMMAND
     	ram[counter_ram]=bitset<8>(3).to_string();
		counter_ram++;
		}
		
		else
		{
			cout << "INVLAID INSTRUCTION " << endl;
		}
		
		void writetotal()
		{
			ram[counter_ram]= // // HERE STORE THE ADDITION OR SUBTRACTION RESULT IN  
		}
	
	 }
	 
	 else
	 {
	 	cout << "INVALID MEMORY ACCESS " << endl;
	 }
	
    //Read function so that the instruction register can call the appropiate address
    
    // HERE THE ADDRESS( THE INT *PTR VARIBALE) WILL COME FROM THE PROGRAM COUNTER (ADDRESS OF THE INSTRUCTION  AND STORE THE RETURN VALUE INSIDE THE INSTRUCTION REGISTER
    
    int read(string index)
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
};
