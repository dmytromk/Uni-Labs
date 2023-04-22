#pragma once
#include <vector>
#include <algorithm>
#include <time.h>

/*class HashSubTable
{   
    private: 
		int a;
		int b;
		int c;
		int p; //prime number bigger than any key 
		int size = 0;
		std::vector<double> array;

	HashSubTable(int p, std::vector<int> value_array);
	void add(double);
	void rehash();
	bool check_for_collisions();
	void print();
};*/

struct Constants
{
	int a = 0; //for integer part
	int b = 0; //for fractional part
	int c = 0; //for sign
	int k = 0;
	void randomize(int p);
};

struct HashTable
{
	Constants consts;
	int p;
	int size = 0;
	std::vector<std::vector<double>>* key_array;
	Constants* constants_array;
	HashTable(std::vector<std::vector<double>> keys);
	void rehash();
	void print();
	void find(std::vector<double> key);
	~HashTable();
};