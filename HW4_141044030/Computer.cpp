/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// Computer.cpp
////////////////////////////////////////////////////

#include "Computer.h"

Computer::Computer(CPU yourCPU,CPUProgram yourCPUProgram,Memory yourMemory,int option):myCPU(option),
myCPUProgram(option),myMemory(option),optionNumComp(option)
{
	setCPU(yourCPU);
	setCPUProgram(yourCPUProgram);
	setMemory(yourMemory);

}
Computer::Computer(int option):myCPU(option),
myCPUProgram(option),myMemory(option),optionNumComp(option)
{
	/**/
}
void Computer::setCPU(CPU yourCPU)
{
	myCPU = yourCPU;
}
void Computer::setCPUProgram(CPUProgram yourCPUProgram)
{
	myCPUProgram = yourCPUProgram;
}
void Computer::setMemory(Memory yourMemory)
{
	myMemory = yourMemory;
}
void Computer::execute()
{
	if(myCPU.FindSyntaxErrors(myCPUProgram.getAllLine(),myCPUProgram.size()))
		while(!myCPU.halted())
		{	
			string instruct = myCPUProgram.getLine(myCPU.getPC()-1);
			myCPU.execute(instruct,myMemory);
		}
	else
		cerr << "***Syntax errors found.***" << endl;
	
}