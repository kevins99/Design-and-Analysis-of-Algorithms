//#include<stdio.h>
//#include<string.h>
#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;


struct mnemoreg
{
	string name;
	string type;
	int size;
	string opcode;
	int chain;
	

};

mnemoreg s[26];

void init()
{
	for(int i=0;i<26;i++)
	{
		s[i].chain=-1;
		s[i].name="$";
	}
}




int index_calculation(string x)
{
	int numeric=0;

	numeric=x[0];

	cout<<"ascii values is : ";
	cout<<numeric<<endl;

	return(numeric%26);

}


void display_mnemonic_table()
{
	cout<<"----------------------------------------------------\n";
	cout<<"|  Index   |"<<"   Name   |"<<" Chain Bit  |\n";
	cout<<"----------------------------------------------------\n";

	for(int i=0;i<26;i++)
	{
		cout<<"|"<<setw(10)<<i<<"|"<<setw(10)<<s[i].name<<"|"<<setw(12)<<s[i].chain<<"|";
		cout<<"\n";
	}

	cout<<"----------------------------------------------------\n";

}


void create_mnemonic_table(string name,string type,int size,string opcode)
{


	int index;
	int temp,temp2;
	

	index=index_calculation(name);

	if(s[index].name=="$") //if entry is a new entry for that index then insert directly and return
	{
		s[index].name=name;
		s[index].type=type;
		s[index].size=size;
		s[index].opcode=opcode;
		return;
	}

	temp2=index;

	while(temp2!=index_calculation(s[index].name) && s[index].name!="$")
		index=(index+1)%26;

	//index=temp2;

	while(s[index].chain!=-1) //Now using chain bits go till end of chain for given index
			index=s[index].chain;


	temp=index;

	while(s[temp].name!="$") //Now increment index by one till we get empty place to store new record
		temp=(temp+1)%26;


	//Now use this index of new record and assign it to chain bit of "previous last record"
	if(index!=temp)
		s[index].chain=temp;


	s[temp].name=name;
	s[temp].type=type;
	s[temp].size=size;
	s[temp].opcode=opcode;

}



int search_mnemonic_table(string x)
{
	int index=index_calculation(x);


	while(1)
	{
		if(s[index].name==x)
			{
				cout<<"Record found at index "<<index;
				return index;
			}
		else if(s[index].chain==-1 && index_calculation(s[index].name)==index)
			{
				cout<<"Record not found";
				return -1;
			}
		else
		{
			if(index_calculation(s[index].name)!=index)
				index=(index+1)%26;
			else
				index=s[index].chain;
		}

	}


}


void mnemonic_table_init()
{
    init();
    create_mnemonic_table("MOVE","IS",1,"(IS,01)");
    create_mnemonic_table("ADD","IS",1,"(IS,02)");
    create_mnemonic_table("AND","IS",1,"(IS,02)");
    create_mnemonic_table("MUL","IS",2,"(IS,03)");
    
    
    	create_mnemonic_table("ADD",2);
	create_mnemonic_table("SUB",2);
	create_mnemonic_table("DIV",2);
	create_mnemonic_table("MUL",2);
	create_mnemonic_table("START",1);
	create_mnemonic_table("EQU",1);
	create_mnemonic_table("LTORG",1);
	create_mnemonic_table("END",1);
	create_mnemonic_table("DC",1);
	create_mnemonic_table("DS",1);
	create_mnemonic_table("MOVER",2);
	create_mnemonic_table("PRINT",1);
	create_mnemonic_table("STOP",1);
	create_mnemonic_table("ORIGIN",1);
	create_mnemonic_table("MOVEM",2);
	create_mnemonic_table("BC",1);
	create_mnemonic_table("READ",1);			

    display_mnemonic_table();
   // search_mnemonic_table("ADD");


}
int main()
{

   mnemonic_table_init();
   /*
   char ip[100];
   char *tok;
   FILE *fp;
   fp=fopen("Assemblycode.txt","r");
   
   while(fgets(ip,100,fp)!=NULL)
   {
   	printf("%s",ip);
   	tok=strtok(ip," ");
   	
   	while (tok != NULL)
        {
         printf("%s\n",tok);
         tok = strtok (NULL, " ");   //pass NULL to tell function to continue tokenizing
        }
   	
   }
   
   
   
   fclose(fp);
   */

}


