#pragma once

#include <iostream>

#include <string>
#include <vector>
#include <map>

#define  NO_OF_CHARS 256

int naive_substring_search(std::string pattern, std::string text)
{	
	int m = pattern.size();
	int n = text.size();

	for (int i = 0; i <= n-m; i++)
	{
		int j = 0;

		for (; j < m; j++)
			if (text[i + j] != pattern[j])
				break;

		if (j == m)
			return i;
	}
	return -1;
}


/*int* kmp_table(std::string pattern, int size)
{
	int* resulting_table = new int[size];
	resulting_table[0] = 0;
	int i = 0;
	int j = 1;

	while (j < size)
	{
		if (pattern[i] == pattern[j])
		{
			i++;
			resulting_table[j] = i;
			j++;
		}
		else //(pattern[i] != pattern[j])
		{
			if (i == 0)
			{	
				resulting_table[j] = 0;
				j++;			
			}
			else //(i != 0)
			{
				i = resulting_table[i-1];
			}
		}
		
	}
	return resulting_table;
}*/

int* prefix_func(std::string pattern, int size)
{
	int* result = new int[size];
	result[0] = 0;

	for (int i = 1; i < size; ++i)
	{
		int j = result[i - 1];

		while (j != 0 && pattern[i] != pattern[j])
			j = result[j - 1];

		if (pattern[i] == pattern[j])
			j++;

		result[i] = j;
	}

	return result;
}

int kmp_substring_search(std::string pattern, std::string text)
{
	int m = pattern.size();
	int n = text.size();

	int* table = prefix_func(pattern, m);

	int i = 0; //text
	int j = 0; //pattern

	while(i < n)
	{
		if (text[i] == pattern[j])
		{
			i++;
			j++;
			if (j == m)
			{
				delete[] table;
				return i - m;
			}
		}

		else //text[i] != pattern[j]
		{
			if (j == 0)
				i++;
			else
				j = table[j - 1];
		}
	}

	delete[] table;

	return -1;
}


/*std::map<char, int> boyer_moore_dictionary(std::string pattern, int size)
{
	std::map<char, int> result;

	for (int i = 0; i < size; i++)
		result[pattern[i]] = i;

	return result;
}*/

void create_bad_symbol_table(std::string pattern, int size, int badchar_table[NO_OF_CHARS])
{
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar_table[i] = size;

	for (i = 0; i < size - 1; i++)
		badchar_table[(int)pattern[i]] = size - i - 1;
}

bool is_prefix(std::string pattern, int position, int size) 
{
	for (int i = position, j = 0; i < size; i++, j++)
		if (pattern[i] != pattern[j])
			return false;

	return true;
}

int suffix_size(std::string pattern, int position, int size) 
{
	int result = 0;
	int i = position;
	int j = size - 1;

	while (i >= 0 && pattern[i] == pattern[j]) {
		--i;
		--j;
		result++;
	}

	return result;
}

int* create_good_suffix_table(std::string pattern, int size)
{
	int* result = new int[size];

	int last_prefix_index = size;

	for (int i = size; i > 0; --i) {
		if (is_prefix(pattern, i, size))
			last_prefix_index = i;

		result[size - i] = last_prefix_index - i + size;
	}

	for (int i = 0; i < size - 1; ++i)
	{
		int j = suffix_size(pattern, i, size);
		result[j] = size - 1 - i + j;
	}

	return result;

}

int boyer_moore_substring_search(std::string pattern, std::string text)
{
	int m = pattern.size();
	int n = text.size();

	int badchar_table[NO_OF_CHARS];
	create_bad_symbol_table(pattern, m, badchar_table);

	int* goodsuffix_table = create_good_suffix_table(pattern, m);

	//std::map<char, int> dictionary = boyer_moore_dictionary(pattern, m);

	/*while (i <= n - m)
	{
		int j = m - 1; //pattern

		while (j >= 0 && text[i+j] == pattern[j])
			j--;

		if (j < 0)
			return i;

		else //text[i] != pattern[j]
		{
			int pref = badchar_table[text[i + j]];
			auto temp = goodsuffix_table[m - j];
			if (j == m - 1)
				i += std::max(1, j - pref);
			else
				i += std::max(goodsuffix_table[m - j], std::max(1, j - pref));
			
		}
	}*/

	for (int i = m - 1, j; i < n;) //i - idx text, j - idx pattern
	{
		for (j = m - 1; pattern[j] == text[i]; --i, --j)
		{
			if (j == 0)
			{
				delete[] goodsuffix_table;
				return i;
			}
		}
		i += std::max(goodsuffix_table[m - 1 - j], badchar_table[text[i]]);
	}

	delete[] goodsuffix_table;
	return -1;
}

std::string generate_random_binary_string(int length)
{
	std::string result = "";

	for (int i = 0; i < length; i++)
	{
		int x = rand() % 2;
		result += std::to_string(x);
	}

	return result;
}
