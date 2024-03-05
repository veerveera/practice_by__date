#include <iostream>
#include "omp.h"

int rank;
int N, i, k, z, z1, z2;
int sum = 0;

void first() {
#pragma omp for
	for (int i = 0; i < 4; i++)
		std::cout << "hello world!" << std::endl;
	return;
};

void second() {
int k;
#pragma omp parallel for
		std::cout << "Enter number" << std::endl;
		std::cin >> k;
		for (int i = 0; i < k; i++)
			std::cout << "I am " << i << " thread from " << k << " threads!" << std::endl;
	return;
}

void thrid() {
	int k, rank;
	std::cout << "Enter count of threads: " << std::endl;
	std::cin >> k;

#pragma omp parallel num_threads(k)
	{
#pragma omp critical
		{
			rank = omp_get_thread_num();
			std::cout << "I'm " << rank << " thread." << std::endl;
		}
	}
}
//fourth(last)

int main() {

	first();
	std::cout << "------------------------" << std::endl;
	second();
	std::cout << "------------------------" << std::endl;
	thrid();
	std::cout << "------------------------" << std::endl;


	std::cout << "Enter number N: " << std::endl;
	std::cin >> N;
	std::cout << "Enter number of threads k :" << std::endl;
	std::cin >> k;
	z = N / k;
	z1 = 0;
	z2 = z;

#pragma omp parallel reduction(+:sum) num_threads(k)
	{
#pragma omp for{

		for (i = 0; i <= N; i++)
			sum = sum + i;
		rank = omp_get_thread_num();
		std::cout << "[ " << rank << " ]: SUM = " << sum << std::endl;
		}
	std::cout << "Result: SUM = " << sum << std::endl;
	}
