#include "dict.h"

#include <string.h>
#include <iostream>

express::TreeDict::Node::Node(char* eng, char* rus, int call_am)
{
	this->eng = eng;
	this->rus = rus;
	this->call_am = call_am;
}

void express::TreeDict::addAlph(char* eng, char* rus, int call_am, Node* iter)
{
	if (iter == nullptr)
	{
		Node* to_add = new Node(eng, rus, call_am);
		this->head = to_add;
		return;
	}

	int comp = compare_alph_order(eng, iter->eng);

	if (comp == 0)
	{
		std::cout << "Such word does already exist. Counter is increased by 1.\n";
		iter->call_am = iter->call_am + 1;
		return;
	}

	else if (comp < 0)
	{
		if (iter->l_child == nullptr)
		{
			Node* to_add = new Node(eng, rus, call_am);
			iter->l_child = to_add;
			return;
		}

		else addAlph(eng, rus, call_am, iter->l_child);
	}

	else if (comp > 0)
	{
		if (iter->r_child == nullptr)
		{
			Node* to_add = new Node(eng, rus, call_am);
			iter->r_child = to_add;
			return;
		}

		else addAlph(eng, rus, call_am, iter->r_child);
	}
}

void express::TreeDict::addWordConsole()
{
	char *english = new char[20];
	char *russian = new char[20];
	int call_amount;

	std::cout << "Enter the word:";
	std::cin >> english;

	if (this->doesExist(english, this->head))
	{
		std::cout << "Unfortunately, such word does already exist.\n\n";
		return;
	}

	std::cout << "Enter the translation:";
	std::cin >> russian;

	std::cout << "Enter the amount of calls:";
	std::cin >> call_amount;

	std::cout << "\n\n";

	this->addAlph(english, russian, call_amount, this->head);
}

void express::TreeDict::print(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		std::cout << iter->eng << " ";
		print(iter->l_child);
		print(iter->r_child);
	}
}

void express::TreeDict::printGraph(const std::string& prefix, const express::TreeDict::Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|-- " : "|-- ");

		// print the value of the node
		std::cout << node->eng << std::endl;

		// enter the next tree level - left and right branch
		printGraph(prefix + (isLeft ? "|     " : "      "), node->l_child, true);
		printGraph(prefix + (isLeft ? "|     " : "      "), node->r_child, false);
	}
}

express::TreeDict::Node* express::TreeDict::find(Node* iter, int criteria)
{
	if (iter == nullptr) return nullptr;

	if (iter->call_am == criteria && (!iter->flag_check)) return iter;

	else
	{
		Node* result = nullptr;

		Node* l_result = find(iter->l_child, criteria);
		Node* r_result = find(iter->r_child, criteria);

		if (l_result != nullptr)
			result = l_result;

		else if (r_result != nullptr)
			result = r_result;

		return result;
	}
}

int express::TreeDict::findMax(Node* iter)
{
	if (iter == nullptr) return -1;
	
	int result = -1;
	if(!iter->flag_check) result = iter->call_am;

	int l_result = findMax(iter->l_child);
	int r_result = findMax(iter->r_child);

	if (l_result > result)
		result = l_result;

	if (r_result > result)
		result = r_result;

	return result;
}

bool express::TreeDict::doesExist(char* word, Node* iter)
{
	if (iter == nullptr) return false;
	
	if (std::strcmp(word, iter->eng) == 0) return true;

	bool l_result = doesExist(word, iter->l_child);

	if (l_result) return true;

	else return doesExist(word, iter->r_child);
}

void express::TreeDict::searchTransl(char* word, Node* iter)
{
	if (iter == nullptr) return;

	if (word == iter->eng)
	{
		std::cout << iter->rus << "\n";
		iter->call_am = iter->call_am + 1;
		return;
	}

	searchTransl(word, iter->l_child);
	searchTransl(word, iter->r_child);

	std::cout << "Such word doesn't exist\n";
	return;
}

void express::TreeDict::deleteTree(Node* iter)
{
	if (iter == nullptr) return;

	/* first delete both subtrees */
	deleteTree(iter->l_child);
	deleteTree(iter->r_child);

	/* then delete the node */
	delete iter;
}

int express::compare_alph_order(char* first, char* second)
{
	int min = std::min(std::strlen(first), std::strlen(second));

	int result = std::char_traits<char>::compare(first, second, min);
	if (result == 0)
	{
		if (std::strlen(first) == std::strlen(second)) return 0;
		else if (std::strlen(first) < std::strlen(second)) return -1;
		else return 1;
	}
	return result;
}

express::TreeDict express::new_tree_by_call(TreeDict tree)
{
	TreeDict result;
	while (tree.findMax(tree.head) >= 0)
	{
		int max = tree.findMax(tree.head);
		express::TreeDict::Node* temp = tree.find(tree.head, max);
		temp->flag_check = true;
		express::TreeDict::Node* to_add = new express::TreeDict::Node(temp->eng, temp->rus, temp->call_am);
		result.addAlph(to_add->eng, to_add->rus, to_add->call_am, result.head);
	}

	return result;
}




