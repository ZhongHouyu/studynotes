#pragma once

#define DataType int
#define MAXSIZE 1024
class Seqstack
{
public:
	DataType data[MAXSIZE];
	int top;
public:
	Seqstack();
	void initSeqStack();
	bool isEmptySeqStack();
	int pushSeqStack(DataType x);
	DataType popSeqStack();
	void printSeqStack();
	virtual ~Seqstack() {};
};
