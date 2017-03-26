/////////////////////////////////////////////////////
// Berkant Erbey 
// 27.10.2016 
// HW3
// driver.cpp
////////////////////////////////////////////////////

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

int main(int argc, char const *argv[])
{
	
	CPUProgram myProg(argv[1]);
	CPU myCPU;
	
	if(argc == 3)
	{
		int option = myCPU.StringtoInt(argv[2]);
		myCPU.setOption(option);
		
		if(myCPU.FindSyntaxErrors(myProg.getAllLine(),myProg.size()))
			while(!myCPU.halted())
			{	
				string instruct = myProg.getLine(myCPU.getPC()-1);
				myCPU.execute(instruct);
			}
		else
			cerr << "***Syntax errors found.***" << endl;
	}
	else
		cout << "***Given arguments is invalid***";
	
	return 0;
}