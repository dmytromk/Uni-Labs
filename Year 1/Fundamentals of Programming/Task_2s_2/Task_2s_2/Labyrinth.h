#pragma once
#include <iostream>

namespace labyrinth
{
	struct Point
	{
		int x, y;
		void printInfo();
		Point(int x, int y);
	};
	struct LabyrStack
	{
		struct Node
		{
			Point* info;
			Node* next = nullptr;
			Node* prev = nullptr;
			Node(Point* info);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		void printStack();
		void delLast();
		void add(Point* point);
	};
}