#pragma once
#include "rational_numbers.h"

struct TreapNode //���������� ����� (��������� �� ����� ����� �������)
{
	Rational key, priority; //���� � ��������
	TreapNode* left = nullptr; //���� ���
	TreapNode *right = nullptr; //������ ���
	TreapNode(Rational key, Rational priority); //�����������
	TreapNode(Rational key, Rational priority, TreapNode* left, TreapNode* right); //����������� � ���������� ������
	/*void add(Rational key, Rational priority);
	void add(TreapNode* to_add);*/
	void split(Rational key_to_split, TreapNode* &L, TreapNode* &R); //�������� Split (����� ��������) 
};

TreapNode* search(TreapNode* root, Rational key); //�������� Search (����� ��������) 
bool check_keys(TreapNode* L, TreapNode* R); //��������, �� �� ����� � ����� L ����� �� ����� � ����� R
TreapNode* merge(TreapNode* left_head, TreapNode* right_head); //�������� Merge
TreapNode* insert(TreapNode* root, Rational key); //�������� Insert (�������)
TreapNode* del(TreapNode* root, Rational key); //�������� Delete (���������)

void print(const std::string& prefix, const TreapNode* node, bool isLeft, bool isRoot); //���� ����������� ������ � �������
void print(const TreapNode* node);

