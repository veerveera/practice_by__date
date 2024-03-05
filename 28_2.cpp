#include <iostream>
#include "omp.h"

int rank;
int N, i, k, z, z1, z2;
int sum = 0;

int main() {
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
