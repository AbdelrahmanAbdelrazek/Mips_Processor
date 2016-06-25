#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"
#include <bitset>
using namespace std;
//function to convert string to binary
string clearspace(string toclear)
{
	for(int counter=0;counter<toclear.size();counter++)
{
	if(toclear[counter]==' ')
	{
		toclear.erase(counter,1);
	}
}
	return toclear;
}
bool tobool (char x)
{
	if (x=='0')
	return 0;
	else
	return 1;
}
//function to decode the register name into an address using call by refrence to modify the instruction boolean encoding array
void register_encode(string Register,bool &address2,bool &address3,bool &address4,bool &address5,bool &address6)
{ 
	if (Register == "$zero")
	{
		address2=0;	address3=0;	address4=0;	address5=0;	address6=0;
	}
else if (Register=="$at")
{
		 address2=0; address3=0; address4=0;	address5=0; address6=1;
}
else if (Register=="$v0")
{
		 address2=0; address3=0; address4=0;	address5=1; address6=0;
}
else if (Register=="$v1")
{
		 address2=0; address3=0; address4=0;	address5=1; address6=1;
}
else if (Register=="$a0")
{
		 address2=0; address3=0; address4=1;	address5=0; address6=0;
}
else if (Register=="$a1")
{
		 address2=0; address3=0; address4=1;	address5=0; address6=1;
}
else if (Register=="$a2")
{
		 address2=0; address3=0; address4=1;	address5=1; address6=0;
}
else if (Register=="$a3")
{
		 address2=0; address3=0; address4=1;	address5=1; address6=1;
}
else if (Register=="$t0")
{
		 address2=0; address3=1; address4=0; address5=0; address6=0;
}
else if (Register=="$t1")
{
		 address2=0; address3=1; address4=0; address5=0; address6=1;
}
else if (Register=="$t2")
{
		 address2=0; address3=1; address4=0; address5=1; address6=0;
}
else if (Register=="$t3")
{
		 address2=0; address3=1; address4=0; address5=1; address6=1;
}
else if (Register=="$t4")
{
		 address2=0; address3=1; address4=1; address5=0; address6=0;
}
else if (Register=="$t5")
{
		 address2=0; address3=1; address4=1; address5=0; address6=1;
}
else if (Register=="$t6")
{
		 address2=0; address3=1; address4=1; address5=1; address6=0;
}
else if (Register=="$t7")
{
		 address2=0; address3=1; address4=1; address5=1; address6=1;
}
else if (Register=="$s0")
{
		 address2=1; address3=0; address4=0; address5=0; address6=0;
}
else if (Register=="$s1")
{
		 address2=1; address3=0; address4=0; address5=0; address6=1;
}
	else if (Register=="$s2")
{
		 address2=1; address3=0; address4=0; address5=1; address6=0;
}
else if (Register=="$s3")
{
		 address2=1; address3=0; address4=0; address5=1; address6=1;
}
else if (Register=="$s4")
{
		 address2=1; address3=0; address4=1; address5=0; address6=0;
}
else if (Register=="$s5")
{
		 address2=1; address3=0; address4=1; address5=0; address6=1;
}
else if (Register=="$s6")
{
		 address2=1; address3=0; address4=1; address5=1; address6=0;
}
else if (Register=="$s7")
{
		 address2=1; address3=0; address4=1; address5=1; address6=1;
}
else if (Register=="$t8")
{
		 address2=1; address3=1; address4=0; address5=0; address6=0;
}
else if (Register=="$t9")
{
		 address2=1; address3=1; address4=0; address5=0; address6=1;
}
else if (Register=="$sp")
{
		 address2=1; address3=1; address4=1; address5=0; address6=1;
}
else if (Register=="$fp")
{
		 address2=1; address3=1; address4=1;	address5=1; address6=0;
}
else if (Register=="$ra")
{
		 address2=1; address3=1; address4=1;	address5=1; address6=1;
}
}



//function to count the number of occurence of commas (,) inside the string
int count_commas(string s) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s[i] == ',') count++;
  return count;
}
//function to encode the registers
void main()
{	ofstream testout;
	testout.open("instruction_memory.list", std::ofstream::out | std::ofstream::trunc);
	testout.close();
Dictionary labels;
int numberofinstruction=0;
string testingstring;
string line[64];
ifstream myfile;

myfile.open ("assembly.txt");
// taking input from file into an array "line" which holds every single line inside the array in a single element inside the array
while ( getline (myfile,testingstring))
 { 
if ( testingstring.substr(testingstring.size()-1,1)==":")
{
	labels.Add(testingstring.substr(0,testingstring.size()-1),numberofinstruction*4);
}
else
{
line[numberofinstruction]=testingstring;
numberofinstruction++;
}
}
 myfile.close();
//transform to binary
 bool binaryinstruction[32];
 string firstterm,secondterm,thirdterm,fourthterm;
 for (int counter=0;counter<numberofinstruction;counter++)
 {	switch (count_commas(line[counter])){
 case 0:
	 firstterm=line[counter].substr(0,line[counter].find(" "));
	secondterm=line[counter].substr(line[counter].find(" ")+1,line[counter].size()-line[counter].find(" "));
firstterm=clearspace(firstterm);
secondterm=clearspace(secondterm);
	if(firstterm=="jal")

	{	
		//jal encoding
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=1;
		binaryinstruction[5]=1;

		int jumpaladdress_integer=labels.get_address(secondterm)/4;
		string jumpaladdress_string=bitset<26>(jumpaladdress_integer).to_string();
		for (int x=0;x<=25;x++)
		{
			binaryinstruction[6+x]=tobool(jumpaladdress_string[x]);
		}

	}
	else if(firstterm=="j")

	{	
		//j encoding
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=1;
		binaryinstruction[5]=0;
		int jumpaladdress_integer=labels.get_address(secondterm)/4;
		string jumpaladdress_string=bitset<26>(jumpaladdress_integer).to_string();
		for (int x=0;x<=25;x++)
		{
			binaryinstruction[6+x]=tobool(jumpaladdress_string[x]);
		}

	}
	else if(firstterm=="jr")
	{
		//jr encoding
		for(int x=0 ; x<=31;x++)
		{
		binaryinstruction[x]=0;
		}
		binaryinstruction[28]=1;
		register_encode(secondterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
	}
	break;

 case 1:
	 firstterm=line[counter].substr(0,line[counter].find(" "));
	 secondterm=line[counter].substr(line[counter].find(" ")+1,line[counter].find(",")-line[counter].find(" ")-1);
	 thirdterm=line[counter].substr(line[counter].find(",")+1,line[counter].size()-line[counter].find(","));
	 firstterm=clearspace(firstterm);
	secondterm=clearspace(secondterm);
	thirdterm=clearspace(thirdterm);
	 if (firstterm=="lw")
	 {	//LW encoding
		binaryinstruction[0]=1;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;	
		binaryinstruction[4]=1;
		binaryinstruction[5]=1;
		register_encode(secondterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		string offset=thirdterm.substr(0,thirdterm.find('('));
		offset=bitset<16>(stoi(offset)).to_string();
		for(int x=0;x<=15;x++)
		{
			binaryinstruction[16+x]=tobool(offset[x]);
		}
		string lwregister=thirdterm.substr(thirdterm.find('$'),thirdterm.size()-thirdterm.find('(')-2);
		register_encode(lwregister,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
	 }
	 else 
	 {	//SW encoding
		binaryinstruction[0]=1;
		binaryinstruction[1]=0;
		binaryinstruction[2]=1;
		binaryinstruction[3]=0;
		binaryinstruction[4]=1;
		binaryinstruction[5]=1;
//begin
		register_encode(secondterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		string offset=thirdterm.substr(0,thirdterm.find('('));
		offset=bitset<16>(stoi(offset)).to_string();
		for(int x=0;x<=15;x++)
		{
			binaryinstruction[16+x]=tobool(offset[x]);
		}
		string lwregister=thirdterm.substr(thirdterm.find('$'),thirdterm.size()-thirdterm.find('(')-2);
		register_encode(lwregister,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
//end

	 }
	 break;
 case 2:
	 firstterm=line[counter].substr(0,line[counter].find(" "));
	 secondterm=line[counter].substr(line[counter].find(" ")+1,line[counter].find(",")-line[counter].find(" ")-1);
	 line[counter].erase(0,line[counter].find(",")+1);
	 thirdterm=line[counter].substr(0,line[counter].find(","));
	 fourthterm=line[counter].substr(line[counter].find(",")+1,line[counter].size()-line[counter].find(",")-1);
	 firstterm=clearspace(firstterm);
	secondterm=clearspace(secondterm);
	thirdterm=clearspace(thirdterm);
	fourthterm=clearspace(fourthterm);
	 if(firstterm=="add")
	 {
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		binaryinstruction[21]=0;
		binaryinstruction[22]=0;
		binaryinstruction[23]=0;
		binaryinstruction[24]=0;
		binaryinstruction[25]=0;
		binaryinstruction[26]=1;
		binaryinstruction[27]=0;
		binaryinstruction[28]=0;
		binaryinstruction[29]=0;
		binaryinstruction[30]=0;
		binaryinstruction[31]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(fourthterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);

	 }
	 else if(firstterm=="addi")
	{	
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=1;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		register_encode(secondterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		fourthterm=bitset<16>(stoi(fourthterm)).to_string();
		for(int x=0;x<=15;x++)
		{
			binaryinstruction[16+x]=tobool(fourthterm[x]);
		}
	 }
	else if(firstterm=="sll")
		{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		binaryinstruction[6]=0;
		binaryinstruction[7]=0;
		binaryinstruction[8]=0;
		binaryinstruction[9]=0;
		binaryinstruction[10]=0;
		binaryinstruction[26]=0;
		binaryinstruction[27]=0;
		binaryinstruction[28]=0;
		binaryinstruction[29]=0;
		binaryinstruction[30]=0;
		binaryinstruction[31]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		fourthterm=bitset<5>(stoi(fourthterm)).to_string();
		for(int x=0;x<=4;x++)
		{
			binaryinstruction[21+x]=tobool(fourthterm[x]);
		}

	 }
	else if(firstterm=="and")
	{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		binaryinstruction[21]=0;
		binaryinstruction[22]=0;
		binaryinstruction[23]=0;
		binaryinstruction[24]=0;
		binaryinstruction[25]=0;
		binaryinstruction[26]=1;
		binaryinstruction[27]=0;
		binaryinstruction[28]=0;
		binaryinstruction[29]=1;
		binaryinstruction[30]=0;
		binaryinstruction[31]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(fourthterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
	}
else if(firstterm=="andi")
{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=1;
		binaryinstruction[3]=1;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		register_encode(secondterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		fourthterm=bitset<16>(stoi(fourthterm)).to_string();
		cout <<fourthterm;
		for(int x=0;x<=15;x++)
		{
			binaryinstruction[16+x]=tobool(fourthterm[x]);
		}


	}
else if(firstterm=="nor")
{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(fourthterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		binaryinstruction[21]=0;
		binaryinstruction[22]=0;
		binaryinstruction[23]=0;
		binaryinstruction[24]=0;
		binaryinstruction[25]=0;
		binaryinstruction[26]=1;
		binaryinstruction[27]=0;
		binaryinstruction[28]=0;
		binaryinstruction[29]=1;
		binaryinstruction[30]=1;
		binaryinstruction[31]=1;
}
else if (firstterm=="sub")
{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		binaryinstruction[21]=0;
		binaryinstruction[22]=0;
		binaryinstruction[23]=0;
		binaryinstruction[24]=0;
		binaryinstruction[25]=0;
		binaryinstruction[26]=1;
		binaryinstruction[27]=0;
		binaryinstruction[28]=0;
		binaryinstruction[29]=0;
		binaryinstruction[30]=1;
		binaryinstruction[31]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(fourthterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);

}
else if(firstterm=="slt")
{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=0;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		binaryinstruction[21]=0;
		binaryinstruction[22]=0;
		binaryinstruction[23]=0;
		binaryinstruction[24]=0;
		binaryinstruction[25]=0;
		binaryinstruction[26]=1;
		binaryinstruction[27]=0;
		binaryinstruction[28]=1;
		binaryinstruction[29]=0;
		binaryinstruction[30]=1;
		binaryinstruction[31]=0;
		register_encode(secondterm,binaryinstruction[16],binaryinstruction[17],binaryinstruction[18],binaryinstruction[19],binaryinstruction[20]);
		register_encode(thirdterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(fourthterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
}
else if(firstterm=="beq")
{
		binaryinstruction[0]=0;
		binaryinstruction[1]=0;
		binaryinstruction[2]=0;
		binaryinstruction[3]=1;
		binaryinstruction[4]=0;
		binaryinstruction[5]=0;
		register_encode(secondterm,binaryinstruction[6],binaryinstruction[7],binaryinstruction[8],binaryinstruction[9],binaryinstruction[10]);
		register_encode(thirdterm,binaryinstruction[11],binaryinstruction[12],binaryinstruction[13],binaryinstruction[14],binaryinstruction[15]);
		int labeladdress_integer=labels.get_address(fourthterm)-(counter*4);
		labeladdress_integer=labeladdress_integer/4;
		labeladdress_integer=labeladdress_integer-1;
		string labeladdress_string=bitset<16>(labeladdress_integer).to_string();
		for (int x=0;x<=15;x++)
		{
			binaryinstruction[16+x]=tobool(labeladdress_string[x]);
		}


	}
	 }
	 //testing
	 ofstream myfile2;
	 myfile2.open ("instruction_memory.list", std::ofstream::out | std::ofstream::app);

for (int f=0;f<=31;f=f+8)
{
	myfile2 <<binaryinstruction[f]<<binaryinstruction[f+1]<<binaryinstruction[f+2]<<binaryinstruction[f+3]<<binaryinstruction[f+4]<<binaryinstruction[f+5]<<binaryinstruction[f+6]<<binaryinstruction[f+7]<<endl;
}
//end testing
}
cout<<"assembling finished!"<<endl<<"Please refer to binary instruction file to check for the binary instruction"<<endl;
system("pause");
}
