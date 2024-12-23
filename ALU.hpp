#ifndef ALU_HPP
#define ALU_HPP

#include "headers.hpp"

#include "Register.hpp"
#include "RAM.hpp"

class ALU {
private:
    static uint8_t result;

public:
    // addition
    void add(uint8_t operand1, uint8_t operand2) {
        result = operand1 + operand2;
    }

    // subtraction
    void subtract(uint8_t operand1, uint8_t operand2) {
        result = operand1 - operand2;
    }
};
uint8_t ALU::result = 0;


#endif