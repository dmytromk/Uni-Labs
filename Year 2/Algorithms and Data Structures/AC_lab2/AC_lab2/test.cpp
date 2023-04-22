#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <time.h>
#include <string>
#include <iostream>

#include "SubstringSearchAlgorithms.h"

TEST_CASE("Validity test")
{
	srand(time(NULL));

	int text_len = 100;
	int pat_len = 5;

	//std::string needle = generate_random_binary_string(pat_len);
	//std::string haystack = generate_random_binary_string(text_len);

	std::string needle = "ABBAB";
	std::string haystack = "BABABBAB";

	/*std::string pat = "AABAACAABAA";
	auto table = kmp_table(pat);
	std::cout << "\n";
	for (auto i : table)
		std::cout << i << " ";
	std::cout << "\n";

	std::string patt = "TEST";
	auto b_table = boyer_moore_dictionary(patt);
	std::cout << "\n";
	for (const auto& elem : b_table)
	{
		std::cout << elem.first << " " << elem.second <<"\n";
	}
	std::cout << "\n";*/

	int naive = naive_substring_search(needle, haystack);
	int kpm = kmp_substring_search(needle, haystack);
	int boyer_moore = boyer_moore_substring_search(needle, haystack);

	CHECK(naive == kpm);
	CHECK(naive == boyer_moore);
}

TEST_CASE("Speed test (binary)")
{
	srand(time(NULL));

	int text_len = 10000000;
	int pat_len = 500;

	std::string needle = generate_random_binary_string(pat_len);
	std::string haystack = generate_random_binary_string(text_len);

	std::clock_t start, end;

	std::cout << "\nBINARY SPEEDTEST";

	start = clock();
	int naive = naive_substring_search(needle, haystack);
	end = clock();
	std::cout << "\nNaive search algorithm speed: " << end - start << "ms";
	
	start = clock();
	int kmp = kmp_substring_search(needle, haystack);
	end = clock();
	std::cout << "\nKPM search algorithm speed: " << end - start << "ms";

	start = clock();
	int boyer_moore = boyer_moore_substring_search(needle, haystack);
	end = clock();
	std::cout << "\nBoyer-Moore search algorithm speed: " << end - start << "ms\n";

	std::cout << "Naive is: " << naive << "\n";
	std::cout << "KMP is: " << kmp << "\n";
	std::cout << "Boyer-Moore is: " << boyer_moore << "\n\n";

	CHECK(naive == kmp);
	CHECK(naive == boyer_moore);
}