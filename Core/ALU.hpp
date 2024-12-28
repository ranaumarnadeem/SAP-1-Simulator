#ifndef ALU_HPP
#define ALU_HPP

#include "headers.hpp"

#include "Register.hpp"
#include "RAM.hpp"
class ALU {
private:
    static int result;

public:
	ALU(){};
	~ALU(){};
    // addition
    int add(int operand1, int operand2) {
        result = operand1 + operand2;
        return result;
    }

    // subtraction
    int subtract(int operand1, int operand2) {
        result = operand1 - operand2;
        return result;
    }
};
int ALU::result = 0;


#endif
