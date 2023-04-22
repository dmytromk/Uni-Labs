#include "graph.h"

#include <fstream>
#include <iostream>

void grp::Line::printInfo()
{
	std::cout << "(" << first_node << ", "
		<< second_node << ") - " << length << "\n";
}

grp::Line::Line(int first_node, int second_node, int length)
{
	this->first_node = first_node;
	this->second_node = second_node;
	this->length = length;
}

grp::LineList::Node::Node(Line* info)
{
	this->info = info;
}

void grp::LineList::printList()
{
	Node* iter1 = head;
	while (iter1->next)
	{
		iter1->info->printInfo();
		std::cout << "\n";
		iter1 = iter1->next;
	}
	iter1->info->printInfo();
}

void grp::LineList::swap(Node* a, Node* b)
{
	Node* iter1 = head;
	Node* iter2 = head;

	while (iter1)
	{
		if (iter1 == a) break;
		iter1 = iter1->next;
	}

	while (iter2)
	{
		if (iter2 == b) break;
		iter2 = iter2->next;
	}

	grp::Line* temp = iter1->info;

	iter1->info = iter2->info;
	iter2->info = temp;

	return;
}

grp::LineList::Node* grp::LineList::partition(Node* low, Node* high)
{
	grp::Line* x = high->info;
	Node* i = low->prev;

	for (Node* j = low; j != high; j = j->next)
	{
		if (j->info->length <= x->length)
		{
			i = (i == nullptr) ? low : i->next;
			swap(i, j);
		}
	}
	i = (i == nullptr) ? low : i->next;
	swap(i, high);
	return i;
}

void grp::LineList::quicksort(Node* low, Node* high)
{
	if (high != nullptr && low != high && low != high->next)
	{
		Node* p = partition(low, high);
		quicksort(low, p->prev);
		quicksort(p->next, high);
	}
}

void grp::LineList::add(int first_node, int second_node, int length)
{
	Line* to_add = new Line(first_node, second_node, length);
	Node* node = new Node(to_add);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

grp::LineList grp::read(char* const NAME)
{
	std::ifstream out(NAME, std::ifstream::in);
	LineList result;

	int first_node, second_node, length;
	while (out >> first_node >> second_node >> length) 
		result.add(first_node, second_node, length);

	out.close();

	return result;
}
