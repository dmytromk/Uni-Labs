// lab_2s_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "dict.h"

#include <iostream>



int main()
{

    //char fir[] = "abs";
    //char sec[] = "b";

    /*std::cout << express::compare_alph_order(fir, sec);

    express::TreeDict tree;

    char a[] = "aks";
    char rus[] = "слдвлти";

    char b[] = "aa";
    char c[] = "ab";



    char e[] = "azb";
    char g[] = "azkz";
    char f[] = "aza";



   // tree.addAlph(a, rus, 2, tree.head);
    tree.addAlph(b, rus, 0, tree.head);
    tree.addAlph(c, rus, 6, tree.head);
    //tree.addAlph(d, rus, 50, tree.head);
    tree.addAlph(e, rus, 0, tree.head);
    tree.addAlph(f, rus, 0, tree.head);
   tree.addAlph(g, rus, 0, tree.head);

    //tree.print(tree.head);
    //std::cout << tree.findMax(tree.head);

    express::TreeDict treeTwo;
    treeTwo = express::new_tree_by_call(tree);
    //treeTwo.print(treeTwo.head);
    treeTwo.printGraph("", treeTwo.head, false);*/

    express::TreeDict DictTree;
    express::TreeDict CallTree;
    while (true)
    {
        std::cout << "Enter 1 to print tree.\n";
        std::cout << "Enter 2 to add word.\n";
        std::cout << "Enter 3 to search translation.\n";
        std::cout << "Enter 4 to convert tree.\n\n";

        char input = ' ';
        std::cin >> input;

        switch (input)
        {
        case '1':
            DictTree.printGraph("", DictTree.head, false);
            break;

        case '2':
            DictTree.addWordConsole();
            break;

        case '3':
            std::cout << "Enter the word:";
            char word[20];
            std::cin >> word;
            DictTree.searchTransl(word, DictTree.head);
            break;

        case '4':
            CallTree = express::new_tree_by_call(DictTree);
            CallTree.printGraph("", CallTree.head, false);
            break;
        }
    }
}

