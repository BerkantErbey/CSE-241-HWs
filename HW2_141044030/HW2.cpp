/////////////////////////////////////////////////////
// Berkant Erbey 
// 14.10.2016 
// HW2
// HW2.cpp
////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>


using namespace std;


int findSyntaxErrors(string *str,const int lnum);
////////////////////////////////////////////////////
//If return zero false,return 1 correct
//Instruction dosyamizdaki (yazim) hatalari buluyor
////////////////////////////////////////////////////

void LineEdit(string &str);
//Satiri duzenleyen fonksiyon
//Icinde removeleadingspace,removesmcandafter
//addspacetocomma,removelastspace fonksiyonlari var
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

void TextParser(const string &str,string &word1,string &word2,string &word3,string &word4);
////////////////////////////////////////////////////
//Satiri parcalayip gerekli parametreleri yakalayan fonksiyon
//Parcalama kismi
	//İlk boslugu bul sonraki ilk bosluk olmayan yeri bul
	//Arasini alip wordlere at seklinde calisiyor
	//İndexleri hatali durumlara karsi kontrol ediyor
	//İndexlere göre 1kelime,2kelime,3kelime,
	//4 kelime seklindeki stringleri ayiriyor
// MOV R1,R3  --> word1= "MOV" word2 = "R1" word3 = ","" word4 = "R3"
///////////////////////////////////////////////////

void ExeInstruct(const string *str,int lnum,const int optionNum);
////////////////////////////////////////////////////
//Instructionlari gerceklestiren fonksiyon
//Satir,satirsayisi ve option numarasi aliyor
////////////////////////////////////////////////////

int Power(int x,int y);
// X üzeri y yi hesaplar

int StringtoInt(const string str);
/////////////////////////////////////////////////////
//String i integer a ceviren fonksiyon
//Stringteki ifade sayı degilse -1 return ediyor
////////////////////////////////////////////////////

int RegisterCheck(const string &str);
////////////////////////////////////////////////////
//Verilen stringin register olup olmadigi kontrol edilir.
//Registersa 1,değilse 0 return edilir
////////////////////////////////////////////////////

void InsPrn(const string &str,const int *rArray,const unsigned int *memoryArray);
////////////////////////////////////////////////////
//Verilen parametreye register icerigini,bellek icerigini 
//ya da bir sabit sayıyı ekrana basar
////////////////////////////////////////////////////

int InsJmp(const string &str1,const string &str2,const int *rArray);
////////////////////////////////////////////////////
//Registerdaki deger 0 a esitse verilen satiri return ediyor
//JMP R1,12 r1 = 0 return 12 / r1 != 0 return -1
////////////////////////////////////////////////////

int InsJpn(const string &str1,const string &string2,const int *rArray);
////////////////////////////////////////////////////
////Registerdaki deger 0 a esit ve kücükse verilen satiri return ediyor
//JPN R1,12 r1 <= 0 return 12 / r1 > 0 return -1
////////////////////////////////////////////////////

void InsAdd(const string &str1,const string &str2,int *rArray,unsigned int *memoryArray);
////////////////////////////////////////////////////
//Verilen parametreye göre register ile memory, 
//register ile register,register ile sabit sayi iceriklerini
//toplar. 1.ADD R1,R2 2.ADD R1,10 3.ADD R4,#14 
////////////////////////////////////////////////////

void InsSub(const string &str1,const string &str2,int *rArray,unsigned int *memoryArray);
////////////////////////////////////////////////////
//Verilen parametreye göre register ile memory, 
//register ile register,register ile sabit sayi iceriklerini
//cikarir. 1.SUB R1,R2 2.SUB R1,10 3.SUB R4,#14 
////////////////////////////////////////////////////

void InsMov(const string &str1,const string &str2,int *rArray,unsigned int *memoryArray);
////////////////////////////////////////////////////
//MOV Instruction Fonksiyonu
////////////////////////////////////////////////////

void PrintReg(int *rArray);
////////////////////////////////////////////////////
//Registerlarin icerigini ekrana basan fonksiyon
////////////////////////////////////////////////////

int NumExtract(const string &str);
////////////////////////////////////////////////////
//Stringin içinden sayıyı çıkaran fonksiyon 
// #12->12 , R4 -> 4 seklinde cikariyor
//Cikardigi sayiyi return ediyor
////////////////////////////////////////////////////

void FillMemory(unsigned int *memoryArray,int size);
////////////////////////////////////////////////////
//Hafiza dizisini belirlenen sayi ile doldurmak icin gereken fonksiyon
////////////////////////////////////////////////////

void PrintMemory(unsigned int *memoryArray,int size);
////////////////////////////////////////////////////
//Hafiza dizisinin icerigini ekrana basan fonksiyon
////////////////////////////////////////////////////

int MemoryCheck(const string &str);
////////////////////////////////////////////////////
//Verilen stringin hafiza olup olmadigini kontrol eder.
//#0 .... #49 ve basinda # olmali
////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	fstream inp;
	const int MaxLineNum = 200;
	
	string line[MaxLineNum];
	
	int lnum = 0;
	int optionNum = StringtoInt(argv[2]);

	if(argc == 3)
	{
		inp.open(argv[1]);
		if(inp.is_open() == 0) 
			cerr << "***File can not opened***" << endl;
		else
		{
			while(getline(inp,line[lnum]))//Dosya sonuna kadar satirlari al
			++lnum;

			cout <<"Line num:";
			cout << lnum << endl;

			if(findSyntaxErrors(line,lnum))
			{
				cout << "Cant find Syntax Errors" << endl;
				ExeInstruct(line,lnum,optionNum);
			}
			else
				cout << "***Find Syntax Error(s)***" << endl;
		
			inp.close();
		}
	}
	

	return 0;

}
int findSyntaxErrors(string *line,const int lnum)
{
	//Stringi parcalara ayirmak icin gerekli degiskenler
	int index1,index2,index3,index4,index5,index6,index7;
	
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
			if(word1 == "MOV" || word1 == "JMP" || word1 == "JPN" || word1 == "PRN" || 
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
					{
						cerr << "***False HLT Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "PRN") 
				{
					if(RegisterCheck(word2) && word3 == "")
					{
						++flag;	
					}
					else if(StringtoInt(word2) >= 0)
					{
						++flag;
					}
					else if(word2.substr(0,1) == "#" && StringtoInt(word2.substr(1)) <= 49 && StringtoInt(word2.substr(1)) >= 0)
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
					if(word2!="" && word3 == "" && StringtoInt(word2) >= 0 && StringtoInt(word2) <= lnum)
					{
						++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) >= 0 && StringtoInt(word4) <= lnum)
					{
						++flag;
					}
					else
					{
						cerr << "***False JMP Instruction Syntax***" << endl; 
					}
				}
				else if(word1 == "JPN")
				{
					if(RegisterCheck(word2) == 1 && word3 == "," && StringtoInt(word4) <= lnum && StringtoInt(word4) >= 0)
					{
						++flag;
					}
					else
					{
						cerr << "***False JPN Instruction Syntax***" << endl;
					}
				}
				else if(word1 == "ADD")
				{
					if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) > 0)
					{
						++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4))
					{
					 	++flag;
					}
					else if(RegisterCheck(word2)
					 && word3 == "," && word4.substr(0,1) == "#" && StringtoInt(word4.substr(1)) <= 49 && StringtoInt(word4.substr(1)) >= 0)
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
					if(RegisterCheck(word2)
					 && word3 == "," && StringtoInt(word4) > 0 )
					{
						++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4))
					{
					 	++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && word4.substr(0,1) == "#" && 
						StringtoInt(word4.substr(1)) <= 49 && StringtoInt(word4.substr(1)) >= 0)
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
					if(RegisterCheck(word2) && word3 == "," && StringtoInt(word4) >= 0)//MOV R1,12
					{
						++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && RegisterCheck(word4)) //MOV R1,R3
					{
					 	++flag;
					}
					else if(RegisterCheck(word2) && word3 == "," && word4.substr(0,1) == "#" && 
					StringtoInt(word4.substr(1)) >= 0 && StringtoInt(word4.substr(1)) <= 49)//MOV r1,#4
					{
						++flag;
					}
					else if(MemoryCheck(word2) && word3 == "," && RegisterCheck(word4))//MOV #45,R2
					{
						++flag;
					}
					else if(MemoryCheck(word2) && word3 == "," && StringtoInt(word4) >= 0)//MOV #14,516
					{
						++flag;    //Unsigned int oldugundan 0 dan buyuk esit olmali
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
		//1 dongu tamamlandiginda yeni degerler icin wordleri bosaltma.
		word1.erase();
		word2.erase();
		word3.erase();
		word4.erase();
	}

	if(hltfound == 0)
		cerr << "***HLT parameter not found***" << endl;

	cout << endl;

	if( hltfound != 0 && flag == lnum)//HLT varsaDogru satir sayisi toplam satira esitse
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
void TextParser(const string &str,string &word1,string &word2,string &word3,string &word4)
{

	int index1,index2,index3,index4,index5,index6,index7;//Parcalama islemi icin degiskenler

	index1 = str.find_first_of(" ");
	if(index1 == -1)
	{
		word1 += str;
	}
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
			
			str.insert(commapos," ",1);
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
void ExeInstruct(const string *line,const int lnum,const int optionNum)
{
	
	const int rSize = 5;    		//Register Dizisinin Boyutu
	const int mSize = 50;			//Bellek Dizisinin Boyutu
	
	int rArray[rSize] = {0,0,0,0,0};	//Register Dizisi
	unsigned int memoryArray[mSize];	//Bellek Dizisi
	
	string word1,word2,word3,word4;//Parcalari attigimiz stringler

	FillMemory(memoryArray,mSize);//Hafizayi 0 larla dolduruyor
	
	for(int i = 0 ; i < lnum; ++i)
	{	
		if(optionNum == 1 || optionNum == 2)
		{
			cout << i+1; cout << "   " ;
			cout << line[i] ;
		}
	
		TextParser(line[i],word1,word2,word3,word4);
		
		if(word1 == "HLT")
		{	
			PrintReg(rArray);
			PrintMemory(memoryArray,mSize);
			return;
		}
		else if(word1 == "PRN")
		{
			InsPrn(word2,rArray,memoryArray);
		}
		else if(word1 == "JMP")
		{
			if(InsJmp(word2,word4,rArray) != -1)
				i = InsJmp(word2,word4,rArray) - 2;
		}
		else if(word1 == "JPN")
		{
			if(InsJpn(word2,word4,rArray) != -1)
				i = InsJpn(word2,word4,rArray) - 2;
		}
		else if(word1 == "ADD")
			InsAdd(word2,word4,rArray,memoryArray);
		else if(word1 == "SUB")
			InsSub(word2,word4,rArray,memoryArray);
		else if(word1 == "MOV")
			InsMov(word2,word4,rArray,memoryArray);


		if(optionNum == 1)//optionNum 1se arrayi bas
			PrintReg(rArray);
		else if(optionNum == 2)
		{
			PrintReg(rArray);
			PrintMemory(memoryArray,mSize);
		}

		word1.erase();//Donguden cikmadan wordleri sil
		word2.erase();
		word3.erase();
		word4.erase();

	}

}
void InsPrn(const string &word2,const int *rArray,const unsigned int *memoryArray)
{

	if(word2 == "R1" || word2 == "R2" || word2 == "R3" || word2 == "R4" || word2 == "R5")
	{
		
		int rNum = NumExtract(word2);//R1 den 1 i ayir int e cevir
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
	else if(word2.substr(0,1) == "#")//Hafiza adresiyse
		cout << memoryArray[(NumExtract(word2))] << endl;// # sonrasini int e cevir 
	else
		cout << StringtoInt(word2) << endl;

}
int InsJmp(const string &word2,const string &word4,const int *rArray)
{

	if(word4 == "" && StringtoInt(word2) != -1 )
		return StringtoInt(word2);
	else if(word4 != "" && NumExtract(word2) >= 1 && NumExtract(word2) <=5)
	{
		int i = NumExtract(word2);
		if(rArray[i-1] == 0)
			return StringtoInt(word4);
		else
			return -1;
	}

}
int InsJpn(const string &word2,const string &word4,const int *rArray)
{
	if(rArray[NumExtract(word2) - 1] <= 0)//Jpn instruction kurali
		return StringtoInt(word4);

	return -1;
}
void InsAdd(const string &word2,const string &word4,int *rArray,unsigned int *memoryArray)
{

	int i = NumExtract(word2);
	int j = NumExtract(word4);

	if(RegisterCheck(word4)) //ADD r1,r2  r1+r2 -->R1
		rArray[i-1] += rArray[j-1];
	else if(MemoryCheck(word4) == 1 ) //Add R1,#43
		rArray[i-1] += memoryArray[j];
	else
		rArray[i-1] += StringtoInt(word4);

}
void InsSub(const string &word2,const string &word4,int *rArray,unsigned int *memoryArray)
{
	int i = NumExtract(word2);
	int j = NumExtract(word4);
	if(StringtoInt(word4) == -1) //3.Parametre Registersa
		rArray[i-1] -= rArray[j-1];
	else if((word4.substr(0,1) == "#")) // 3.Parametre Bellek Adresiyse
		rArray[i-1] -= memoryArray[j];
	else
		rArray[i-1] -= StringtoInt(word4);

}
void InsMov(const string &word2,const string &word4,int *rArray,unsigned int *memoryArray)
{
	
	int i = NumExtract(word2);
	int j = NumExtract(word4);

	if(RegisterCheck(word2) == 1 && RegisterCheck(word4) == 1) //MOV R1,R2   R1 ---> R2
		rArray[j-1] = rArray[i-1];
	else if(RegisterCheck(word2) == 1 && StringtoInt(word4) >= 0) //MOV R1,10   10-->r1  
		rArray[i-1] = StringtoInt(word4); 
	else if(RegisterCheck(word2) == 1 && MemoryCheck(word4) == 1)//MOV R1,#4
		memoryArray[j] = rArray[i-1];
	else if(MemoryCheck(word2) == 1 && RegisterCheck(word4) == 1)//MOV #7,R2
		rArray[j-1] = memoryArray[i]; 
	else if(MemoryCheck(word2) == 1 && StringtoInt(word4) >= 0)//MOV #12,45
		memoryArray[i] = StringtoInt(word4);

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
			res*=x;
	}

	return res;

}
void PrintReg(int *rArray)
{

	cout << "\t";
	cout << " R1 = " << rArray[0];
	cout << " R2 = " << rArray[1];
	cout << " R3 = " << rArray[2];
	cout << " R4 = " << rArray[3];
	cout << " R5 = " << rArray[4] << endl;

}
int NumExtract(const string &str)
{
	//#12 yi 12 ye çevirir
	return StringtoInt(str.substr(1));
	//R1 seklindeki 1 alip inte cevir
}
void FillMemory(unsigned int *memoryArray,int mSize)
{

	for(int i = 0; i < mSize; ++i)
		memoryArray[i] = 0;

}
void PrintMemory(unsigned int *memoryArray,int mSize)
{

	cout << "__________________________\n";
	for(int i = 0; i< mSize; ++i)
	{
		cout << "\t#" << i << "-->"<< memoryArray[i];
		if(i % 10 == 0 && i != 0 )//Her satirda 10 tane memory icerigi olsun
			cout << endl;
	}
	 
	cout <<	"__________________________" << endl;

}
int RegisterCheck(const string &str)
{
	//R varmi,Rden sonra gelen sayi 1 ile 5 arasindami
	if(str.substr(0,1) == "R" && NumExtract(str) >= 1 && NumExtract(str) <= 5)
		return 1;
	else
		return 0;
	
}
int MemoryCheck(const string &str)
{
	//# varmi,# den sonra gelen sayi 0 ile 49 arasındami
	if(str.substr(0,1) == "#" && NumExtract(str) >= 0 && NumExtract(str) <= 49)
		return 1;
	else
		return 0;

}
////////////////////////////////////////////////////
//__________________END OF HW2.cpp_______________//
////////////////////////////////////////////////////