#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>

#include "InsertSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "ShellSort.h"

#include "readArrayFile.h"

using namespace std;

// Data-generating functions

// All elements of array are random
template <typename T>
T *generateRandomOrdered(int size);

// Simply sorted array
template <typename T>
T *generateAscendingOrder(int size);

// Sorted in descending order
template <typename T>
T *generateDescendingOrder(int size);

// Sorted first 33% of array
template <typename T>
T *generate33percentSorted(int size);

// Sorted first 66% of array
template <typename T>
T *generate66percentSorted(int size);

template <typename T>
bool checkIfSorted(T *data_ptr, int size);

int main()
{
	srand(time(NULL));
	// For int data type
	SortsInterface<int> **sortMethodsInt = new SortsInterface<int> *[4];
	sortMethodsInt[0] = new InsertSort<int>();
	sortMethodsInt[1] = new QuickSort<int>();
	sortMethodsInt[2] = new HeapSort<int>();
	sortMethodsInt[3] = new ShellSort<int>();

	// Int array pointer and size
	int *int_data_ptr = NULL;
	int int_data_size = 0;

	// Int array after sorting
	int *output_int_data_ptr = NULL;
	int output_int_data_size = 0;

	// For float data type
	SortsInterface<float> **sortMethodsFloat = new SortsInterface<float> *[4];
	sortMethodsFloat[0] = new InsertSort<float>();
	sortMethodsFloat[1] = new QuickSort<float>();
	sortMethodsFloat[2] = new HeapSort<float>();
	sortMethodsFloat[3] = new ShellSort<float>();

	// Float array pointer and size
	float *float_data_ptr = NULL;
	int float_data_size = 0;

	// Float array after sorting
	float *output_float_data_ptr = NULL;
	int output_float_data_size = 0;

	// Read file object
	readArrayFile raf;

	int main_menu_option = 1;

	// 1 - int, 2 - float
	int data_type_option = 0;

	while (main_menu_option)
	{
		main_menu_option = 0;

		cout << "\nChoose one option:\n";
		cout << "1 - Read data from file\n";
		cout << "2 - Generate data\n";
		cout << "3 - Show unsorted data\n";
		cout << "4 - Sort data\n";
		cout << "5 - Show sorted data\n";
		cout << "0 - Exit\n";
		cout << "> ";

		cin >> main_menu_option;

		if (main_menu_option == 1)
		{
			int read_file_menu = 0;
			string filename;

			cout << "\n1 - Read data from file:\n";
			cout << "Enter text file name > ";
			cin >> filename;

			cout << "Choose array elements' data type:\n";
			cout << "1 - int\n";
			cout << "2 - float\n";
			cout << "0 - Exit\n";
			cout << "> ";

			cin >> read_file_menu;

			if (read_file_menu == 1)
			{
				int err_code = raf.readIntArrayFile(filename);

				if (err_code == -1)
				{
					cout << "Check spelling of filename.\n";
					cout << "Data hasn't been readen\n";
				}
				else if (err_code == -2)
				{
					cout << "Size missmatch in file - data array is shorter then declared.\n";
					cout << "Data hasn't been readen\n";
				}
				else
				{
					if (int_data_ptr || int_data_size)
						delete[] int_data_ptr;

					if (output_int_data_ptr || output_int_data_size)
					{
						delete[] output_int_data_ptr;
						output_int_data_ptr = NULL;
					}

					int_data_ptr = raf.getIntArrayPointer();
					int_data_size = raf.getIntArraySize();

					data_type_option = 1;
				}
			}
			else if (read_file_menu == 2)
			{
				int err_code = raf.readFloatArrayFile(filename);

				if (err_code == -1)
				{
					cout << "Check spelling of filename.\n";
					cout << "Data hasn't been readen\n";
				}
				else if (err_code == -2)
				{
					cout << "Size missmatch in file - data array is shorter then declared.\n";
					cout << "Data hasn't been readen\n";
				}
				else
				{
					if (float_data_ptr || float_data_size)
						delete[] float_data_ptr;

					if (output_float_data_ptr || output_float_data_size)
					{
						delete[] output_float_data_ptr;
						output_float_data_ptr = NULL;
					}

					float_data_ptr = raf.getFloatArrayPointer();
					float_data_size = raf.getFloatArraySize();

					data_type_option = 2;
				}
			}
		}
		else if (main_menu_option == 2)
		{
			int generate_data_menu = 0;
			int choosed_data_type = 0;
			int size;

			cout << "\n2 - Generate data:\n";
			cout << "Choose generation option:\n";
			cout << "1 - All elements of array are random\n";
			cout << "2 - Sorted array\n";
			cout << "3 - Sorted in descending order\n";
			cout << "4 - Sorted first 33\% of array\n";
			cout << "5 - Sorted first 66\% of array\n";
			cout << "> ";

			cin >> generate_data_menu;

			cout << "Enter size of array > ";

			cin >> size;

			cout << "Choose array elements' data type:\n";
			cout << "1 - int\n";
			cout << "2 - float\n";
			cout << "0 - Exit\n";
			cout << "> ";

			cin >> choosed_data_type;

			if (choosed_data_type == 1)
			{
				data_type_option = 1;

				if (int_data_ptr || int_data_size)
				{
					delete[] int_data_ptr;
					int_data_ptr = NULL;
				}

				if (output_int_data_ptr || output_int_data_size)
				{
					delete[] output_int_data_ptr;
					output_int_data_ptr = NULL;
				}

				int_data_size = size;

				if (generate_data_menu == 1)
				{
					int_data_ptr = generateRandomOrdered<int>(size);
				}
				else if (generate_data_menu == 2)
				{
					int_data_ptr = generateAscendingOrder<int>(size);
				}
				else if (generate_data_menu == 3)
				{
					int_data_ptr = generateDescendingOrder<int>(size);
				}
				else if (generate_data_menu == 4)
				{
					int_data_ptr = generate33percentSorted<int>(size);
				}
				else if (generate_data_menu == 5)
				{
					int_data_ptr = generate66percentSorted<int>(size);
				}
			}
			else if (choosed_data_type == 2)
			{
				data_type_option = 2;

				if (float_data_ptr || float_data_size)
				{
					delete[] float_data_ptr;
					float_data_ptr = NULL;
				}
				if (output_float_data_ptr || output_float_data_size)
				{
					delete[] output_float_data_ptr;
					output_float_data_ptr = NULL;
				}

				float_data_size = size;

				if (generate_data_menu == 1)
				{
					float_data_ptr = generateRandomOrdered<float>(size);
				}
				else if (generate_data_menu == 2)
				{
					float_data_ptr = generateAscendingOrder<float>(size);
				}
				else if (generate_data_menu == 3)
				{
					float_data_ptr = generateDescendingOrder<float>(size);
				}
				else if (generate_data_menu == 4)
				{
					float_data_ptr = generate33percentSorted<float>(size);
				}
				else if (generate_data_menu == 5)
				{
					float_data_ptr = generate66percentSorted<float>(size);
				}
			}
		}
		else if (main_menu_option == 3)
		{
			if (data_type_option == 1)
			{
				cout << "[\t";
				for (int i = 0; i < int_data_size; i++)
				{
					cout << int_data_ptr[i] << '\t';
				}
				cout << "]\n";
			}
			else if (data_type_option == 2)
			{
				cout << "[\t";
				for (int i = 0; i < float_data_size; i++)
				{
					cout << float_data_ptr[i] << '\t';
				}
				cout << "]\n";
			}
			else
			{
				cout << "There is nothing to show. Read data from file or generate it first\n";
			}
		}
		else if (main_menu_option == 4)
		{
			int sort_algorytm_menu = -1;
			int specific_options = 0;

			cout << "\n4 - Sort data:\n";
			cout << "Choose sorting algorithm:\n";
			cout << "1 - Insert Sort\n";
			cout << "2 - Quick Sort\n";
			cout << "3 - Heap Sort\n";
			cout << "4 - Shell Sort\n";
			cout << "0 - Exit\n";
			cout << "> ";

			cin >> sort_algorytm_menu;

			if (sort_algorytm_menu != 0)
			{
				if (sort_algorytm_menu == 2)
				{
					cout << "Choose pivot position:\n";
					cout << "1 - Left\n";
					cout << "2 - Right\n";
					cout << "3 - Center\n";
					cout << "4 - Random\n";
					cout << "> ";

					cin >> specific_options;
				}
				else if (sort_algorytm_menu == 4)
				{
					cout << "Choose gap sequence:\n";
					cout << "1 - Shell Sequence (N/2^k)\n";
					cout << "2 - Sedgewick Sequence (4^k + 3 * 2^(k - 1) + 1, prefixed with 1)\n";
					cout << "> ";

					cin >> specific_options;
				}

				if (data_type_option == 1)
				{
					sortMethodsInt[sort_algorytm_menu - 1]->setData(int_data_ptr, int_data_size);
					std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
					sortMethodsInt[sort_algorytm_menu - 1]->sort(specific_options);
					std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> delta = end - start;
					cout << "Duration: " << delta.count() << " ms" << '\n';

					cout << "Checking if correctly sorted: ";

					output_int_data_ptr = sortMethodsInt[sort_algorytm_menu - 1]->getData();
					output_int_data_size = int_data_size;

					if (checkIfSorted(output_int_data_ptr, output_int_data_size))
					{
						cout << "OK\n";
					}
					else
					{
						cout << "Incorrect\n";
					}
				}
				else if (data_type_option == 2)
				{
					sortMethodsFloat[sort_algorytm_menu - 1]->setData(float_data_ptr, float_data_size);
					std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
					sortMethodsFloat[sort_algorytm_menu - 1]->sort(specific_options);
					std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> delta = end - start;
					cout << "Duration: " << delta.count() << " ms" << '\n';

					cout << "Checking if correctly sorted: ";

					output_float_data_ptr = sortMethodsFloat[sort_algorytm_menu - 1]->getData();
					output_float_data_size = float_data_size;

					if (checkIfSorted(output_float_data_ptr, output_float_data_size))
					{
						cout << "OK\n";
					}
					else
					{
						cout << "Incorrect\n";
					}
				}
				else
				{
					cout << "There is nothing to sort. Read data from file or generate it first\n";
				}
			}
		}

		else if (main_menu_option == 5)
		{
			if (data_type_option == 1)
			{
				if (output_int_data_ptr && output_int_data_size)
				{
					cout << "[\t";
					for (int i = 0; i < output_int_data_size; i++)
					{
						cout << output_int_data_ptr[i] << '\t';
					}
					cout << "]\n";
				}
				else
				{
					cout << "You haven't sorted your new data yet\n";
				}
			}
			else if (data_type_option == 2)
			{
				if (output_float_data_ptr && output_float_data_size)
				{
					cout << "[\t";
					for (int i = 0; i < output_float_data_size; i++)
					{
						cout << output_float_data_ptr[i] << '\t';
					}
					cout << "]\n";
				}
				else
				{
					cout << "You haven't sorted your new data yet\n";
				}
			}
			else
			{
				cout << "There is nothing to show. Read data from file or generate it and then sort it first\n";
			}
		}
		else
		{
			main_menu_option = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		delete sortMethodsInt[i];
		delete sortMethodsFloat[i];
	}

	delete[] sortMethodsInt;
	delete[] sortMethodsFloat;

	if (int_data_ptr)
		delete[] int_data_ptr;

	if (float_data_ptr)
		delete[] float_data_ptr;

	if (output_int_data_ptr)
		delete[] output_int_data_ptr;

	if (output_float_data_ptr)
		delete[] output_float_data_ptr;

	return 0;
}

template <typename T>
T *generateRandomOrdered(int size)
{
	T *new_data = new T[size];
	std::random_device rd;
	std::mt19937 gen(rd());

	if (typeid(T) == typeid(float))
	{
		std::uniform_real_distribution<float> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			new_data[i] = distribution(gen);
		}
	}
	else if (typeid(T) == typeid(int))
	{
		std::uniform_int_distribution<int> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			new_data[i] = distribution(gen);
		}
	}

	return new_data;
}

template <typename T>
T *generateAscendingOrder(int size)
{
	T *new_data = new T[size];

	for (int i = 0; i < size; i++)
	{
		new_data[i] = T(i);
	}

	return new_data;
}

template <typename T>
T *generateDescendingOrder(int size)
{
	T *new_data = new T[size];

	for (int i = 0; i < size; i++)
	{
		new_data[i] = T(size - i);
	}

	return new_data;
}

template <typename T>
T *generate33percentSorted(int size)
{
	T *new_data = new T[size];
	std::random_device rd;
	std::mt19937 gen(rd());

	if (typeid(T) == typeid(float))
	{
		std::uniform_real_distribution<float> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			if (i < size / 3)
			{
				new_data[i] = float(i);
			}
			else
			{
				new_data[i] = distribution(gen);
			}
		}
	}
	else if (typeid(T) == typeid(int))
	{
		std::uniform_int_distribution<int> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			if (i < size / 3)
			{
				new_data[i] = i;
			}
			else
			{
				new_data[i] = distribution(gen);
			}
		}
	}

	return new_data;
}

template <typename T>
T *generate66percentSorted(int size)
{
	T *new_data = new T[size];
	std::random_device rd;
	std::mt19937 gen(rd());

	if (typeid(T) == typeid(float))
	{
		std::uniform_real_distribution<float> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			if (i < 2 * size / 3)
			{
				new_data[i] = float(i);
			}
			else
			{
				new_data[i] = distribution(gen);
			}
		}
	}
	else if (typeid(T) == typeid(int))
	{
		std::uniform_int_distribution<int> distribution(0, size);

		for (int i = 0; i < size; i++)
		{
			if (i < 2 * size / 3)
			{
				new_data[i] = i;
			}
			else
			{
				new_data[i] = distribution(gen);
			}
		}
	}

	return new_data;
}

template <typename T>
bool checkIfSorted(T *data_ptr, int size)
{
	bool checker;

	for (int i = 1; i < size; i++)
	{
		checker = (data_ptr[i - 1] <= data_ptr[i]);
		if (!checker)
			break;
	}

	return checker;
}
