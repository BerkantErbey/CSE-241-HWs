/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 14.11.2016 
// HW5
// CPUProgram.cpp
////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "CPUProgram.h"

CPUProgram::CPUProgram(string fileName):fName(fileName)
{
	ReadFile(fName);
}
CPUProgram::CPUProgram()
{
	/*Empty*/
}
CPUProgram::CPUProgram(int option)
{
	/*Empty*/
}
void CPUProgram::ReadFile(string fileName)
{
	
	fstream inp;
	string temp; //getline fonksiyonu icin temp string
	inp.open(fileName);
	
	if(inp.is_open() == 0)
		cerr << "***File can not opened***" << endl;
	else
		while(getline(inp,temp))//Dosya sonuna kadar satirlari al
		{
			line.push_back(temp);
			++lineNum;
		}

	inp.close();
}
string CPUProgram::getLine(int currLine)
{
	return instruction = line[currLine]; 
}
/*string* CPUProgram::getAllLine()
{
	return line;
} HW4 te gecerliydi HW5 te iptal oldu*/
int CPUProgram::size() const
{
	return line.size();//Vectorun size fonksiyonu
}
int CPUProgram::setSize(int lSize)
{
	
	lineNum = lSize;
	return lineNum;
}
const string& CPUProgram::operator [](int lNum) const 
{
	//Hata olursa ilk satiri dondurur
	if(lNum  >= line.size() || lNum < 0)
	{
		cerr << "***Out of index error***" << endl;
		cerr << "First index of vector ->> ";
		return line[0];
	}

	return line[lNum];
}
CPUProgram CPUProgram::operator +(string instruction) 
{
	CPUProgram yourCPUProg;

	if(instruction.empty())
		cerr << "***Empty String***" << endl;
	else
	{
		yourCPUProg = *this;
		yourCPUProg.line.push_back(instruction);
	}
	setSize(yourCPUProg.line.size());

	return yourCPUProg;
}
void CPUProgram::operator +=(string instruction)
{
	if(instruction.empty())
		cerr << "***Empty String***" << endl;
	else
	{
		setSize(lineNum+1);//
		line.push_back(instruction);
	}	
}
CPUProgram CPUProgram::operator +(const CPUProgram& yourCPUProg)
{
	CPUProgram myCPUProg;
	unsigned int i;
	string temp;
	
	myCPUProg = *this;

	for(i = 0; i < yourCPUProg.line.size(); ++i)
	{
		temp = yourCPUProg.line[i];
		myCPUProg.line.push_back(temp);	
	}

	setSize(myCPUProg.line.size());
	
	return myCPUProg;
}
bool CPUProgram::operator ==(CPUProgram& yourCPUProg) const
{
	if(line.size() == yourCPUProg.line.size())
		return true;
	else
		return false;
}
bool CPUProgram::operator !=(CPUProgram& yourCPUProg) const
{
	if(line.size() != yourCPUProg.line.size())
		return true;
	else
		return false;
}
bool CPUProgram::operator <(CPUProgram& yourCPUProg) const
{
	if(line.size() < yourCPUProg.line.size())
		return true;
	else
		return false;  
}
bool CPUProgram::operator >(CPUProgram& yourCPUProg) const
{
	if(line.size() > yourCPUProg.line.size())
		return true;
	else
		return false; 
}
bool CPUProgram::operator <=(CPUProgram& yourCPUProg) const
{
	if(line.size() <= yourCPUProg.line.size())
		return true;
	else
		return false;
}
bool CPUProgram::operator >=(CPUProgram& yourCPUProg) const
{
	if(line.size() >= yourCPUProg.line.size())
		return true;
	else
		return false;
}
ostream& operator <<(ostream& outStream,const CPUProgram& yourCPUProg)
{
	for(unsigned int i = 0; i < yourCPUProg.line.size(); ++i)
		cout << yourCPUProg.line[i]<< endl;
	return outStream;
}
CPUProgram CPUProgram::operator ()(int beginning,int end)
{
	CPUProgram myCPUProg;
	string temp;
	
	if(beginning < end && end <= static_cast<int>(line.size()))
	{
		for(int i = beginning- 1; i < end; ++i)
		{
			temp = line[i];
			myCPUProg.line.push_back(temp);
		}
	}
	else
		cerr << "***An Error occurred because the indexes***" << endl;

	return myCPUProg;
}
CPUProgram CPUProgram::operator --()//Prefix
{
	line.pop_back();
	return *this;
}
CPUProgram CPUProgram::operator --(int useless)//Postfix
{
	CPUProgram myCPUProg = *this;
	myCPUProg.line.pop_back();
	return myCPUProg;
}