/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// Memory.h
////////////////////////////////////////////////////


#ifndef Memory_H__
#define Memory_H__


using namespace std;

#include <iostream>


class Memory
{

	public:
	
		Memory(int option);
		Memory();
		//Memory icin uygun getter ve setterlar
		unsigned int getMem(int index) const;



	void setMem(int index,unsigned int value) ;

	void printAll();

	private:
	
		static const int mSize = 50;
		unsigned int mArray[mSize];
		int optionNumber;

};


#endif