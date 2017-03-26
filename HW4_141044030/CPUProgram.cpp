/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// CPUProgram.cpp
////////////////////////////////////////////////////

using namespace std;
#include "CPUProgram.h"
#include <fstream>

CPUProgram::CPUProgram(string fileName):fName(fileName)
{
	ReadFile(fName);
}
CPUProgram::CPUProgram(int option)
{
	/*Empty*/
}
void CPUProgram::ReadFile(string fileName)
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