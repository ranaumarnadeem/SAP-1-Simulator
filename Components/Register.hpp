#include "../Lib/headers.cpp"
// MAKING THE PROGRAM COUNTER AS A GLOBAL STRING VARIABLE (STRING BECAUSE IT WILL STORE THE ADDRESS IN STRING FORMAT) AND GLOBAL SO THAT IT CAN BE ACCESSED BY EVERY FUNCTION THE WHERE NEEDED.
//PROGRAM COUNTER IS STORING 00000000 AS ITS FIRST INSTRUCTION WHICH IS LDA ACCORDING TO THE OPCODE.
string ProgramCounter="00000000";

class Register {
private:
	//CHANGED THE VARIABLE "data" FROM U_INT_8 TO STRING  DATA TYPE TO ENSURE UNIFORMITY THROUGHOUT THE PROGRAM.
    string data; 
    bool enable;  // enable for read
    bool load;   // Load for writing in register

public:
    
    Register() : data(""), enable(false), load(false) {}

    
    ~Register() {}

    
    void write(string value) {
        if (load) { 
            data = value;
        } else {
            throw logic_error("Load should be active to write");
        }
    }

    // Read
    string read() const {
        if (enable) { 
            return data;
        } else {
            throw logic_error("Enable should be active to read");
        }
    }

    // Reset
    void reset() {
        data = "";
        enable = false;
        load = false;
    }

    // Setter for enable
    void setEnable(bool state) {
        enable = state;
    }

    // Setter for enable
    void setLoad(bool state) {
        load = state;
    }
};

\
