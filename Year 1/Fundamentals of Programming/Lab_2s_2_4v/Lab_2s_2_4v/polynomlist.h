#pragma once

namespace polmult
{
	struct Pol
	{
		int coef;
		int pow;
		void printInfo();
		Pol(int coef, int pow);
	};
	struct PolList 
	{
		struct Node
		{
			Pol* info;
			Node* next = nullptr;
			Node(Pol* info);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		void printList();
		void removeDup();
		void add(int coef, int pow);
	};
	PolList multiply(PolList list1, PolList list2);
	PolList read(char* const NAME);
}
