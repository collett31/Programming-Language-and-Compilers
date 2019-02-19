#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
 //Lexical analyzer code
 
using namespace std;
 
int isKeyword(char buffer[]){
	char keywords[5][10] = {"char","double","display","int","string"};
	int i, flag = 0;
	
	for(i = 0; i < 5; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	
	return flag;
}
 
int main(){
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("program.txt");
	int i,j=0;
	
	if(!fin.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}
	
	while(!fin.eof()){
   		ch = fin.get();
   		
		for(i = 0; i < 6; ++i){
   			if(ch == operators[i])
   				cout<<ch<<" is operator\n";
   		}
   		
   		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;
   				   				
   				if(isKeyword(buffer) == 1)
   					cout<<buffer<<" is keyword\n";
   				else
   					cout<<buffer<<" is indentifier\n";
   		}
   		
	}
	
	fin.close();
	
	return 0;
}
