#pragma once
#include "SortsInterface.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <math.h>

#include <iostream>
using namespace std;

template <typename T>
class ShellSort : public SortsInterface<T>
{
private:
	int size = 0;
	T *data = NULL;

	int sequence_option = 0;

	// Shell Sequence (N/2^k)
	int *shellSeq = NULL;
	int shellSeqSize = 0;

	// Sedgewick Sequence (4^k + 3*2^(k-1) + 1, prefixed with 1)
	int *sedgewickSeq = NULL;
	int sedgewickSeqSize = 0;

	void generateSequences()
	{
		if (this->shellSeq)
			delete[] this->shellSeq;
		if (this->sedgewickSeq)
			delete[] this->sedgewickSeq;

		// Shell Sequence (N/2^k)
		int k = 0;
		
		do
		{
			k++;
		}
		while (size > (int)pow(2, k));

		k--;

		this->shellSeqSize = k;

		this->shellSeq = new int[this->shellSeqSize];

		for (int i = 0; i < this->shellSeqSize; i++)
		{
			this->shellSeq[i] = this->size / (int)pow(2, i + 1);
		}


		// Sedgewick Sequence (4^k + 3*2^(k-1) + 1)
		k = 0;

		do
		{
			k++;
		}
		while (size > (int)(pow(4, k) + 3 * pow(2, k - 1) + 1));
		
		this->sedgewickSeq = new int[k];


		k--;

		for (int i = k; i >= 1; i--)
		{
			this->sedgewickSeq[k - i] = (int)pow(4, i) + 3 * pow(2, i - 1) + 1;
		}

		this->sedgewickSeq[k] = 1;

		this->sedgewickSeqSize = k + 1;
	}

public:
	void setData(T *newData, int newSize) override
	{
		if (this->data)
			delete[] this->data;

		this->size = newSize;
		this->data = new T[this->size];
		std::copy(newData, newData + this->size, this->data);

		generateSequences();
	}

	void sort(int choser) override
	{
		int* sequence;
		int length;

		if (choser == 1)
		{
			// Shell sequence
			sequence = this->shellSeq;
			length = shellSeqSize;
		}
		else if (choser == 2)
		{
			// Sedgewick sequence
			sequence = this->sedgewickSeq;
			length = this->sedgewickSeqSize;
		}
		else
		{
			// Default state - Shell sequence
			sequence = this->shellSeq;
			length = shellSeqSize;
		}

		for (int i = 0; i < length; i++) 
		{	
			int step = sequence[i];
			
			for (int j = step; j < size; j++) 
			{
				T key = data[j];

				int pos = j - step;

				while (pos >= 0 && data[pos] > key)
				{
					data[pos + step] = data[pos];
					pos -= step;
				}

				data[pos + step] = key;
			}

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

	~ShellSort() override
	{
		delete[] this->data;
		delete[] this->shellSeq;
		delete[] this->sedgewickSeq;
	};
};