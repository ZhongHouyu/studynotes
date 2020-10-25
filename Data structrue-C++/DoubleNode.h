#pragma once
class DoubleNode
{
public:
	DoubleNode* prior_node;
	int data;
	DoubleNode* next_node;
	DoubleNode() {
		this->data = 0;
		this->prior_node = nullptr;
		this->next_node = nullptr;
	}
	~DoubleNode() {};
};

