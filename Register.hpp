#pragma once

#include "headers.hpp"

class Register {
protected:
    // CHANGED THE VARIABLE "data" FROM UINT_8 TO STRING DATA TYPE TO ENSURE UNIFORMITY THROUGHOUT THE PROGRAM.
    static string data;

public:
    // Write
    void write(string value) {
        data = value;
    }

    // Read
    string read() const {
        return data;
    }
};

string Register::data = "";
