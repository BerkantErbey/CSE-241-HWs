/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 04.11.2016 
// HW4
// CPU.h
////////////////////////////////////////////////////
#ifndef CPU_H__
#define CPU_H__

#include <iostream>
#include <string>
#include "Memory.h"

using namespace std;

class CPU
{
	
	public:

	//Appropriate Constructors
	CPU(int option);
	CPU();

	//--Getters--//
	//---------------------------------------------//
	
	//Getters for all registers and PC
	const int getPC() const;
	const int getRegs(int index) const;
	//int getLineNum();
	const int getHalt() const;
	const int getOption() const;
	
	//---------------------------------------------//
	//--Setters--//
	//---------------------------------------------//
	//Setters for all registers and PC
	void setRegs(int index,int value);
	void setPC(int value);
	
	string* getAllLine();
	void setLineNum();
	void setHalt();
	void setOption(int value);
	//---------------------------------------------//

	

	//Halted function returns true if the last instruction executed halted the cpu
	const int halted() const;

	//Execute function takes a string that contains an instruction line,execute it and advances the pc accordingly
	//for example myCpu.execute("mov r1 , r100") puts the value of 100 to register 1
	void execute(string line,Memory& myMemory);

	//FindSyntax Erros given string array with using lnum
	//returns the true if no error,otherwise return false 
	bool FindSyntaxErrors(string *str,const int lnum);
	void print() const;
	/*String to Integer Converting*/
	const int StringtoInt(const string &str) const;

private:
	
	//print function that prints all the registers and the pc
	
	
	//---Edits the giving line---/
	//---------------------------------------------//
	void LineEdit(string &str);
	void RemoveLeadingSpace(string &str);
	void AddSpacetoComma(string &str);
	void RemoveSmcAndAfter(string &str);
	void toUpper(string &str);
	void RemoveLastSpace(string &str);
	//---------------------------------------------//
	
	//Parsing the given line into four piece//
	//---------------------------------------------//
	void TextParser(const string &str,string &word1,string &word2,string &word3,string &word4);
	//---------------------------------------------//
	//Power  x^y
	int Power(const int x,const int y) const;
	
	//R5->5
	const int NumExtract(const string &str) const;
	const bool RegisterCheck(const string &str) const;
	const bool MemoryCheck(const string &str) const;

	//Execution Functions
	//---------------------------------------------//
	const void InsPrn(const string &str,const Memory& myMemory) const;
	int InsJmp(const string &str1,const string &str2) const;
	void InsAdd(const string &str1,const string &str2,Memory& myMemory);
	void InsSub(const string &str1,const string &str2,Memory& myMemory);
	void InsMov(const string &str1,const string &str2,Memory& myMemory);
	int InsJpn(const string &str1,const string &str2) const;
	//---------------------------------------------//



	static const int rSize = 5;	//Register Dizisinin boyutu
	static const int lSize = 200;//Maximum line size in Instructions.txt

	string instruction; // MOV R1,R2
	string line[lSize];	//Metin dosyasini depoladigimiz string dizisi
	string word1,word2,word3,word4;
	
	int optionNum;
	int rArray[rSize];//Register dizisi 
	int PC = 1; //Program counter
	int haltVal = 0; // Halt value flag
	
};

#endif
