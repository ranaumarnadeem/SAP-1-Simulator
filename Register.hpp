#pragma once

#include "headers.hpp"

class Register 
{
protected:
    // CHANGED THE VARIABLE "data" FROM UINT_8 TO STRING DATA TYPE TO ENSURE UNIFORMITY THROUGHOUT THE PROGRAM.
     static string dataAC;
     static string dataIR;

public:
	
	Register(){};
	~Register(){}
    // Write
    void writeAC(string value) 
	{
        dataAC=value;
    }
    
    void writeIR(string value)
    {
    	dataIR=value;
	}

    // Read
    string readAC() const {
        return dataAC;
    }
    
    string readIR() const
    {
    	return dataIR;
	}
};
string Register::dataAC = "";
string Register::dataIR="";
