	#include "headers.hpp"
	#include "Utilities.cpp"
	
class RAM {
protected:
    // Array represents 16 memory regions of the RAM in SAP 1.
    string* ram = new string[MEMORY_SIZE];

public:
    // Function to write in the memory locations
    void writeData(int num1, char op, int num2) {
        // Condition to check for the valid memory regions 
        if (counter_ram < MEMORY_SIZE) {
            // DEMONSTRATING LDA INSTRUCTION (LOAD THE DATA FROM MEMORY TO THE ACCUMULATOR)
            ram[counter_ram] = bitset<8>(0).to_string();
            counter_ram++;
            ram[counter_ram] = bitset<8>(num1).to_string();
            counter_ram++;
            ram[counter_ram] = bitset<8>(num2).to_string();
            counter_ram++;

            if (op == '+') {
                // DEMONSTRATING ADD INSTRUCTION (ADDING THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)
                ram[counter_ram] = bitset<8>(1).to_string();
                counter_ram++;
            }
            else if (op == '-') {
                // DEMONSTRATING SUBTRACT INSTRUCTION (ADDING THE NUMBERS IN THE ACCUMULATOR AND IN THE MEMORY ADDRESS)  
                ram[counter_ram] = bitset<8>(2).to_string();
                counter_ram++;
            }
            else {
                cout << "INVALID INSTRUCTION " << endl;
            }

            // TO STORE THE STA INSTRUCTION (STORE THE ACCUMULATOR RESULT IN THE MEMORY)
            ram[counter_ram] = bitset<8>(3).to_string();
            counter_ram++;
        }
    }

    void writeresult(string result) {
        ram[5] = result; // HERE STORE THE ADDITION OR SUBTRACTION RESULT AT INDEX 5
    }

    // Read function so that the instruction register can call the appropriate address
    string read(int index) const {
        if (index < 0 || index >= MEMORY_SIZE) {
            cout << "TRYING TO ACCESS INVALID MEMORY LOCATION" << endl;
        }
        else {
            string temp = bitset<8>(index).to_string();
            cout << "THE CONTENT AT MEMORY LOCATION " << temp << " IS " << ram[index] << endl;
            return ram[index];
        }
    }

    // Destructor to deallocate dynamically allocated array.
    ~RAM() {
        delete[] ram;
    }
};

