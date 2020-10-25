#pragma once
#include"DoubleNode.h"
class CircleDoubleLink
{
public:
	DoubleNode* head;
	DoubleNode* end;
	int lenth;
public:
	CircleDoubleLink();
	~CircleDoubleLink();
	int insertNode(int data, int position);
	int deleteNode(int data, int position);
	int printLink();
};

