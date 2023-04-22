#pragma once
#include "rational_numbers.h"
#include <iostream>

struct BinomialNode //біноміальне дерево
{
	Rational key; //ключ
	int degree = 0; //степінь
	BinomialNode* parent = nullptr; //батько
	BinomialNode* child = nullptr; //крайній лівий син
	BinomialNode* sibling = nullptr; //правий брат
	BinomialNode(Rational key); //конструктор
	BinomialNode(Rational key, int degree, BinomialNode* parent, BinomialNode* child, BinomialNode* sibling); //overload конструктора
};

BinomialNode* CloneBinomialTree(BinomialNode* root); //клонування дерева
void link(BinomialNode*& left, BinomialNode*& right); //об'днання дерев
void destroy_tree(BinomialNode* root); //знищення дерева
void printTree(BinomialNode* h); //вивід дерева
void decrease_key(BinomialNode*& h, Rational key); //зменшення ключа вузла в дереві


struct BinomialHeap //біноміальна піраміда
{
	BinomialNode* head; //вказівник на перше дерево купи

	BinomialHeap(); //конструктор
	BinomialHeap(const BinomialHeap& heap); //overload конструктора
	BinomialHeap& operator= (const BinomialHeap& heap); //оператор = для піраміди

	BinomialNode* find_min(); //функція пошуку мінімума
	void push_back(BinomialNode* to_add); //допоміжна функція додавання дерева в піраміду
	//BinomialNode* reverse(BinomialNode* temp);
	BinomialHeap insert(BinomialNode* to_insert); //функція insert для вузла
	void extract_min(); //функція extract-min - видалення мінімального вузла 
	void add(Rational key); //функція insert для key
	~BinomialHeap(); //деструктор
};


BinomialHeap merge(BinomialHeap& x, BinomialHeap& y); //merge пірамід
void printHeap(BinomialHeap heap); // вивід піраміди в консоль


