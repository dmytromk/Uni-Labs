#include "PerfectHash.h"
#include "utils.h"

#include <iostream>
#include <math.h>

void Constants::randomize(int p)
{
    this->a = rand() % p;
    this->b = rand() % p;
    this->c = rand() % p;

    int k_div = 6;
    this->k = rand() % k_div;
}

HashTable::HashTable(std::vector<std::vector<double>> keys)
{
    srand(time(NULL));

    std::sort(keys.begin(), keys.end());
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());

    for (int i = 0; i < keys.size(); ) {
        if (keys[i].size() == 0) {
            keys.erase(keys.begin() + i);
        }
        else ++i;
    }

    this->size = keys.size();

    this->key_array = new std::vector<std::vector<double>>[this->size];
    this->constants_array = new Constants[this->size];

    this->p = next_prime(pow(size, 2));
    this->consts.randomize(this->p);

    for (auto& elem : keys)
    {
        int key = hash_function(elem, this->size, this->p, this->consts);
        this->key_array[key].push_back(elem);
    }

    rehash();
}

void HashTable::rehash()
{
    for (int i = 0; i <= this->size - 1; i++)
    {
        int collisions_amount = this->key_array[i].size();
        int collision_array_size = pow(collisions_amount, 2);
        if (collisions_amount >= 2)
        {
            int attempt = 0;
            while (attempt < 30)
            {
                this->constants_array[i].randomize(this->p);
                std::vector<std::vector<double>> collision_array;
                collision_array.resize(collision_array_size);

                int counter = 0;
                for (counter = 0; counter <= collisions_amount - 1; counter++)
                {
                    std::vector<double> collision = this->key_array[i][counter];
                    int sub_key = hash_function(collision, collision_array_size, this->p, this->constants_array[i]);
                    if (collision_array[sub_key].size() != 0)
                        break;
                    collision_array[sub_key] = collision;
                }
                if (counter == collisions_amount)
                {
                    /*for (auto& elem : collision_array)
                        if(isnan(elem)) 
                            elem = 0;*/
                    this->key_array[i] = collision_array;
                    break;
                }

                attempt++;
            }       
            if (attempt == 30)
                std::cout << "ERROR! NO POSSIBLE WAY TO AVOID COLLISIONS!\n\n";
        }
    }
}

HashTable::~HashTable()
{
    delete [] this->key_array;
    this->key_array = nullptr;

    delete[] this->constants_array;
    this->constants_array = nullptr;
}

void HashTable::print()
{
    for (int i = 0; i <= this->size - 1; i++)
    {
        std::cout << "Element " << i << ":";
        for (auto& elem : this->key_array[i])
            if (elem.size() == 0) std::cout << " _ ";
            else
            {
                std::cout << " {";
                for (auto& arr : elem)
                    std::cout << arr << "; ";
                std::cout << "} ";
            }
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "Constant Hash: ";
    std::cout << "a = " << this->consts.a 
        << "  b = " << this->consts.b
        << "  c = " << this->consts.c 
        << "  k = " << this->consts.k
        << "  p = " << this->p;
    std::cout << "\n";

    for (int i = 0; i <= this->size - 1; i++)
    {
        std::cout << "Constant[" << i << "]: ";
        std::cout << "a = " << this->constants_array[i].a 
            << "  b = " << this->constants_array[i].b 
            << "  c = " << this->constants_array[i].c 
            << "  k = " << this->constants_array[i].k;
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void HashTable::find(std::vector<double> key)
{
    int main_idx = hash_function(key, this->size, this->p, this->consts);
    int arr_size = this->key_array[main_idx].size();
    if (arr_size == 0)
    {
        std::cout << "THERE IS NO SUCH A NUMBER!\n\n";
        return;
    }

    int second_idx = 0;
    if (arr_size > 1)
        second_idx = hash_function(key, this->key_array[main_idx].size(), this->p, this->constants_array[main_idx]);

    if(this->key_array[main_idx][second_idx] == key && this->key_array[main_idx][second_idx].size() != 0)
        std::cout << "{" << main_idx << " ; " << second_idx << "}\n\n";
    else
        std::cout << "THERE IS NO SUCH A NUMBER!\n\n";
}
