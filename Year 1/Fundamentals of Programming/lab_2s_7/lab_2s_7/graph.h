#pragma once

namespace grp
{
	struct Line
	{
		int first_node;
		int second_node;
		int length;
		void printInfo();
		Line(int first_node, int second_node, int length);
	};
	struct LineList
	{
		struct Node
		{
			Line* info;
			Node* next = nullptr;
			Node* prev = nullptr;
			Node(Line* info);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		void printList();
		void swap(Node* a, Node* b);
		Node* partition(Node* low, Node* high);
		void quicksort(Node* low, Node* high);
		void add(int first_node, int second_node, int length);
	};
	LineList read(char* const NAME);
}