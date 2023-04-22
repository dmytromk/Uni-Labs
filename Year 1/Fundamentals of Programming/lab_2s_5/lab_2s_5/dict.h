#pragma once

#include <string>

namespace express
{

	struct TreeDict
	{
		struct Node
		{
			char* eng;
			char* rus;
			bool flag_check = false;
			int call_am = 0;
			Node* l_child = nullptr;
			Node* r_child = nullptr;
			Node(char* eng, char* rus, int call_am = 0);
		};

		Node* head = nullptr;

		void addAlph(char* eng, char* rus, int call_am, Node* iter);
		void addWordConsole();

		void print(Node* iter);
		void printGraph(const std::string& prefix, const express::TreeDict::Node* node, bool isLeft);

		Node* find(Node* iter, int criteria);

		int findMax(Node* iter);
		bool doesExist(char* word, Node* iter);
		void searchTransl(char* word, Node* iter);

		void deleteTree(Node* iter);
		//void printGraph(const std::string& prefix, const express::TreeDict::Node* node, bool isLeft);
	};

	int compare_alph_order(char* first, char* second);

	TreeDict new_tree_by_call(TreeDict tree);

}