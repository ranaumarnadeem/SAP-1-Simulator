#include "./headers.hpp"
#include <bitset>
#define MEMORY_SIZE 16

string toBinary(uint8_t num, int bits = 8) {
    return bitset<8>(num).to_string().substr(8 - bits);
}

