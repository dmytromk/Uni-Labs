#include "Labyrinth.h"

void labyrinth::Point::printInfo()
{
	std::cout << this->x << " " << this->y << "\n  |\n";
}

labyrinth::Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

labyrinth::LabyrStack::Node::Node(Point* info)
{
	this->info = info;
}

void labyrinth::LabyrStack::printStack()
{
	Node* iter1 = head;
	while (iter1->next)
	{
		iter1->info->printInfo();
		iter1 = iter1->next;
	}
	iter1->info->printInfo();
	std::cout << "\n";
}

void labyrinth::LabyrStack::delLast()
{

	if (!tail)
	{
		return;
	}
	else
	{
		if (!tail->prev)
		{
			Node* temp = tail;
			tail = nullptr;
			head = nullptr;
			delete(temp);
			temp = NULL;
		}
		else
		{
			tail->prev->next = nullptr;
			Node* temp = tail;
			tail = tail->prev;
			delete(temp);
			temp = NULL;
		}
	}
}

void labyrinth::LabyrStack::add(Point* point)
{
	Node* node = new Node(point);
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


