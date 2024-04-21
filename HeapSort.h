#pragma once
#include "SortsInterface.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>

#include <iostream>
using namespace std;

template <typename T>
class HeapSort : public SortsInterface<T>
{
private:
	int size = 0;
	T *data = NULL;

	void heapify()
	{
		for (int i = size - 1; i >= 0; i--)
		{
			adjustForHeap(i, size);
		}
	}

	void adjustForHeap(int node_id, int heap_length)
	{
		int leftChild = 2 * node_id + 1;
		int rightChild = leftChild + 1;

		if (leftChild >= heap_length)
		{
			// No children
			return;
		}

		if (rightChild >= heap_length)
		{
			// Only one child (from left side)
			if (data[node_id] < data[leftChild])
			{
				// Adjustment to heap and there is NO invocation recurrently 
				// adjustForheap() becuase of it's properties
				T tmp = data[node_id];
				data[node_id] = data[leftChild];
				data[leftChild] = tmp;
			}
			else
			{
				return;
			}
		}
		else
		{
			// Both of children are present
			if (data[leftChild] > data[rightChild])
			{
				// Left child is candidate to swap with his ancestor
				if (data[node_id] < data[leftChild])
				{
					// Adjustment to heap and invocation recurrently adjustForheap()
					T tmp = data[node_id];
					data[node_id] = data[leftChild];
					data[leftChild] = tmp;

					adjustForHeap(leftChild, heap_length);
				}
			} 
			else 
			{
				// Right child is candidate to swap with his ancestor
				if (data[node_id] < data[rightChild]) 
				{
					// Adjustment to heap and invocation recurrently adjustForheap()
					T tmp = data[node_id];
					data[node_id] = data[rightChild];
					data[rightChild] = tmp;

					adjustForHeap(rightChild, heap_length);
				}
			}
		}
	}

	void deleteByOne() {
		int heap_length = size;

		while (heap_length != 1)
		{
			// Deletion of root element of maxHeap
			// Deleted element is maximum, so we gonna store him right after the end of heap
			T tmp = data[0];
			data[0] = data[heap_length - 1];
			data[heap_length - 1] = tmp;
			heap_length--;			

			// Formation of maxHeap on remaining elements
			adjustForHeap(0, heap_length);
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
		// Formation of maxHeap
		heapify();

		// Deletion of root elements one by one (actually sorting)
		deleteByOne();
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

	~HeapSort() override
	{
		delete[] this->data;
	};
};