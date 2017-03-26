#include <iostream>
#include <string>
#include <fstream>//Dosya fonksiyonlari


using namespace std;


int Power(int x,int y);
// X üzeri y yi hesaplar

int StringtoInt(const string str);
/////////////////////////////////////////////////////
//String i integer a ceviren fonksiyon
//Stringteki ifade sayı degilse -1 return ediyor
////////////////////////////////////////////////////



void toUpper(string &str);
////////////////////////////////////////////////////
//Stringteki kucuk harfleri buyuk harf yapan fonksiyon
////////////////////////////////////////////////////

void RemoveLeadingSpace(string &str);
////////////////////////////////////////////////////
//Stringin basindaki bosluklari silen fonksiyon
////////////////////////////////////////////////////
void RemoveSmcAndAfter(string &str);
////////////////////////////////////////////////////
//Noktali virgul ve sonrasini silen fonksiyon
////////////////////////////////////////////////////
void AddSpacetoComma(string &str);
////////////////////////////////////////////////////
//Virgulun sagi ve solu bos degilse,
//sagina ve soluna bosluk atan fonksiyon
void RemoveLastSpace(string &str);
////////////////////////////////////////////////////
//Stringin sonundaki bosluklari silen fonksiyon
////////////////////////////////////////////////////
void LineEdit(string &str);
//Satiri duzenleyen fonksiyon
//Icinde removeleadingspace,removesmcandafter
//addspacetocomma,removelastspace fonksiyonlari var
////////////////////////////////////////////////////
void ExeInstruct(string *str,int lnum,int optionnum);
////////////////////////////////////////////////////
//Instructionlari gerceklestiren fonksiyon
//Satir,satirsayisi ve option numarasi aliyor
////////////////////////////////////////////////////

int findSyntaxErrors(string *str,int lnum);
////////////////////////////////////////////////////
//If return zero false,return 1 correct
//Instruction dosyamizdaki (yazim) hatalari buluyor
////////////////////////////////////////////////////


void InsPrn(const string &str,const int *rArray);
////////////////////////////////////////////////////
//PRN Instruction Fonksiyonu
////////////////////////////////////////////////////
int InsJmp(const string &str1,const string &str2,const int *rArray);
////////////////////////////////////////////////////
//JMP Instruction Fonksiyonu
////////////////////////////////////////////////////
void InsAdd(const string &str1,const string &str2,int *rArray);
////////////////////////////////////////////////////
//ADD Instruction Fonksiyonu
////////////////////////////////////////////////////
void InsSub(const string &str1,const string &str2,int *rArray);
////////////////////////////////////////////////////
//SUB Instruction Fonksiyonu
////////////////////////////////////////////////////
void InsMov(const string &str1,const string &str2,int *rArray);
////////////////////////////////////////////////////
//MOV Instruction Fonksiyonu
////////////////////////////////////////////////////
void PrintReg(int *rArray);
////////////////////////////////////////////////////
//Registerlarin icerigini ekrana basan fonksiyon
////////////////////////////////////////////////////
int RegisterNumExtract(const string &str);
////////////////////////////////////////////////////
//R1 stringindeki sayiyi 1 seklinde cikaran fonksiyon
//Cikardigi sayiyi return ediyor
////////////////////////////////////////////////////



int main(int argc, char* argv[])
{

	fstream inp;

	string line1[200];
	int lnum = 0;
	int optionnum = StringtoInt(argv[2]);

	if(argc == 3)
	{
		inp.open(argv[1]);
		if(inp.is_open() == 0) 
			cerr << "***File can not opened***" << endl;
		else
		{
	
			while(getline(inp,line1[lnum]))//Dosya sonuna kadar satirlari al
				++lnum;

			cout <<"Line num:";
			cout << lnum << endl;

			if(findSyntaxErrors(line1,lnum))
			{
				cout << "Cant find Syntax Errors" << endl;
				ExeInstruct(line1,lnum,optionnum);
			}
		
			inp.close();
		}
	}
	

	


	return 0;

}
int findSyntaxErrors(string *line1,int lnum)
{
	//Stringi parcalara ayirmak icin gerekli degiskenler
	int index1,index2,index3,index4,index5,index6,index7;
	
	int flag = 0;//Dogru satir sayisi tutan degisken
	int hltfound = 0;//Hlt nin bulunup bulunmadigini tutan degisken
	string word1,word2,word3,word4;//Bir satiri boldugumuz parcalar
	
	cout << endl;
	for(int i = 0 ; i < lnum; ++i)
	{
		
		//Text Edit
		LineEdit(line1[i]);
		
		cout << line1[i] ;
		cout << "---Line---";
		cout << i+1  << endl;

		//Parcalama kismi
		//İlk boslugu bul sonraki ilk bosluk olmayan yeri bul
		//Arasini alip wordlere at seklinde calisiyor
		//İndexleri hatali durumlara karsi kontrol ediyor
		index1 = line1[i].find_first_of(" ");
		if(index1 == -1)
		{
			word1 += line1[i];
		}
		else
		{
			word1 += line1[i].substr(0,index1);

			index2 = line1[i].find_first_not_of(" ",index1);
			index3 = line1[i].find_first_of(" ",index2);

			if( index2 != -1  && index3 != -1)
			{
				word2 += line1[i].substr(index2,index3-index2);
				index4 = line1[i].find_first_not_of(" ",index3);
				index5 = line1[i].find_first_of(" ",index4);
				
				if(index4 != -1 && index5 != -1)
				{
					word3 += line1[i].substr(index4,index5-index4);
					index6 = line1[i].find_first_not_of(" ",index5);
					index7 = line1[i].find_first_of(" ",index6);
					
					if(index6 != -1 && index7 != -1)
						word4+= line1[i].substr(index6,index7-index6);
					else if(index6 != -1 && index7 == -1)
						word4+= line1[i].substr(index6,index7-index6);
				}
				else if(index4 != -1 && index5 == -1)
				{
					index5 = line1[i].length();
					word3 += line1[i].substr(index4,index5-index4);
					index6 = line1[i].find_first_not_of(" ",index5);
					index7 = line1[i].find_first_of(" ",index6);
					if(index6 != -1 && index7 != -1)
						word4+= line1[i].substr(index6,index7-index6);
				}
			}
			else if(index2 != -1 && index3 == -1)
			{
				index3 = line1[i].length();
				word2 += line1[i].substr(index2,index3-index2);
			}
		}
		
		if( 3 == word1.length() )
		{
			if(word1 == "MOV" || word1 == "JMP" || word1 == "PRN" || 
				word1 == "ADD" || word1 == "SUB" || word1 == "HLT")
			{
				if(word1 == "HLT") 
				{
					cout << "girdi" << endl;
					if(word2.empty() || word2[0] ==' ')
					{
						hltfound = 1;
						++flag;
						cout << "HLT bulundu" << endl;
					}
					else
					{
						cerr << "***False HLT Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "PRN") 
				{
					if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5") && word3 == "")
					{
						
						++flag;	
					}
					else if(StringtoInt(word2) >= 0)
					{
						++flag;
					}
					else
					{
						cerr << "***False PRN Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "JMP")
				{
					if(word2!="" && word3 == "" && StringtoInt(word2) >= 0 && StringtoInt(word2) <= lnum-1)
					{
						++flag;
					}
					else if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3=="," && StringtoInt(word4) >= 0 && StringtoInt(word4) <= lnum )
					{
						++flag;
					}
					else
					{
						cerr << "***False JMP Instruction Syntax***" << endl; 
					}
				}
				else if(word1 == "ADD")
				{
					if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && StringtoInt(word4) > 0 )
					{
						++flag;
					}
					else if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && (word4 == "R1" || word4 == "R2" || word4 == "R3" || word4 == "R4" 
					 	|| word4 == "R5" ))
					{
					 	++flag;
					}
					else
					{
						cerr << "***False ADD Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "SUB")
				{
					if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && StringtoInt(word4) > 0 )
					{
						++flag;
					}
					else if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && (word4 == "R1" || word4 == "R2" || word4 == "R3" || word4 == "R4" 
					 	|| word4 == "R5" ))
					{
					 	++flag;
					}
					else
					{
						cerr << "***False SUB Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "MOV")
				{
					if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && StringtoInt(word4) > 0)
					{
						++flag;
					}
					else if((word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
					 && word3 == "," && (word4 == "R1" || word4 == "R2" || word4 == "R3" || word4 == "R4" 
					 	|| word4 == "R5" ))
					{
					 	++flag;
					}
					else
					{
						cerr << "***False MOV Instruction Syntax***" << endl;
					}
				}
				else
				{
					cerr << "***Undefined Instruction" << endl;
				}
			}
			else
			{
				cerr << "***Undefined Instruction" << endl;
			}

	
		}
		word1.erase();
		word2.erase();
		word3.erase();
		word4.erase();
	}

	if(hltfound == 0)
		cerr << "***HLT parameter not found***" << endl;

	cout << endl;

	if( hltfound != 0 && flag == lnum)
		return 1;

	
	return 0;
}
void LineEdit(string &str)
{

	RemoveLeadingSpace(str);//Stringin basindaki bosluklari silen fonksiyon
	RemoveSmcAndAfter(str);//Noktali virgul ve sonrasini silen fonksiyon
	toUpper(str);//Stringteki kucuk harfleri buyuk harf yapan fonksiyon
	AddSpacetoComma(str);//Virgulun sagi ve solu bos degilse,
						//sagina ve soluna bosluk atan fonksiyon
	RemoveLastSpace(str);//Stringin sonundaki bosluklari silen fonksiyon
	
}
int StringtoInt(const string str)
{
	int num = 0;
	int size = str.length();

	//Gonderilen deger sayi degilse -1 return eder
	for(int i = 0; i < size ; ++i)
		if(str[i] > 'A' && str[i] < 'Z')
			return -1;
	

	for(int i = 0 ; i < size; ++i)
		num+=(str[i] -'0') * Power(10,size-i-1);	
	
	return num;
}
int Power(int x,int y)
{
	int res = 1;
	int i;
	if( y==1)
		res = x;
	else
	{
		for(i = 1; i< y+1; ++i)
		{
			res*=x;
		}
	}


	return res;
}
void RemoveLeadingSpace(string &str)
{

	int i = str.find_first_not_of(" ");
	str.erase(0,i);

}
void AddSpacetoComma(string &str)
{

	int commapos = str.find_first_of(",");
	
	if(commapos != -1)//Virgul varsa bunlari yap
	{

		if(str[commapos-1] != ' ')//Sag taraf
		{
			
			str.insert(commapos," asss",1);
		}
		
		commapos = str.find_first_of(",");

		if(str[commapos+1] != ' ' )//Sol taraf
		{	
			str.insert(commapos+1," ",1);
		}
	}

}
void RemoveSmcAndAfter(string &str)
{
	
	int i = str.find_first_of(";");
	
	if( i != -1)//Noktali virgul varsa
		str.erase(i);// i. yerden itibaren sil
}
void toUpper(string &str)
{

	
	int strsize = str.length(); // Bir satirin uzunlugu
	for(int i = 0; i < strsize ; ++i)
		{	//a ile z arasindaki kucuk harflerse
			if(str[i] >= 'a' && str[i] <= 'z')
				str[i] += 'A' - 'a'; 	
		}
	
}
void RemoveLastSpace(string &str)
{
	int i = str.find_last_not_of(" ");
	int j = str.find_last_of(" ");

	if(i < j)
		str.erase(i+1,j);
}
void ExeInstruct(string *line1,int lnum,int optionnum)
{
	int rArray[5] = {0,0,0,0,0};//Register Array

	int index1,index2,index3,index4,index5,index6,index7;//Parcalama islemi icin degiskenler
	string word1,word2,word3,word4;//Parcalari attigimiz stringler



	for(int i = 0 ; i < lnum; ++i)
	{
		
		LineEdit(line1[i]);//Satiri düzenleme
		
		if(optionnum == 1)
		{
			cout << "---Line---";
			cout << i+1; cout << " " ;
			cout << line1[i] ;
		}
		
		index1 = line1[i].find_first_of(" ");
		if(index1 == -1)
		{
			word1 += line1[i];
		}
		else
		{
			word1 += line1[i].substr(0,index1);

			index2 = line1[i].find_first_not_of(" ",index1);
			index3 = line1[i].find_first_of(" ",index2);

			if( index2 != -1  && index3 != -1)
			{
				word2 += line1[i].substr(index2,index3-index2);
				index4 = line1[i].find_first_not_of(" ",index3);
				index5 = line1[i].find_first_of(" ",index4);
				
				if(index4 != -1 && index5 != -1)
				{
					word3 += line1[i].substr(index4,index5-index4);
					index6 = line1[i].find_first_not_of(" ",index5);
					index7 = line1[i].find_first_of(" ",index6);
					
					if(index6 != -1 && index7 != -1)
						word4+= line1[i].substr(index6,index7-index6);
					else if(index6 != -1 && index7 == -1)
						word4+= line1[i].substr(index6,index7-index6);
				}
				else if(index4 != -1 && index5 == -1)
				{
					index5 = line1[i].length();
					word3 += line1[i].substr(index4,index5-index4);
					index6 = line1[i].find_first_not_of(" ",index5);
					index7 = line1[i].find_first_of(" ",index6);
					if(index6 != -1 && index7 != -1)
						word4+= line1[i].substr(index6,index7-index6);
				}
			}
			else if(index2 != -1 && index3 == -1)
			{
				index3 = line1[i].length();
				word2 += line1[i].substr(index2,index3-index2);
			}
		}

		if(word1 == "HLT")
		{
			return;
		}
		else if(word1 == "PRN")
		{
			InsPrn(word2,rArray);
		}
		else if(word1 == "JMP")
		{
			if(InsJmp(word2,word4,rArray) != -1 )
				i = InsJmp(word2,word4,rArray) - 2;
		}
		else if(word1 == "ADD")
		{
			InsAdd(word2,word4,rArray);
		}
		else if(word1 == "SUB")
		{
			InsSub(word2,word4,rArray);
		}
		else if(word1 == "MOV")
		{
			InsMov(word2,word4,rArray);
		}


		if(optionnum == 1)//Optionnum 1se arrayi bas
			PrintReg(rArray);

		word1.erase();//Donguden cikmadan wordleri sil
		word2.erase();
		word3.erase();
		word4.erase();

	}

}
void InsPrn(const string &word2,const int *rArray)
{

	if(word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
	{
		
		int rNum = RegisterNumExtract(word2);//R1 den 1 i ayir int e cevir
		switch(rNum)
		{
			case 1:
				cout << " R1: ";
				cout << rArray[0] << endl;
				break;
			case 2:
				cout << " R2: ";
				cout << rArray[1] << endl;
				break;
			case 3:
				cout << " R3: ";
				cout << rArray[2] << endl;
				break;
			case 4:
				cout << " R4: ";
				cout << rArray[3] << endl;
				break;
			case 5:
				cout << " R5: ";
				cout << rArray[4] << endl;
				break;
		}
	}
	else
	{
		
		cout << StringtoInt(word2) << endl;
	}

}
int InsJmp(const string &word2,const string &word4,const int *rArray)
{

	if(word4 == "" && StringtoInt(word2) != -1 )
	{
		return StringtoInt(word2);
	}
	else if(word4 != "" && RegisterNumExtract(word2) >= 1 && RegisterNumExtract(word2) <=5)
	{
		int i = RegisterNumExtract(word2);
		if(rArray[i-1] == 0)
		{
			return StringtoInt(word4);
		}
		else
			return -1;
	}

}
void InsAdd(const string &word2,const string &word4,int *rArray)
{

	int i = RegisterNumExtract(word2) - 1;

	if(StringtoInt(word4) == -1) // 3.Parametre Registersa
	{
		
		int j = RegisterNumExtract(word4) - 1;

		rArray[i] += rArray[j];//ADD r1,r2  r1+r2 -->R1

	}
	else
	{
		rArray[i] += StringtoInt(word4);
	}

}
void InsSub(const string &word2,const string &word4,int *rArray)
{
	int i = RegisterNumExtract(word2) - 1;

	if(StringtoInt(word4) == -1) //3.Parametre Registersa
	{
		int j = RegisterNumExtract(word4) - 1;
		rArray[i] -= rArray[j];
	}
	else
	{
		rArray[i] -=StringtoInt(word4);
	}
}
void InsMov(const string &word2,const string &word4,int *rArray)
{
	
	int i = RegisterNumExtract(word2) - 1;

	if(StringtoInt(word4) == -1) //3.Parametre Registersa
	{
		int j = RegisterNumExtract(word4) - 1;
		rArray[j] = rArray[i];//MOV R1,R2   R1 ---> R2
	}
	else
	{
		rArray[i] = StringtoInt(word4);
	}



}
void PrintReg(int *rArray)
{

	cout << " R1 = " << rArray[0];
	cout << " R2 = " << rArray[1];
	cout << " R3 = " << rArray[2];
	cout << " R4 = " << rArray[3];
	cout << " R5 = " << rArray[4] << endl;

}
int RegisterNumExtract(const string &str)
{

	return StringtoInt(str.substr(1,1));
	//R1 seklindeki 1 alip inte cevir
}