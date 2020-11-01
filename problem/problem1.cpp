#include "test1.h"
#include<iostream>
using namespace std;
unsigned long fe(unsigned long fe1,unsigned long fe2,unsigned long temp3)
{
	if (temp3 > 2) {
		return fe(fe1,fe2,temp3 - 1) + fe(fe1,fe2,temp3 - 2);
	}
	if (temp3 == 2)return fe2;
	if (temp3 == 1)return fe1;
}
void res(int input_number) 
{
	
	unsigned long temp2[2^32][2] = { 0 };
	unsigned long t = 0;
	for (unsigned long fe1 = 1; fe1 < input_number; fe1 ++) {
		for (unsigned long fe2 = 1; fe2 < input_number; fe2++) {
			
			unsigned long temp1 = input_number+1;
			while(temp1>2)
			{
				
				if (input_number == fe(fe1, fe2, temp1)) {
					temp2[temp1-1][1]++;
					temp2[temp1-1][0] = temp1;
					t=temp1;
				}
				temp1--;
			}
		}
	}
	for (unsigned long fe1 = 2; fe1 <= t; fe1++) {
		if (temp2[fe1][1] != 0) {
			cout << temp2[fe1][0] << temp2[fe1][1] << endl;
		}
	}
}