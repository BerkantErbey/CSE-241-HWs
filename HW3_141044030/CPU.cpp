/////////////////////////////////////////////////////
// Berkant Erbey 
// 24.10.2016 
// HW3
// CPU.cpp
////////////////////////////////////////////////////


//#include <iostream>
//#include <cstdlib>
//#include <string>
#include "CPU.h"


CPU::CPU()
{
	for(int i= 0; i<5; ++i)
	{
		setRegs(i,0);
	}
}
const int CPU::getRegs(int index) const
{
	return rArray[index];
}
const int CPU::getPC() const
{
	return PC;
}
const int CPU::getOption() const 
{
	return optionNum;
}
void CPU::setOption(int value)
{
	optionNum = value;
}
void CPU::setRegs(int index,int value)
{
	rArray[index] = value;
}
void CPU::setPC(int value)
{
	PC = value;
}

void CPU::print() const
{
	for(int i = 0; i < 5;++i)
	{
		cout <<"\t" << "R" << i+1 << " = " << getRegs(i) ;
	}
	
	cout << "\tPC = " << getPC() << endl;
}
const int CPU::halted() const
{
	return getHalt();
}
void CPU::execute(string instruction)
{

	string word1,word2,word3,word4;//Parcalari attigimiz stringler
	int i = PC;


	//cout << "executein icinde optiondan once" << endl;
	
	if(optionNum == 1)
	{
		cout << i << "\t" ;
		cout << instruction << "\t" ;
	}


	//instruction = line[PC];
	TextParser(instruction,word1,word2,word3,word4);
	//cout << "Textparser sonrasi" << endl;
	
	if(word1 == "HLT" || word1 == "PRN" ||word1 == "JMP" || word1 == "ADD" || word1 == "SUB" || word1 == "MOV")
	{
		
		if(word1 == "HLT")
		{
			print();
			setHalt();
			return;
		}
		
		else if(word1 == "PRN")
			InsPrn(word2);
		else if(word1 == "JMP")
		{
			if(InsJmp(word2,word4) != -1)
			{
				//PC = InsJmp(word2,word4,rArray) - 1;
				int value = InsJmp(word2,word4) - 1;
				setPC(value);
			}
		}
		else if(word1 == "ADD")
			InsAdd(word2,word4);
		else if(word1 == "SUB")
			InsSub(word2,word4);
		else if(word1 == "MOV")
			InsMov(word2,word4);
	}

	if(optionNum == 1)//optionNum 1se arrayi bas
		print();

	word1.erase();//Fonksiyondan cikmadan wordleri sil
	word2.erase();
	word3.erase();
	word4.erase();

	//++PC;
	int lValue = getPC();
	setPC(lValue+1);
	
	return;
}
bool CPU::FindSyntaxErrors(string *line,const int lnum)
{
	int flag = 0;//Dogru satir sayisi tutan degisken
	int hltfound = 0;//Hlt nin bulunup bulunmadigini tutan degisken
	string word1,word2,word3,word4;//Bir satiri boldugumuz parcalar
	
	cout << endl;
	
	for(int i = 0 ; i < lnum; ++i)
	{
		//Text Edits
		LineEdit(line[i]);
		
		cout << i+1 << "   ";
		cout << line[i] << endl ;
		
		TextParser(line[i],word1,word2,word3,word4);

		if( 3 == word1.length() )
		{
			if(word1 == "MOV" || word1 == "JMP" || word1 == "PRN" || 
				word1 == "ADD" || word1 == "SUB" || word1 == "HLT")
			{
				if(word1 == "HLT") 
				{
					if(word2.empty() || word2[0] ==' ')
					{
						hltfound = 1;
						++flag;
						cout << "HLT Instruction found" << endl;
					}
					else
						cerr << "***False HLT Instruction Syntax***" << endl;
				}
				else if(word1 == "PRN") 
				{
					if(RegisterCheck(word2) && word3 == "")
						++flag;	
					else if(StringtoInt(word2) >= 0)
						++flag;
					else
						cerr << "***False PRN Instruction Syntax***" << endl;
				}
				else if(word1 == "JMP")
				{
					if(word2!="" && word3 == "" && StringtoInt(word2) >= 0 && StringtoInt(word2) <= lnum)
						++flag;
					else if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) >= 0 && StringtoInt(word4) <= lnum)
						++flag;
					else
						cerr << "***False JMP Instruction Syntax***" << endl; 
				}
				else if(word1 == "ADD")
				{
					if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) > 0)
						++flag;
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4))
					 	++flag;
					else
						cerr << "***False ADD Instruction Syntax***" << endl;
				}
				else if(word1 == "SUB")
				{
					if(RegisterCheck(word2)
					 && word3 == "," && StringtoInt(word4) > 0 )
						++flag;
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4))
					 	++flag;
					else
						cerr << "***False SUB Instruction Syntax***" << endl;
				}
				else if(word1 == "MOV")
				{
					if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) >= 0)//MOV R1,12
						++flag;
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4)) //MOV R1,R3
					 	++flag;
					else
						cerr << "***False MOV Instruction Syntax***" << endl;
				}
			}
			else
				cerr << "***Undefined Instruction" << endl;
		}
		//1 dongu tamamlandiginda yeni degerler icin wordleri bosaltma.
		word1.erase();
		word2.erase();
		word3.erase();
		word4.erase();
	}

	if(hltfound == 0)
		cerr << "***HLT parameter not found***" << endl;

	if( hltfound != 0 && flag == lnum)//HLT varsaDogru satir sayisi toplam satira esitse
		return true;

	return false;
}
void CPU::LineEdit(string &str)
{
	RemoveLeadingSpace(str);//Stringin basindaki bosluklari silen fonksiyon
	RemoveSmcAndAfter(str);//Noktali virgul ve sonrasini silen fonksiyon
	toUpper(str);//Stringteki kucuk harfleri buyuk harf yapan fonksiyon
	AddSpacetoComma(str);//Virgulun sagi ve solu bos degilse,
						//sagina ve soluna bosluk atan fonksiyon
	RemoveLastSpace(str);//Stringin sonundaki bosluklari silen fonksiyon
}
void CPU::RemoveLeadingSpace(string &str)
{
	int i = str.find_first_not_of(" ");
	str.erase(0,i);
}
void CPU::RemoveSmcAndAfter(string &str)
{
	int i = str.find_first_of(";");
	
	if( i != -1)//Noktali virgul varsa
		str.erase(i);// i. yerden itibaren sil
}
void CPU::toUpper(string &str)
{
	int strsize = str.length(); // Bir satirin uzunlugu
	
	for(int i = 0; i < strsize ; ++i)
	{	//a ile z arasindaki kucuk harflerse
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] += 'A' - 'a'; 	
	}
}
void CPU::AddSpacetoComma(string &str)
{
	int commapos = str.find_first_of(",");
	
	if(commapos != -1)//Virgul varsa bunlari yap
	{
		if(str[commapos-1] != ' ')//Sag taraf		
			str.insert(commapos," ",1);
		
		commapos = str.find_first_of(",");

		if(str[commapos+1] != ' ' )//Sol taraf	
			str.insert(commapos+1," ",1);
	}
}
void CPU::RemoveLastSpace(string &str)
{
	const int i = str.find_last_not_of(" ");
	const int j = str.find_last_of(" ");

	if(i < j)
		str.erase(i+1,j);
}
void CPU::TextParser(const string &str,string &word1,string &word2,string &word3,string &word4)
{
	int index1,index2,index3,index4,index5,index6,index7;
	//Parcalama islemi icin degiskenler

	index1 = str.find_first_of(" ");
	
	if(index1 == -1)//Tek kelime varsa
		word1 += str;
	else
	{
		word1 += str.substr(0,index1);
		index2 = str.find_first_not_of(" ",index1);
		index3 = str.find_first_of(" ",index2);

		if( index2 != -1  && index3 != -1)
		{
			word2 += str.substr(index2,index3-index2);
			index4 = str.find_first_not_of(" ",index3);
			index5 = str.find_first_of(" ",index4);
		
			if(index4 != -1 && index5 != -1)
			{
				word3 += str.substr(index4,index5-index4);
				index6 = str.find_first_not_of(" ",index5);
				index7 = str.find_first_of(" ",index6);
				
				if(index6 != -1 && index7 != -1)
					word4+= str.substr(index6,index7-index6);
				else if(index6 != -1 && index7 == -1)
					word4+= str.substr(index6,index7-index6);
			}
			else if(index4 != -1 && index5 == -1)
			{
				index5 = str.length();
				word3 += str.substr(index4,index5-index4);
				index6 = str.find_first_not_of(" ",index5);
				index7 = str.find_first_of(" ",index6);
				
				if(index6 != -1 && index7 != -1)
					word4+= str.substr(index6,index7-index6);
			}
		}
		else if(index2 != -1 && index3 == -1)
		{
			index3 = str.length();
			word2 += str.substr(index2,index3-index2);
		}
	}
}
const int CPU::StringtoInt(const string &str) const
{
	int num = 0;
	const int size = str.length();

	//Gonderilen deger sayi degilse -1 return eder
	for(int i = 0; i < size ; ++i)
		if(str[i] > 'A' && str[i] < 'Z')
			return -1;
	
	for(int i = 0 ; i < size; ++i)
		num+=(str[i] -'0') * Power(10,size-i-1);	
	
	return num;
}
int CPU::Power(int x,int y) const
{
	int res = 1;
	int i;
	
	if( y==1)
		res = x;
	else
		for(i = 1; i< y+1; ++i)
			res*=x;

	return res;
}
int CPU::NumExtract(const string &str) const
{
	//#12 yi 12 ye çevirir
	return StringtoInt(str.substr(1));
	//R1 seklindeki 1 alip inte cevir
}
int CPU::RegisterCheck(const string &str) const
{
	//R varmi,Rden sonra gelen sayi 1 ile 5 arasindami
	if(str.substr(0,1) == "R" && NumExtract(str) >= 1 && NumExtract(str) <= 5)
		return 1;
	else
		return 0;
}
void CPU::InsPrn(const string &word2) const
{
	if(RegisterCheck(word2))//PRN R1
	{	
		int rNum = NumExtract(word2);//R1 den 1 i ayir int e cevir
		switch(rNum)
		{
			case 1:
				cout << " R1: ";
				cout << getRegs(0) << endl;
				break;
			case 2:
				cout << " R2: ";
				cout << getRegs(1) << endl;
				break;
			case 3:
				cout << " R3: ";
				cout << getRegs(2) << endl;
				break;
			case 4:
				cout << " R4: ";
				cout << getRegs(3) << endl;
				break;
			case 5:
				cout << " R5: ";
				cout << getRegs(4) << endl;
				break;
		}
	}
	else //PRN 521
		cout << StringtoInt(word2) << endl;
}
int CPU::InsJmp(const string &word2,const string &word4)
{
	if(word4 == "" && StringtoInt(word2) != -1 )//JMP 12
		return StringtoInt(word2);
	else if(word4 != "" && NumExtract(word2) >= 1 && NumExtract(word2) <=5)//JMP R1,12
	{
		int i = NumExtract(word2);
		
		if(getRegs(i-1) == 0)
			return StringtoInt(word4);
		else
			return -1;
	}
}
void CPU::InsAdd(const string &word2,const string &word4)
{
	const int i = NumExtract(word2);
	int j;
	int res;
	
	if(RegisterCheck(word4)) //ADD r1,r2  r1+r2 -->R1
	{
		j = NumExtract(word4);
		//rArray[i-1] += rArray[j-1];
		res = getRegs(i-1) + getRegs(j-1);
		setRegs(i-1,res);
	}	
	else
	{
		j = StringtoInt(word4);
		//rArray[i-1] +=  StringtoInt(word4);
		res = getRegs(i-1) + j;
		setRegs(i-1,res);
	}	
}

void CPU::InsSub(const string &word2,const string &word4)
{
	const int i = NumExtract(word2);
	int j;
	int res;
	
	if(StringtoInt(word4) == -1) //3.Parametre Registersa
	{
		j = NumExtract(word4);
		//rArray[i-1] -= Array[j-1];
		res = getRegs(i-1) - getRegs(j-1);
		setRegs(i-1,res);
	}	
	else
	{
		j = StringtoInt(word4);
		//rArray[i-1] -= StringtoInt(word4);
		res = getRegs(i-1) - j;
		setRegs(i-1,res);
	}
}
void CPU::InsMov(const string &word2,const string &word4)
{
	int i = NumExtract(word2);
	int j;//value for word4
	int res;
	
	if(RegisterCheck(word2) == 1 && RegisterCheck(word4) == 1) //MOV R1,R2   R1 ---> R2
	{
		j = NumExtract(word4);
		//rArray[j-1] = rArray[i-1];
		res = getRegs(i-1);
		setRegs(j-1,res); 
	}
	else if(RegisterCheck(word2) == 1 && StringtoInt(word4) >= 0) //MOV R1,10   10-->r1  
	{
		//rArray[i-1] = StringtoInt(word4);
		j = StringtoInt(word4);
		res = getRegs(i-1);
		setRegs(i-1,j);
	}
}
void CPU::PrintReg() const
{
	cout << "\t";
	
	for(int i= 1; i <= 5; ++i)
		cout << "\tR" << i << " : "<< getRegs(i-1);

	cout << "\t";
}
const int CPU::getHalt() const
{
	return haltVal;
}
void CPU::setHalt()
{
	haltVal = 1;
}























