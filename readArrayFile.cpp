#include "readArrayFile.h"

int readArrayFile::readIntArrayFile(std::string filename)
{
	std::ifstream fin;

	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "Cannot open specified file." << '\n';

		return -1;
	}
	else
	{
		std::cout << filename << " is opened succesfully." << '\n';

		fin >> this->int_array_size;

		this->intArray = new int[this->int_array_size];

		for (int i = 0; i < this->int_array_size; i++)
		{
			if (fin.eof())
			{
				return -2;
			}

			fin >> this->intArray[i];
		}

		return 0;
	}
}

int readArrayFile::readFloatArrayFile(std::string filename)
{
	std::ifstream fin;

	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "Cannot open specified file." << '\n';

		return -1;
	}
	else
	{
		std::cout << filename << " is opened succesfully." << '\n';

		fin >> this->float_array_size;

		this->floatArray = new float[this->float_array_size];

		for (int i = 0; i < this->float_array_size; i++)
		{
			if (fin.eof())
			{
				std::cout << "Test case" << '\n';
				return -2;
			}

			fin >> this->floatArray[i];
		}

		return 0;
	}
}

int readArrayFile::getIntArraySize()
{
	return this->int_array_size;
}

int *readArrayFile::getIntArrayPointer()
{
	if (this->int_array_size <= 0 || !this->intArray)
	{
		return NULL; 
	}

	int *intArrayCopy = new int[this->int_array_size];
	std::copy(this->intArray, this->intArray + this->int_array_size, intArrayCopy);
	return intArrayCopy; 
}

int readArrayFile::getFloatArraySize()
{
	return this->float_array_size;
}

float *readArrayFile::getFloatArrayPointer()
{
	if (this->float_array_size <= 0 || !this->floatArray)
	{
		return NULL; 
	}

	float *floatArrayCopy = new float[this->float_array_size];
	std::copy(this->floatArray, this->floatArray + this->float_array_size, floatArrayCopy);
	return floatArrayCopy; 
}

readArrayFile::~readArrayFile()
{
	if (this->intArray)
		delete[] this->intArray;
	if (this->floatArray)
		delete[] this->floatArray;
}
