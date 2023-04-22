#include "polynomlist.h"

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

void append(char* s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}

void polmult::Pol::printInfo()
{
	std::cout << this->coef << "*x^" << this->pow;
}

polmult::Pol::Pol(int coef, int pow)
{
	this->coef = coef;
	this->pow = pow;
}

polmult::PolList::Node::Node(Pol* info)
{
	this->info = info;
}

void polmult::PolList::printList()
{
	Node* iter1 = head;
	while (iter1->next)
	{
		iter1->info->printInfo();
		std::cout << " + ";
		iter1 = iter1->next;
	}
	iter1->info->printInfo();
	std::cout << "\n";
}

void polmult::PolList::removeDup()
{
	Node* iter1 = head;
	Node* iter2 = head;
	Node* temp;
	while (iter1->next)
	{
		iter2 = iter1;
		while (iter2 && iter2->next)
		{
			//main LOGIC
			if (iter2->next->info->pow == iter1->info->pow)
			{
				iter1->info->coef = iter1->info->coef + iter2->next->info->coef;
				temp = iter2->next;

				iter2->next = iter2->next->next;
				iter2 = iter2->next;

				delete(temp);
				temp = NULL;
			}
			else iter2 = iter2->next;
		}
		iter1 = iter1->next;
	}
}

void polmult::PolList::add(int coef, int pow)
{
	Pol* to_add = new Pol(coef, pow);
	Node* node = new Node(to_add);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
	}
}

polmult::PolList polmult::multiply(PolList list1, PolList list2)
{
	PolList result;
	if (!list1.tail || !list2.tail)
	{
		Pol* to_add = new Pol(0, 0);
		PolList::Node* node = new PolList::Node(to_add);
		result.head = node;
		result.tail = node;
		return result;
	}
	else
	{
		polmult::PolList::Node* iter1 = list1.head;
		polmult::PolList::Node* iter2 = list2.head;
		while (iter1)
		{
			while (iter2)
			{
				int coef = iter1->info->coef * iter2->info->coef;
				int pow = iter1->info->pow + iter2->info->pow;
				result.add(coef, pow);
				iter2 = iter2->next;
			}
			iter1 = iter1->next;
			iter2 = list2.head;
		}
		result.removeDup();
		return result;
	}
}

polmult::PolList polmult::read(char* const NAME)
{
	std::ifstream out(NAME, std::ifstream::in);
	PolList result;

	const int SIZE = 8;
	bool b_coef = true;
	char buffer[SIZE];
	char coef[8] = "";
	char pow[SIZE] = "";
	int i_coef = 0;
	int i_pow = 0;

	while (!out.eof())
	{
		out.read((char*)&buffer, sizeof(buffer));
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (buffer[i] == '+' || buffer[i] == '-')
			{
				b_coef = true;
				i_pow = std::stoi(pow);
				memset(pow, 0, sizeof(pow));
				result.add(i_coef, i_pow);
				append(coef, buffer[i]);
			}
			else if (buffer[i] == 'x')
			{
				b_coef = false;
				i_coef = std::stoi(coef);
				memset(coef, 0, sizeof(coef));
			}
			else if (isdigit(buffer[i]) && b_coef) append(coef, buffer[i]);
			else if (isdigit(buffer[i]) && !b_coef) append(pow, buffer[i]);
			else if (buffer[i] == ' ' || b_coef =='^' || buffer[i] == '*') continue;
			else if(buffer[i] == '\0')
			{
				result.add(i_coef, i_pow);
				return result;
			}
		}
	}
	out.close();
	return result;
}
