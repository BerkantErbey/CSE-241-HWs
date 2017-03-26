/////////////////////////////////////////////////////
// Berkant Erbey 
// 25.10.2016 
// HW3
// CPUProgram.cpp
////////////////////////////////////////////////////

using namespace std;
#include "CPUProgram.h"

CPUProgram::CPUProgram(string fileName):fName(fileName)
{
	readFile(fName);
}
const void CPUProgram::readFile(string fileName)
{
	fstream inp;
	inp.open(fileName);

	if(inp.is_open() == 0)
		cerr << "***File can not opened***" << endl;
	else
		while(getline(inp,line[lineNum]))//Dosya sonuna kadar satirlari al
			++lineNum;
	
	inp.close();
}
string CPUProgram::getLine(int currLine)
{
	return instruction = line[currLine]; 
}
const int CPUProgram::size() const
{
	return lineNum;
}
string* CPUProgram::getAllLine()
{
	return line;
}