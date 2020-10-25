#include "Seqstack.h"
#include<iostream>
using namespace std;
Seqstack::Seqstack() 
{
	cout << "created a Seqstack!" << endl;
}
void Seqstack::initSeqStack() 
{
	this->top = -1;
	cout << "initSeqstack!" << endl;
}
bool Seqstack::isEmptySeqStack()
{
	if (this->top == -1) {
		cout << "stack empty!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}
int Seqstack::pushSeqStack( DataType x)
{
	if (this->top < MAXSIZE) {
		this->top++;
		this->data[this->top] = x;
		cout << "push succeed" << endl;
		return 0;
	}
	else {
		cout << "data out of size" << endl;
		return 1;
	}
}
int Seqstack::popSeqStack()
{
	if (!this->isEmptySeqStack()) {
		DataType x = this->data[this->top];
		this->top--;
		return x;
	}
	else
	{
		cout << "stack empty!" << endl;
	}
}
void Seqstack::printSeqStack()
{
	int i = this->top;
	while (i > -1) {
		cout << this->data[i] << endl;
		i--;
	}
}