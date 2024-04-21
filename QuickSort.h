#pragma once
#include "SortsInterface.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>

#include <iostream>

using namespace std;

template <typename T>
class QuickSort : public SortsInterface<T>
{
private:
	int size = 0;
	T *data = NULL;
	int pivot_option = 0;

	int pivotChoser(int low, int high)
	{
		if (pivot_option == 1)
		{
			// Left pivot
			return low;
		}
		else if (pivot_option == 2)
		{
			// Right pivot
			return high;
		}
		else if (pivot_option == 3)
		{
			// Center Pivot
			return (low + high) / 2;
		}
		else if (pivot_option == 4)
		{
			// Random pivot
			return rand() % ((high + 1) - low) + low;
		}
		else
		{
			// Defualt - left pivot
			return low;
		}
	}

	int partition(int low, int high)
	{
		int pivot_index = pivotChoser(low, high);
		T pivot = data[pivot_index];

		// Swaping Left element with pivot
		T tmp = data[pivot_index];
		data[pivot_index] = data[low];
		data[low] = tmp;

		int i = low;
		int j = high + 1;


		while (i < j)
		{
			do
			{
				i++;
			} while (data[i] <= pivot && i != high);

			do
			{
				j--;
			} while (data[j] >= pivot && j != low);

			if (i < j)
			{
				T tmp = data[j];
				data[j] = data[i];
				data[i] = tmp;
			}
		}

		tmp = data[j];
		data[j] = data[low];
		data[low] = tmp;

		return j;
	}

	void quickSort(int low, int high)
	{
		if (low < high)
		{
			int pivot_pos = partition(low, high);
			quickSort(low, pivot_pos - 1);
			quickSort(pivot_pos + 1, high);
		}
	}

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
		pivot_option = choser;
		quickSort(0, size - 1);
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

	~QuickSort() override
	{
		delete[] this->data;
	};
};