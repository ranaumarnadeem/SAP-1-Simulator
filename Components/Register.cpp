#include "../Lib/headers.cpp"

class Register {
private:
    uint8_t data; 
    bool enable;  // enable for read
    bool load;   // Load for writing in register

public:
    
    Register() : data(0), enable(false), load(false) {}

    
    ~Register() {}

    
    void write(uint8_t value) {
        if (load) { 
            data = value;
        } else {
            throw logic_error("Load should be active to write");
        }
    }

    // Read
    uint8_t read() const {
        if (enable) { 
            return data;
        } else {
            throw logic_error("Enable should be active to read");
        }
    }

    // Reset
    void reset() {
        data = 0;
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
