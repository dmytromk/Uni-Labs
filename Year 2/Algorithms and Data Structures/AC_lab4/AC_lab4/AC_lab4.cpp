#include <iostream>
#include "treap.h"

int main()
{
    srand(time(NULL));

    TreapNode* test_node = nullptr; 

    //������ ��������� ������ �� ��������� ���������
    test_node = insert(test_node, Rational(1, 1));
    test_node = insert(test_node, Rational(4, 7));
    test_node = insert(test_node, Rational(7, 6));
    test_node = insert(test_node, Rational(2, 10));
    test_node = insert(test_node, Rational(5, 2));
    test_node = insert(test_node, Rational(1, 5));
    print(test_node); //�������� ��������� ������ � �������
    std::cout << "\n\n";

    test_node = del(test_node, Rational(1, 1)); //�������� ������� 1/1
    print(test_node);
    std::cout << "\n\n";

    test_node = del(test_node, Rational(3, 15)); //�������� ������� 3/15
    print(test_node);
    std::cout << "\n\n";
}
