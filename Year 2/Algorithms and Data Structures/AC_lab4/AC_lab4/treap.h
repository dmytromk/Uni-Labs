#pragma once
#include "rational_numbers.h"

struct TreapNode //Декартовий вузол (посилання на корінь слугує деревом)
{
	Rational key, priority; //ключ і пріоритет
	TreapNode* left = nullptr; //лівий син
	TreapNode *right = nullptr; //правий син
	TreapNode(Rational key, Rational priority); //конструктор
	TreapNode(Rational key, Rational priority, TreapNode* left, TreapNode* right); //конструктор з допоміжними полями
	/*void add(Rational key, Rational priority);
	void add(TreapNode* to_add);*/
	void split(Rational key_to_split, TreapNode* &L, TreapNode* &R); //операція Split (пошук елемента) 
};

TreapNode* search(TreapNode* root, Rational key); //операція Search (пошук елемента) 
bool check_keys(TreapNode* L, TreapNode* R); //перевірка, що всі ключі в дереві L менші за ключі в дереві R
TreapNode* merge(TreapNode* left_head, TreapNode* right_head); //операція Merge
TreapNode* insert(TreapNode* root, Rational key); //операція Insert (вставка)
TreapNode* del(TreapNode* root, Rational key); //операція Delete (видалення)

void print(const std::string& prefix, const TreapNode* node, bool isLeft, bool isRoot); //вивід декартового дерева в консоль
void print(const TreapNode* node);

