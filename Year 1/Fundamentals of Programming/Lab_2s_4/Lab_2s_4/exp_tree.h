#pragma once

#include <string>

namespace express
{

	struct EpxTree
	{
		struct NodeVar
		{
			char key;
			int val;
			NodeVar* next = nullptr;
			NodeVar(char key, int val);
		};

		NodeVar* headVar = nullptr;
		NodeVar* tailVal = nullptr;

		void addVar(char key, int val);
		bool does_exist_var(char key);
		int valVar(char key);

		struct Node
		{
			char val;
			Node* l_child = nullptr;
			Node* r_child = nullptr;
			Node(char val);
		};

		Node* head = nullptr;

		void build(char* input);

		void print(Node* iter);
		void printGraph(const std::string& prefix, const express::EpxTree::Node* node, bool isLeft);

		int evaluate(Node* iter);
	};

	int precedence(char input);
	bool is_num_var(char input);

	void infix_to_postfix(char* input, char* result);
}
