/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// Computer.h
////////////////////////////////////////////////////

#ifndef Computer_H__
#define Computer_H__

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer
{

	public:
		
		Computer(CPU yourCPU,CPUProgram yourCPUProgram,Memory yourMemory,int option);
		Computer(int option);

		//Setters
		void setCPU(CPU yourCPU);
		void setCPUProgram(CPUProgram yourCPUProgram);
		void setMemory(Memory yourMemory);
		
		//Getters
		const CPU getCPU() {return myCPU;};
		const CPUProgram getCPUProgram (){return myCPUProgram;};
		const Memory getMemory() {return myMemory;};
	
		void execute();

	private:
		int optionNumComp; //Computer classi icin option degiskeni 
		
		//Gerekli objeler
		Memory myMemory;
		CPU myCPU;
		CPUProgram myCPUProgram;

};

#endif
