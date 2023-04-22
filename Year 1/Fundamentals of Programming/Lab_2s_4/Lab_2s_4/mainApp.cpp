#include "exp_tree.h"

#include "iostream"


int main()
{
	express::EpxTree tree;

	const int SIZE = 50;
	char inp[SIZE] = "3 + x * (-1) + 9 * (-y)";
	char out[SIZE] = "";

	express::infix_to_postfix(inp, out);
	int size = strlen(out);

	//for (int i = 0; i < size; i++)
		//std::cout << out[i];

	tree.build(out);
	tree.printGraph("", tree.head, false);

	std::cout << tree.evaluate(tree.head);

	return 0;
}