/////////////////////////////////////////////////////
// Berkant Erbey 141044030
// 30.11.2016 
// HW6
// CPUProgramDyn.cpp
////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "CPUProgramDyn.h"


namespace CPUProgramDynErbey
{
	CPUProgramDyn::CPUProgramDyn(string fileName):fName(fileName),line(nullptr)
	{
		ReadFile(fName);
	}
	CPUProgramDyn::CPUProgramDyn():line(nullptr)
	{
		/*Empty*/
	}
	CPUProgramDyn::CPUProgramDyn(int option):line(nullptr)
	{
		/*Empty*/
	}
	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& CPUProgObj)
	{
		setSize(CPUProgObj.size());
		line = new string[CPUProgObj.size()];
		for(int i = 0; i < size(); ++i)
			line[i] = CPUProgObj.line[i];

	}
	void CPUProgramDyn::ReadFile(string fileName)
	{
		fstream inp;
		string temp; //getline fonksiyonu icin temp string
		
		inp.open(fileName);
		int i = 0;//Line index

		//İlk acip kapamada satir sayisini buluyoruz
		if(inp.is_open() == 0)
			cerr << "***File can not opened***" << endl;
		else
		{
			while(getline(inp,temp))//Dosya sonuna kadar satirlari al
				++lineNum;
			inp.close();
		}
		
		//ikinci acip kapamada temp e okuduklarimizi line a atiyoruz.
		inp.open(fileName);
		
		if(inp.is_open() == 0)
			cerr << "***File can not opened(Second opening)***" << endl;
		else
		{	
			i = 0;
			
			line = new string[lineNum];

			while(getline(inp,temp))//Dosya sonuna kadar satirlari al
			{
				line[i] = temp;
				++i;
			}
			inp.close();
		}
	}
	string CPUProgramDyn::getLine(int currLine)
	{
		return instruction = line[currLine]; 
	}
	/*string* CPUProgram::getAllLine()
	{
		return line;
	}*/ //HW4 te gecerliydi HW5 te iptal oldu HW6 da da yok.
	const int CPUProgramDyn::size() const//bu vectorun size fonksiyonunu kullanıyor ise yaramaz
	{
		return lineNum;
	}
	int CPUProgramDyn::setSize(int lSize)
	{
		lineNum = lSize;
		return lineNum;
	}
	const string& CPUProgramDyn::operator [](int lNum) const 
	{
		
		if(line == nullptr)
			cout << "ahmet";

		if(lNum  >= size() || lNum < 0)
		{
			cout << size() << " " << lNum;	
			cerr << "***Out of index error***" << endl;
			cerr << "First index of Line's dynamic array ->> "<< endl;

			return line[0];
		}

		return line[lNum];
	}
	CPUProgramDyn CPUProgramDyn::operator +(string instruction) 
	{
		CPUProgramDyn myCPUProg;
		
		int i;
		int capacity = size();

		if(instruction.empty())
			cerr << "***Empty String***" << endl;
		else
		{
			myCPUProg.line = new string[capacity + 1]; 

			for(i = 0; i < capacity; ++i)
				myCPUProg.line[i] = line[i];

			myCPUProg.line[capacity] = instruction;
			myCPUProg.setSize(capacity + 1);//
		}
		
		
		
		return myCPUProg;
	}
	CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn& yourCPUProg)
	{
		delete [] line;
		line = nullptr;
		line = new string[yourCPUProg.size()];

		for(int i = 0; i < yourCPUProg.size(); ++i)
			line[i] = yourCPUProg.line[i];

		return *this;
	}
	void CPUProgramDyn::operator +=(string instruction)
	{
		if(instruction.empty())
			cerr << "***Empty String***" << endl;
		else
		{
			string* temp;
			int capacity = size();
			temp = new string[capacity];

			for(int i = 0; i < capacity; ++i)
				temp[i] = line[i];

			delete [] line;
			line = nullptr;

			line = new string[capacity + 1];
			setSize(capacity + 1);

			for(int i = 0; i < capacity; ++i)
				line[i] = temp[i];

			delete [] temp;
			temp = nullptr;

			line[capacity] = instruction;	
		}	
	}
	CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& yourCPUProg)
	{
		CPUProgramDyn myCPUProg;
		int i,j;

		int capacity1 = size();
		int capacity2 = yourCPUProg.size();
		int capacity3 = capacity1 + capacity2;

		myCPUProg.line = new string[capacity3];
		myCPUProg.setSize(capacity3);

		for(i = 0; i < size(); ++i)
			myCPUProg.line[i] = line[i];
		
		for(j = 0; j < yourCPUProg.size(); ++j,++i)
			myCPUProg.line[i] = yourCPUProg.line[j];

		return myCPUProg;
	}
	bool CPUProgramDyn::operator ==(CPUProgramDyn& yourCPUProg) const
	{
		if(size() == yourCPUProg.size())
			return true;
		else
			return false;
	}
	bool CPUProgramDyn::operator !=(CPUProgramDyn& yourCPUProg) const
	{
		if(size() != yourCPUProg.size())
			return true;
		else
			return false;
	}
	bool CPUProgramDyn::operator <(CPUProgramDyn& yourCPUProg) const
	{
		if(size() < yourCPUProg.size())
			return true;
		else
			return false;  
	}
	bool CPUProgramDyn::operator >(CPUProgramDyn& yourCPUProg) const
	{
		if(size() > yourCPUProg.size())
			return true;
		else
			return false; 
	}
	bool CPUProgramDyn::operator <=(CPUProgramDyn& yourCPUProg) const
	{
		if(size() <= yourCPUProg.size())
			return true;
		else
			return false;
	}
	bool CPUProgramDyn::operator >=(CPUProgramDyn& yourCPUProg) const
	{
		if(size() >= yourCPUProg.size())
			return true;
		else
			return false;
	}
	ostream& operator <<(ostream& outStream,const CPUProgramDyn& yourCPUProg)
	{
		for(int i = 0; i < yourCPUProg.size(); ++i)
			cout << yourCPUProg.line[i]<< endl;
		return outStream;
	}
	CPUProgramDyn CPUProgramDyn::operator ()(int beginning,int end)
	{
		CPUProgramDyn myCPUProg;
		int i,j;//Dongu degiskenleri
		
		if(beginning < end && end <= size())
		{
			string* temp;
			int capacity = end - beginning +1;
			temp = new string[capacity];
			
			for(i = beginning, j=0; i <= end; ++i,++j)
				temp[j] = line[i];
			
			myCPUProg.line = new string[capacity];
			myCPUProg.setSize(capacity);

			for(i = 0; i < capacity; ++i)
				myCPUProg.line[i] = temp[i];

			delete [] temp;
			temp = nullptr;
		}
		else
			cerr << "***An Error occurred because the indexes***" << endl;

		return myCPUProg;
	}
	CPUProgramDyn CPUProgramDyn::operator --()//Prefix
	{
		int capacity = size() - 1;
		
		string* temp;
		temp = new string[capacity];

		int i;

		for(i = 0; i < capacity; ++i)
			temp[i] = line[i];

		delete [] line;
		line = nullptr;

		line = new string[capacity];
		setSize(capacity);
		for(i = 0; i < capacity; ++i)
			line[i] = temp[i];

		delete [] temp;
		temp = nullptr;

		return *this;
	}
	CPUProgramDyn CPUProgramDyn::operator --(int useless)//Postfix i--
	{
		int capacity = size();
		CPUProgramDyn myCPUProg;

		myCPUProg.line = new string[capacity];
		myCPUProg.setSize(capacity);

		for(int i = 0; i < capacity; ++i)
			myCPUProg.line[i] = line[i];

		delete [] line;
		line = nullptr;

		line = new string[capacity-1];

		for(int i = 0 ; i < capacity-1; ++i)
			line[i] = myCPUProg.line[i];

		return myCPUProg;
	}
	CPUProgramDyn::~CPUProgramDyn()
	{
		delete [] line;
		line = nullptr;
	}
}
