#include "exp_tree.h"

#include <iostream>
#include <string>
#include <stack>

express::EpxTree::NodeVar::NodeVar(char key, int val)
{
	this->key = key;
	this->val = val;
}

void express::EpxTree::addVar(char key, int val)
{
	if (this->headVar == nullptr)
	{
		NodeVar* to_add = new NodeVar(key, val);
		if (this->headVar == nullptr)
		{
			this->headVar = to_add;
			this->tailVal = to_add;
		}
		else
		{
			this->tailVal->next = to_add;
			this->tailVal = to_add;
			this->tailVal->next = nullptr;
		}
	}
}

bool express::EpxTree::does_exist_var(char key)
{
	NodeVar* iter = headVar;

	while (iter != nullptr)
	{
		if (iter->key == key)
			return true;
		else
			iter = iter->next;
	}

	return false;
}

int express::EpxTree::valVar(char key)
{
	NodeVar* iter = headVar;

	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter->val;
		else
			iter = iter->next;
	}
}

express::EpxTree::Node::Node(char val)
{
	this->val = val;
	this->l_child = nullptr;
	this->r_child = nullptr;
}

void express::EpxTree::print(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		std::cout << iter->val << " ";
		express::EpxTree::print(iter->l_child);
		express::EpxTree::print(iter->r_child);
	}
}

void express::EpxTree::printGraph(const std::string& prefix, const express::EpxTree::Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|-- " : "|-- ");

		// print the value of the node
		std::cout << node->val << std::endl;

		// enter the next tree level - left and right branch
		printGraph(prefix + (isLeft ? "|   " : "    "), node->l_child, true);
		printGraph(prefix + (isLeft ? "|   " : "    "), node->r_child, false);
	}
}

int express::precedence(char input)
{
	if (input == '^')
		return 3;
	else if (input == '/' || input == '*' || input == '%')
		return 2;
	else if (input == '+' || input == '-')
		return 1;
	else if (input == '#')
		return 1;
	else
		return -1;
}

bool express::is_num_var(char input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')
		|| (input >= '0' && input <= '9'))
		return true;
	else
		return false;
}

void express::infix_to_postfix(char* input, char* result)
{
	std::stack <char> stack;
	int count = 0;

	for (int i = 0; i < strlen(input); i++)
	{
		char cur = input[i];

		if (express::is_num_var(cur))
		{
			result[count] = cur;
			count++;
		}

		else if (cur == '(')
			stack.push(cur);

		else if (cur == ')')
		{
			while (stack.top() != '(')
			{
				result[count] = stack.top();
				count++;
				stack.pop();
			}
			stack.pop();
		}

		else if (cur == '-' 
			&& (express::is_num_var(input[i+1]) || i == 0))
			stack.push('#');

		else 
		{
			if (cur == ' ')
				continue;
			while (!stack.empty()
				&& (express::precedence(cur) <= express::precedence(stack.top())))
			{
				if (cur == '^' && stack.top() == '^')
					break;
				else 
				{
					result[count]=stack.top();
					count++;
					stack.pop();
				}
			}
			stack.push(cur);
		}
	}

	while (!stack.empty()) {
		result[count] = stack.top();
		count++;
		stack.pop();
	}
	return;
}

void express::EpxTree::build(char* input)
{
	express::EpxTree::Node* x, * y, * z;
	std::stack <express::EpxTree::Node*> stack;


	int l = strlen(input);
	for (int i = 0; i < l; i++)
	{
		if (input[i] == '+' || input[i] == '-' || input[i] == '*'
			|| input[i] == '/' || input[i] == '^'
			|| input[i] == '%')
		{
			z = new express::EpxTree::Node(input[i]);
			x = stack.top();
			stack.pop();
			y = stack.top();
			stack.pop();
			z->l_child = y;
			z->r_child = x;
			stack.push(z);
			this->head = z;
		}
		else if (input[i] == '#')
		{
			z = new express::EpxTree::Node(input[i]);
			x = stack.top();
			stack.pop();
			z->l_child = x;
			stack.push(z);
			this->head = z;
		}
		else
		{
			z = new express::EpxTree::Node(input[i]);
			stack.push(z);
		}
	}
	//this->print(head);
}

int express::EpxTree::evaluate(Node* iter)
{
	if (isdigit(iter->val))
	{
		int result = iter->val - '0';
		return result;
	}

	else if ((iter->val >= 'a' && iter->val <= 'z')
		|| (iter->val >= 'A' && iter->val <= 'Z'))
	{
		if (!does_exist_var(iter->val))
		{
			std::cout << "\nEnter the val for " << iter->val << ": ";
			int result;
			std::cin >> result;
			return result;
		}
		else
		{
			return valVar(iter->val);
		}
	}

	else if (iter->val == '#')
		return (-1) * evaluate(iter->l_child);

	else if (iter->val == '-')
		return (evaluate(iter->l_child) - evaluate(iter->r_child));

	else if (iter->val == '+')
		return (evaluate(iter->l_child) + evaluate(iter->r_child));

	else if (iter->val == '*')
		return (evaluate(iter->l_child) * evaluate(iter->r_child));

	else if (iter->val == '/')
		return (evaluate(iter->l_child) / evaluate(iter->r_child));

	else if (iter->val == '%')
		return (evaluate(iter->l_child) % evaluate(iter->r_child));
}