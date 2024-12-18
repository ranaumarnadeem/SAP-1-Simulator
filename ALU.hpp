#include "headers.hpp"

class ALU {
private:
    uint8_t result;    
    bool zeroFlag;    //Zero flag

public:
    ALU() : result(0), zeroFlag(false) {}

    // addition
    uint8_t add(uint8_t operand1, uint8_t operand2) {
        result = operand1 + operand2;
        updateZeroFlag();
        return result;
    }

    //  subtraction
    uint8_t subtract(uint8_t operand1, uint8_t operand2) {
        result = operand1 - operand2;
        updateZeroFlag();
        return result;
    }

    //  result
    uint8_t getResult() const {
        return result;
    }

    // zero flag
    bool isZero() const {
        return zeroFlag;
    }

    // Resets
    void reset() {
        result = 0;
        zeroFlag = false;
    }

private:
    // zero flag based on result
    void updateZeroFlag() {
        zeroFlag = (result == 0);
    }
};
