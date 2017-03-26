/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 14.11.2016 
// HW5
// CPUProgram.h
////////////////////////////////////////////////////

#ifndef HW5CPUProgram_H__
#define HW5CPUProgram_H__


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CPUProgram
{

	public:
		//Takes the string for filename and the calls the readFile function
		CPUProgram(string filename);
		CPUProgram(int option);
		CPUProgram();
		//function takes an integer as the parameter and returns a string 
		

		//Getters

		/////////////////////////////////////////////////////////////////
		string getLine(int line);
		//that contains the program line that corresponds to the integer
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		string* getAllLine();
		//This functions returns all of lines in textfile
		// This funcyion comes from HW4 , HW5 havent this function
		/////////////////////////////////////////////////////////////////


		//Setters	

		/////////////////////////////////////////////////////////////////
		int setSize(int lSize);
		//That function returns the
		/////////////////////////////////////////////////////////////////

		



		//function returns the number of lines read from the file.
		int size() const;
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
		CPUProgram operator +(string instruction);
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
		CPUProgram operator +(const CPUProgram& yourCPUProg);
		//Operator+ that takes two programs and returns a new program 
		//that appends the second programs to the first one
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//Comparison Operators
		bool operator ==(CPUProgram& yourCPUProg) const;
		bool operator !=(CPUProgram& yourCPUProg) const;
		bool operator <(CPUProgram& yourCPUProg) const;
		bool operator >(CPUProgram& yourCPUProg) const;
		bool operator <=(CPUProgram& yourCPUProg) const;
		bool operator >=(CPUProgram& yourCPUProg) const;
		//All comparison operators ==, !=, <, >=, etc. All comparison operators 
		//compare the number of lines of the programs.
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		friend ostream& operator <<(ostream& outStream,const CPUProgram& yourCPUProg);
		//Operator>> that prints the program
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		CPUProgram operator --();//Prefix
		CPUProgram operator --(int useless);//Postfix
		//Post and pre decrement operators - - that 
		//delete the last line of the program.
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		CPUProgram operator ()(int beginning,int end);
		//Function call operator() that takes two integers and 
		//returns a new program that contains the instructions 
		//between the given integers.
		/////////////////////////////////////////////////////////////////

	private:
	
 		string instruction;
 		string fName;
		vector<string> line;
		int lineNum = 0;
};

#endif
