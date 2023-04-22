#pragma once

#include "PerfectHash.h"

#include <math.h>

//check is number a prime number
bool is_prime(int value)
{
    for (int i = 2; i * i <= value; i++)
    {
        if (value % i == 0)
            return false;
    }

    return true;
}

//find the smallest prime number bigger than val
int next_prime(int value)
{
    if (value <= 2)
        return 2;

    value++;

    while (!is_prime(value))
        value++;

    return value;
}

//decompose a real number into array [integer part, decimal part]
//E.g., -21,72876 = [21, 728]
int* decompose_real_number(double value) 
{
    int precision = 3;

    int* result = new int[2];

    double integer_part, fractional_part;
    fractional_part = modf(value, &integer_part);

    result[0] = abs((int)integer_part);
    result[1] = abs((int)(fractional_part * pow(10, precision)));

    return result;
}

//hash a real number
int double_to_int_function(double value, int p, Constants constants)
{
    int* parts = decompose_real_number(value);

    int sign = 0;
    if (value < 0)
        sign = 1;

    int result = (parts[0] * constants.a + parts[1] * constants.b + constants.c * sign) % p;

    return result;
}

int hash_function(std::vector<double> double_array, int size, int p, Constants constants)
{
    int result = 0;
    int arr_size = double_array.size();
    for(int i = 0; i < arr_size; i++)
        result += double_to_int_function(double_array[i], p, constants) * pow(constants.k, i);
    result = (result % p) % size ;
    return result;
}