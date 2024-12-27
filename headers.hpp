#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
//#include "../Components/ALU.cpp"
//#include "../Components/Control_Unit.cpp"
//#include "../Components/Register.cpp"
//#include "../Components/RAM.cpp"
#include <array>
#include <bitset>


using namespace std;

//global counter to keep track of the memory locations
int counter_ram = 0;
// MAKING THE PROGRAM COUNTER AS A GLOBAL STRING VARIABLE (STRING BECAUSE IT WILL STORE THE ADDRESS IN STRING FORMAT) AND GLOBAL SO THAT IT CAN BE ACCESSED BY EVERY FUNCTION WHERE NEEDED.
int ProgramCounter = 0;

#endif
