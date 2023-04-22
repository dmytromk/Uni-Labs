#pragma once
#include "rational_numbers.h"
#include <iostream>

struct BinomialNode //��������� ������
{
	Rational key; //����
	int degree = 0; //������
	BinomialNode* parent = nullptr; //������
	BinomialNode* child = nullptr; //������ ���� ���
	BinomialNode* sibling = nullptr; //������ ����
	BinomialNode(Rational key); //�����������
	BinomialNode(Rational key, int degree, BinomialNode* parent, BinomialNode* child, BinomialNode* sibling); //overload ������������
};

BinomialNode* CloneBinomialTree(BinomialNode* root); //���������� ������
void link(BinomialNode*& left, BinomialNode*& right); //��'������ �����
void destroy_tree(BinomialNode* root); //�������� ������
void printTree(BinomialNode* h); //���� ������
void decrease_key(BinomialNode*& h, Rational key); //��������� ����� ����� � �����


struct BinomialHeap //��������� ������
{
	BinomialNode* head; //�������� �� ����� ������ ����

	BinomialHeap(); //�����������
	BinomialHeap(const BinomialHeap& heap); //overload ������������
	BinomialHeap& operator= (const BinomialHeap& heap); //�������� = ��� ������

	BinomialNode* find_min(); //������� ������ ������
	void push_back(BinomialNode* to_add); //�������� ������� ��������� ������ � ������
	//BinomialNode* reverse(BinomialNode* temp);
	BinomialHeap insert(BinomialNode* to_insert); //������� insert ��� �����
	void extract_min(); //������� extract-min - ��������� ���������� ����� 
	void add(Rational key); //������� insert ��� key
	~BinomialHeap(); //����������
};


BinomialHeap merge(BinomialHeap& x, BinomialHeap& y); //merge �����
void printHeap(BinomialHeap heap); // ���� ������ � �������


