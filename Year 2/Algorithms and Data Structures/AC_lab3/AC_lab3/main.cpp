#include "PerfectHash.h"

#include <vector>
#include <iostream>

int main()
{
	//std::cout << next_prime(193);

	std::vector<std::vector<double>> test
	{ 
		{0.01, -0.1, 0.02, -0.01, 0.25, 0.7}, 
		{2, 4, 5}, 
		{4, 26.3, 0.87}, 
		{109, 2, 5}, 
		{1.53, 0.08, 12.04}
	};

	std::vector<std::vector<double>> test2
	{
		{16.2, 10.001, 10.0004, 15, 0.02},
		{29.32, -15.9, 30.047},
		{-6, 2.3, 0.08754},
		{88895.643, -3.4356, 5.3},
		{553.43562, 34.42, -0.001},
		{0.9, 1.95, -0.26, 0.666, 65.68, -17.92}
	};

	std::vector<std::vector<double>> test3
	{
	  {16.2, 10.001, 10.0004, 15, 0.02},
	  {29.32, -15.9, 30.047},
	  {-6, 2.3, 0.08754},
	  {88895.643, -3.4356, 5.3},
	  {88895.643, 5.3, -3.4356,},
	  {},
	  {553.43562, 34.42, -0.001},
	  {0.9, 1.95, -0.26, 0.666, 65.68, -17.92}
	};

	HashTable test_table(test3);
	test_table.print();

	//test_table.find({ 2, 4, 5 });

	
	return 0;
}