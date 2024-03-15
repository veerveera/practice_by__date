#include <iostream>
#include "omp.h"
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void first() {
	int num;
	cout << "Enter size of mas: " << endl;
	cin >> num;
	int* mas = new int[num];
	double itog = 0;

	for (int i = 0; i < num; i++) {
		srand(time(NULL));
		mas[i] = rand();
	}
#pragma omp parallel num_threads(3) reduction(+:itog){

#pragma omp parallel for
	for (int i = 0; i < num; i++) {
		itog += mas[i];
	}
	cout << "Sum = " << itog << endl;
	return;

	}

	void merge(int* array, int low, int mid, int high)
	{
		int* temp = new int[high + 1];
		int i = low;
		int j = mid + 1;
		int k = 0;

		while (i <= mid && j <= high)
		{
			if (array[i] <= array[j])
				temp[k++] = array[i++];
			else
				temp[k++] = array[j++];
		}
		while (i <= mid)
			temp[k++] = array[i++];
		while (j <= high)
			temp[k++] = array[j++];
		k--;
		while (k >= 0)
		{
			array[k + low] = temp[k];
			k--;
		}
	}

	void sort(int* array, int left, int right)
	{
		int mid;

		if (left < right)
		{
			mid = (left + right) / 2;
			sort(array, left, mid);
			sort(array, mid + 1, right);
			merge(array, left, mid, right);
		}
	}

	void sort_parallel(int* mas, int left, int right) {

		if (left < right) {
			int middle = left + (right - left) / 2;
#pragma omp parallel sections
#pragma omp section
			sort_parallel(mas, left, middle);
#pragma omp section
			sort_parallel(mas, middle + 1, right);

			merge(mas, left, middle, right);
		}
	}

	void second() {
		const int arraySize = 100;
		int myArray[arraySize];
		int myArray1[arraySize];
		long long int sum = 0;
		for (int i = 0; i < arraySize; ++i) {
			myArray[i] = rand() % 101;
			myArray1[i] = myArray[i];
		}

		const int processor_count = std::thread::hardware_concurrency() / 2;
		std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();
		sort(myArray, 0, arraySize - 1);
		std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

		std::chrono::high_resolution_clock::time_point start2 = std::chrono::high_resolution_clock::now();
		sort_parallel(myArray1, 0, arraySize - 1);
		std::chrono::high_resolution_clock::time_point end2 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

		for (int i = 0; i < arraySize; i++) {
			std::cout << myArray[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << myArray1[i] << " ";
		}
		std::cout << std::endl;

		std::cout << duration1.count() << std::endl;
		std::cout << duration2.count() << std::endl;
	}

	int main() {
		cout << "First example" << endl;
		first();
		cout << "----------------------" << endl;
		cout << "Second example" << endl;
		second();
	}