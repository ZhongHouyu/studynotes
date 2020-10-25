#include "CircleDoubleLink.h"
#include "DoubleNode.h"
#include <iostream>
using namespace std;
CircleDoubleLink::CircleDoubleLink()
{	
	this->head = new DoubleNode();
	this->end = new DoubleNode();
	this->head->next_node = this->end;
	this->head->prior_node = this->end;
	this->end->next_node = this->head;
	this->end->prior_node = this->head;
	this->head->data = 0;
	this->end->data = 0;
	this->lenth = 0;
}
int CircleDoubleLink::insertNode(int data,int position)
{
	position = position % (this->lenth+1);
	DoubleNode* n = new DoubleNode();
	DoubleNode* t = this->head;
	n->data = data;
	for (int i = 0; i < position; i++) {
		t = t->next_node;
	}
	n->prior_node = t;
	n->next_node = t->next_node;
	t->next_node->prior_node = n;
	t->next_node = n;
	this->lenth++;
	return 0;
}
int CircleDoubleLink::deleteNode(int data, int position)
{
	position = position % this->lenth;
	
	DoubleNode* t = this->head;
	for (int i = 0; i < position; i++) {
		t = t->next_node;
	}
	if (!t->data == data) {
		cout << "data error:no such data£º" << data << endl;
		return 1;
	}
	else {
		t->prior_node->next_node = t->next_node;
		t->next_node->prior_node = t->prior_node;
		delete t;
		this->lenth--;
		return 0;
	}
}
int CircleDoubleLink::printLink()
{
	DoubleNode* n;
	n = head;
	for (int i = 0; i < this->lenth; i++) {
		n = n->next_node;
		cout << n->data << endl;
	}
	return 0;
}
CircleDoubleLink::~CircleDoubleLink() 
{
	delete this->head;
	delete this->end;

};

/*test code:
#include <iostream>
#include"CircleDoubleLink.h"
using namespace std;
int main()
{
	CircleDoubleLink*  circleDoubleLink = new CircleDoubleLink();
	circleDoubleLink->insertNode(1, 1);
	circleDoubleLink->insertNode(2, 2);
	circleDoubleLink->printLink();
	circleDoubleLink->deleteNode(1, 1);
	circleDoubleLink->printLink();
	delete circleDoubleLink;
	return 0;
}*/