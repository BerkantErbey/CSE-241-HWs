/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// Memory.cpp
////////////////////////////////////////////////////


#include "Memory.h"
using namespace std;

Memory::Memory(int option):optionNumber(option)
{
	for(int i = 0; i < 50; ++i)
		setMem(i,0);	
}
unsigned int Memory::getMem(int index) const
{
	return mArray[index];
}
void Memory::setMem(int index,unsigned int value)
{
	mArray[index] = value;
}
void Memory::printAll()
{
	for(int i = 0; i < mSize; ++i)
	{
			if( i % 5 == 0)
				cout << endl;
		cout << "\t" << "[" << i << "]" << " -> " << mArray[i];;
	}
	cout << endl;
}