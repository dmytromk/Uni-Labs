#include "binomial_heap.h"

int main() 
{
    BinomialHeap test_heap;

    //Будуємо біноміальну купу по наступним елементам
    test_heap.add(Rational(1, 1));
    printHeap(test_heap);

    test_heap.add(Rational(4, 7));
    printHeap(test_heap);

    test_heap.add(Rational(7, 6));
    printHeap(test_heap);

    test_heap.add(Rational(2, 50));
    printHeap(test_heap);

    test_heap.add(Rational(5, 2));
    printHeap(test_heap);

    test_heap.add(Rational(1, 5));
    printHeap(test_heap);

    //зменшуємо key дитини голови піраміди
    decrease_key(test_heap.head->child, Rational(1, 20));
    printHeap(test_heap);

    //видаляємо мінімум
    test_heap.extract_min();
    printHeap(test_heap); //Виводимо піраміду в консоль
}

