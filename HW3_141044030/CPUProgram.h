/////////////////////////////////////////////////////
// Berkant Erbey 
// 25.10.2016 
// HW3
// CPUProgram.h
////////////////////////////////////////////////////

#ifndef CPUProgram_H__
#define CPUProgram_H__


#include <iostream>
#include <fstream>
using namespace std;



class CPUProgram
{

	public:
		
		//Takes the string for filename and the calls the readFile function
		CPUProgram(string filename);

		//function takes an integer as the parameter and returns a string 
		//that contains the program line that corresponds to the integer.
		string getLine(int line);
		
		//function returns the number of lines read from the file.
		const int size() const;
		
		//functions returns the string array for the input text file storing
		string* getAllLine();

	private:
		
		//function takes a string file name as a parameter, reads the program file and stores
		//all the program instructions.
		const void readFile(string fileName);

 		string instruction;
 		string fName;
		static const int lineNumber = 200;
		string line[lineNumber];
		int lineNum = 0;
		fstream inp;
};


#endif
