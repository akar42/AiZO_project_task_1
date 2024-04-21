#pragma once
#include "SortsInterface.h"
#include <cstring>
#include <algorithm>

template <typename T>
class InsertSort : public SortsInterface<T>
{
private:
	int size = 0;
	T *data = NULL;

public:
	void setData(T *newData, int newSize) override
	{
		if (this->data)
			delete[] this->data;

		this->size = newSize;
		this->data = new T[this->size];
		std::copy(newData, newData + this->size, this->data);
	}

	void sort(int choser) override
	{
		for (int i = 1; i < size; i++)
		{
			T key = data[i];
			int j = i - 1;

			while (data[j] > key && j >= 0)
			{
				data[j + 1] = data[j];
				j--;
			}

			data[j + 1] = key;
		}
	}

	T *getData() override
	{
		if (this->size <= 0 || !this->data)
		{
			return NULL;
		}

		T *dataCopy = new T[this->size];
		std::copy(this->data, this->data + this->size, dataCopy);
		return dataCopy;
	}

	~InsertSort() override
	{
		delete[] this->data;
	};
};