#include "../Lib/Utilities.cpp"
#include "../Lib/headers.cpp"


class Memory {
private:
      
    array<int8_t, MEMORY_SIZE> memory;    

public:
    
    Memory();


    ~Memory();

    // Write
    void write(uint8_t address, uint8_t data);
     {
    if (address >= MEMORY_SIZE) {
        throw out_of_range("Address not found\nNote memory size is 16-bit");
    }
    memory[address] = data; 
}

    // Read
    uint8_t read(uint8_t address) const;
 {
    if (address >= MEMORY_SIZE) {
        throw out_of_range("Address not found\nNote memory size is 16-bit");
    }
    return memory[address]; 
}

//Reset
void reset() {
    memory.fill(0); 

}};

