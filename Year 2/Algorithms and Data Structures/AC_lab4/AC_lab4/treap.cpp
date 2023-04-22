#include "treap.h"
#include <stdexcept>

TreapNode::TreapNode(Rational key = Rational(), Rational priority = Rational())
{
	this->key = key;
	this->priority = priority;
}

TreapNode::TreapNode(Rational key, Rational priority, TreapNode* left, TreapNode* right)
{
	this->key = key;
	this->priority = priority;
	this->left = left;
	this->right = right;
}

/*void TreapNode::add(Rational key = Rational(), Rational priority = Rational())
{
	TreapNode *to_add = new TreapNode(key, priority);
	if(this->priority < priority) throw std::domain_error{ "Trying to add node with greater priority" };
	if (this->key > key) this->left = to_add;
	else this->right = to_add;
}

void TreapNode::add(TreapNode* to_add)
{
	if (this->priority < to_add->priority) throw std::domain_error{ "Trying to add node with greater priority" };
	if (this->key > to_add->key)
	{
		if (this->left == nullptr) this->left = to_add;
		else this->left->add(to_add);
	}
	else
	{
		if (this->right == nullptr) this->right = to_add;
		else this->right->add(to_add);
	}
}*/

void TreapNode::split(Rational key_to_split, TreapNode* &L, TreapNode* &R)
{
	TreapNode* new_tree = nullptr;

	if (this->key <= key_to_split)
	{
		if (this->right == nullptr) R = nullptr;
		else this->right->split(key_to_split, new_tree, R);
		L = new TreapNode(this->key, this->priority, this->left, new_tree);
	}

	else
	{
		if (this->left == nullptr) L = nullptr;
		else this->left->split(key_to_split, L, new_tree);
		R = new TreapNode(this->key, this->priority, new_tree, this->right);
	}
}

TreapNode* search(TreapNode* root, Rational key)
{
	if (root == nullptr || root->key == key) return root;
	else if (key < root->key) return search(root->left, key);
	else search(root->right, key);
}

bool check_keys(TreapNode* left_head, TreapNode* right_head) //check if all the keys from L are less than any key from R
{
	if (right_head == nullptr || left_head == nullptr) return true;
	else if (left_head->key > right_head->key) return false;
	else return check_keys(left_head, right_head->right);
}

TreapNode* merge(TreapNode* left_head, TreapNode* right_head)
{
	if (left_head == nullptr) return right_head;
	if (right_head == nullptr) return left_head;

	else if (left_head->priority > right_head->priority)
	{
		TreapNode* new_right = merge(left_head->right, right_head);
		return new TreapNode(left_head->key, left_head->priority, left_head->left, new_right);
	}

	else
	{
		TreapNode* new_left = merge(left_head, right_head->left);
		return new TreapNode(right_head->key, right_head->priority, new_left, right_head->right);
	}
}

TreapNode* insert(TreapNode* root, Rational key)
{
	int max = 100;

	if (root == nullptr)
	{
		root = new TreapNode(key, Rational(1, rand() % max + 1));
		return root;
	}

	TreapNode* l = nullptr, * r = nullptr;
	root->split(key, l, r);
	TreapNode* temp_node = new TreapNode(key, Rational(1, rand() % max + 1));
	merge(merge(l, temp_node), r);
}

TreapNode* del(TreapNode* root, Rational key)
{
	TreapNode *l = nullptr, *r = nullptr, *m = nullptr;
	root->split(key-Rational(1,1000), l, r);
	r->split(key, m, r);
	return merge(l, r);
}

void print(const std::string& prefix, const TreapNode* node, bool isLeft, bool isRoot)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		if (!isRoot)
			std::cout << (isLeft ? "L|---" : "R|----");

		else std::cout << "|---";

		// print the value of the node
		std::cout << "(" << node->key << "; " << node->priority << ")" << std::endl;

		// enter the next tree level - left and right branch
		print(prefix + (isLeft ? "|   " : "    "), node->left, true, false);
		print(prefix + (isLeft ? "|   " : "    "), node->right, false, false);
	}
}


void print(const TreapNode* node)
{
	print("", node, false, true);
}