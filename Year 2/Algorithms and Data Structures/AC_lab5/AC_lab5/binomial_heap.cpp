#include "binomial_heap.h"

BinomialNode::BinomialNode(Rational key)
{
	this->key = key;
}

BinomialNode::BinomialNode(Rational key, int degree, BinomialNode* parent, BinomialNode* child, BinomialNode* sibling)
{
	this->key = key;
	this->degree = degree;
	this->parent = parent;
	this->child = child;
	this->sibling = sibling;
}

BinomialHeap::BinomialHeap()
{
	head = nullptr;
}

BinomialHeap::BinomialHeap(const BinomialHeap& heap)
{
	this->head = nullptr;

	BinomialNode* iter = heap.head;
	while (iter != nullptr)
	{
		this->push_back(CloneBinomialTree(iter));
		iter = iter->sibling;
	}
}

BinomialHeap& BinomialHeap::operator=(const BinomialHeap& heap)
{
	this->head = nullptr;

	BinomialNode* iter = heap.head;
	while (iter != nullptr)
	{
		this->push_back(CloneBinomialTree(iter));
		iter = iter->sibling;
	}

	return *this;
}

BinomialNode* BinomialHeap::find_min()
{
	BinomialNode* iter = this->head;
	BinomialNode* min = iter;
	while (iter != nullptr)
	{
		if (iter->key <= min->key) min = iter;
		iter = iter->sibling;
	}
	return min;
}

void BinomialHeap::push_back(BinomialNode* to_add)
{
	to_add->sibling = nullptr;
	if (this->head == nullptr)
		this->head = to_add;

	else
	{
		BinomialNode* iter = this->head;
		while (iter->sibling != nullptr)
			iter = iter->sibling;
		iter->sibling = to_add;
	}
}

/*BinomialNode* BinomialHeap::reverse(BinomialNode* temp)
{
	if (temp->sibling != nullptr)
	{
		this->head = this->reverse(temp->sibling);
		temp->sibling->sibling = temp;
		temp->sibling = nullptr;
		return this->head;
	}
	return temp;
}*/

BinomialHeap BinomialHeap::insert(BinomialNode* to_insert)
{
	BinomialHeap temp;
	temp.head = to_insert;
	return merge(*this, temp);
}

void BinomialHeap::extract_min()
{
	BinomialHeap temp;
	BinomialHeap child_heap;

	BinomialNode* min = this->find_min();
	BinomialNode* iter = min->child;
	while (iter != nullptr)
	{
		BinomialNode* temp_iter = iter->sibling;

		iter->parent = nullptr;
		iter->sibling = nullptr;
		temp.insert(CloneBinomialTree(iter));

		iter = temp_iter;
	}

	iter = this->head;
	while (iter != nullptr)
	{
		if (iter != min)
		{
			BinomialNode* temp_iter = iter->sibling;

			iter->sibling = nullptr;
			child_heap.insert(CloneBinomialTree(iter));

			iter = temp_iter;
		}
		else iter = iter->sibling;
	}

	*this = merge(temp, child_heap);
}

void BinomialHeap::add(Rational key)
{
	BinomialHeap temp;
	temp.push_back(new BinomialNode(key));
	merge(*this, temp);
}

BinomialHeap::~BinomialHeap()
{
	destroy_tree(this->head);
}

BinomialNode* CloneBinomialTree(BinomialNode* root)
{
	if (!root) return nullptr;

	return new BinomialNode(root->key,
		root->degree,
		root->parent,
		CloneBinomialTree(root->child),
		CloneBinomialTree(root->sibling));
}


void link(BinomialNode*& left, BinomialNode*& right)
{
	left->parent = right;
	left->sibling = right->child;
	right->child = left;
	right->degree += 1;
	return;
}

BinomialHeap merge(BinomialHeap& x, BinomialHeap& y)
{
	BinomialHeap result;
	BinomialNode* iter_x = x.head;
	BinomialNode* iter_y = y.head;
	while (iter_x != nullptr && iter_y != nullptr)
	{
		if (iter_x->degree == iter_y->degree)
		{
			if (iter_x->key <= iter_y->key)
			{
				result.push_back(CloneBinomialTree(iter_y));
				iter_y = iter_y->sibling; 
			}

			else
			{
				result.push_back(CloneBinomialTree(iter_x));
				iter_x = iter_x->sibling;
			}
		}

		else
		{
			if (iter_x->degree < iter_y->degree)
			{
				result.push_back(CloneBinomialTree(iter_x));
				iter_x = iter_x->sibling;
			}

			else
			{
				result.push_back(CloneBinomialTree(iter_y));
				iter_y = iter_y->sibling;
			}
		}
	}

	while (iter_x != nullptr)
	{
		result.push_back(CloneBinomialTree(iter_x));
		iter_x = iter_x->sibling;
	}

	while (iter_y != nullptr)
	{
		result.push_back(CloneBinomialTree(iter_y));
		iter_y = iter_y->sibling;
	}

	x = result;

	if (x.head == nullptr)
		return x;

	BinomialNode* prev_temp = nullptr;
	BinomialNode* temp = x.head;
	BinomialNode* next_temp = x.head->sibling;

	while (next_temp != nullptr)
	{
		if (temp->degree != next_temp->degree ||
			(next_temp->sibling != nullptr && next_temp->sibling->degree == temp->degree))
		{
			prev_temp = temp;	
			temp = next_temp;
		}

		else
		{
			if (temp->key <= next_temp->key)
			{
				temp->sibling = next_temp->sibling;
				link(next_temp, temp);
			}

			else
			{
				if (prev_temp == nullptr) x.head = next_temp;
				else prev_temp->sibling = next_temp;
				link(temp, next_temp);
				temp = next_temp;
			}
		}
		
		next_temp = temp->sibling;
	}

	return x;
}

void destroy_tree(BinomialNode* root)
{
	if (root == nullptr) return;
	destroy_tree(root->child);
	destroy_tree(root->sibling);
	delete root;
}

void printTree(BinomialNode* h)
{
	while (h)
	{
		std::cout << h->key << "  ";
		printTree(h->child);
		h = h->sibling;
	}
}

void decrease_key(BinomialNode*& h, Rational key)
{
	if(h->key < key)
		throw std::domain_error{ "You try to increment key by decreasing it" };

	h->key = key;
	BinomialNode* x = h;
	BinomialNode* y = h->parent;
	while (y != nullptr && x->key < y->key)
	{
		auto temp = x->key;
		x->key = y->key;
		y->key = temp;
	}
}

void printHeap(BinomialHeap heap)
{
	BinomialNode* iter = heap.head;
	std::cout << "\nPRINTING BINOMIAL HEAP...";
	while (iter != nullptr)
	{
		std::cout << "\nCurrent tree degree = " << iter->degree << "\n";
		std::cout << iter->key << "  ";
		printTree(iter->child);
		iter = iter->sibling;
		std::cout << "\n";
	}
	std::cout << "\n";
}

