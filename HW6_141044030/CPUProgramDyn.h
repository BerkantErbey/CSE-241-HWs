/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 30.11.2016 
// HW6
// CPUProgramDyn.h
////////////////////////////////////////////////////

#ifndef CPUProgramDyn_H__
#define CPUProgramDyn_H__

#include <fstream>
#include <iostream>

#include <string>
using namespace std;

namespace CPUProgramDynErbey
{
	class CPUProgramDyn
	{

		public:
			//Takes the string for filename and the calls the readFile function
			CPUProgramDyn(string filename);
			CPUProgramDyn(int option);
			CPUProgramDyn();
			CPUProgramDyn(const CPUProgramDyn& CPUProgObj);
			//function takes an integer as the parameter and returns a string 
		
			//Getters

			/////////////////////////////////////////////////////////////////
			string getLine(int line);
			//that contains the program line that corresponds to the integer
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			//string* getAllLine();
			//This functions returns all of lines in textfile
			// This funcyion comes from HW4 , HW5 havent this function
			/////////////////////////////////////////////////////////////////

			//Setters	

			/////////////////////////////////////////////////////////////////
			int setSize(int lSize);
			//That function returns the
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			//function returns the number of lines read from the file.
			const int size() const;
			//function takes a string file name as a parameter, reads the program file and stores
			void ReadFile(string fileName);
		
			//functions returns the string array for the input text file storing
			//string* getAllLine();

			/////////////////////////////////////////////////////////////////
			const string& operator [](int lNum) const;
			//Operator[] that takes an integer and works like the getLine function.
			//It returns the program line as a string.
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			CPUProgramDyn operator +(string instruction);
			//Operator+ that takes a CPUProgram and an instruction line as a string.
			//It returns a new CPUProgram that has the original CPUProgram with appended 
			//last line from the parameter string.
			/////////////////////////////////////////////////////////////////
		
			/////////////////////////////////////////////////////////////////
			void operator +=(string instruction);
			//Operator+= that takes an instruction line as a string and 
			//appends the instruction to the end of the program.
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			CPUProgramDyn operator +(const CPUProgramDyn& yourCPUProg);
			//Operator+ that takes two programs and returns a new program 
			//that appends the second programs to the first one
			/////////////////////////////////////////////////////////////////

			CPUProgramDyn& operator =(const CPUProgramDyn& yourCPUProg);

			/////////////////////////////////////////////////////////////////
			//Comparison Operators
			bool operator ==(CPUProgramDyn& yourCPUProg) const;
			bool operator !=(CPUProgramDyn& yourCPUProg) const;
			bool operator <(CPUProgramDyn& yourCPUProg) const;
			bool operator >(CPUProgramDyn& yourCPUProg) const;
			bool operator <=(CPUProgramDyn& yourCPUProg) const;
			bool operator >=(CPUProgramDyn& yourCPUProg) const;
			//All comparison operators ==, !=, <, >=, etc. All comparison operators 
			//compare the number of lines of the programs.
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			friend ostream& operator <<(ostream& outStream,const CPUProgramDyn& yourCPUProg);
			//Operator>> that prints the program
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			CPUProgramDyn operator --();//Prefix
			CPUProgramDyn operator --(int useless);//Postfix
			//Post and pre decrement operators - - that 
			//delete the last line of the program.
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			CPUProgramDyn operator ()(int beginning,int end);
			//Function call operator() that takes two integers and 
			//returns a new program that contains the instructions 
			//between the given integers.
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			~CPUProgramDyn();
			//Destructor
			/////////////////////////////////////////////////////////////////

		private:
	
 			string instruction;	
 			string fName;		//Filename
		
			string* line;  		
		
		
			int lineNum = 0;
	};

}//CPUProgramDynErbey



#endif
