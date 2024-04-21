#pragma once
#include <string>
#include <iostream>
#include <fstream>

class readArrayFile
{
private:
	int int_array_size = 0;
	int float_array_size = 0;
	int* intArray = NULL;
	float* floatArray = NULL;
public:
	int readIntArrayFile(std::string filename);
	int readFloatArrayFile(std::string filename);
	int getIntArraySize();
	int getFloatArraySize();
	int* getIntArrayPointer();
	float* getFloatArrayPointer();
	~readArrayFile();
};